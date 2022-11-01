#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "LittleFS.h"
#include <AsyncElegantOTA.h>

#include "ScannerDriver.h"
#include "HomingDriver.h"
#include "LaserDriver.h"
#include "AnimLib.h"

#define FW_VER_MAJ 0
#define FW_VER_MIN 1

#define BTN1 0 // GPIO0
#define BTN2 4 // GPIO4

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

#define FORMAT_LITTLEFS_IF_FAILED false

HomingDriver hd;
ScannerDriver scanner(hd);
LaserDriver laser;
AnimLib anim(scanner, laser);

const char* ssid = "<your_ssid>";
const char* password = "<your_pass>";

const char* soft_ap_ssid = "LaserProjector";
const char* soft_ap_password = "LaserProjector2020";

char incoming_packet[30];
uint8_t process_flag = 0;

unsigned long last_btn_press = 0;

void sendStatus() {
    // M[0-3] - Mode [OFF,MAN,AUT,EXT]
    // L[0-255] - Laser intensity
    // P[1-20] - Preset (used when M1)
    // S[1-2] - Scaling (used when M1)
    // V[1-3] - Speed (used when M1)
    // C0[0-Xmax,0-Ymax,0-1] - Current position, laser [X,Y,Laser]

    char s[50];
    sprintf(s, "M%u;L%u;P%u;S%u;V%u;C0%u,%u,%u\0", anim.getMode(), laser.getIntensity(), anim.getPreset(), anim.getScaling(), scanner.getSpeed(), scanner.getX(), scanner.getY(), laser.getState());

    ws.textAll(s); // notify WebSocket clients
    Serial.println(s); // notify Serial clients
}

void handleIncomingPackets() {
    // Handle Serial
    if (Serial.available()) {
        uint8_t counter = 0;
        while (Serial.available() && counter < 30) {
            incoming_packet[counter++] = Serial.read();
        }
        incoming_packet[counter] = '\0';
        process_flag = 1;
    }
}

void parseMessage(char* msg) {
    // R - Request status
    // H - Home steppers
    // M[0-3] - Set mode [OFF,MAN,AUT,EXT]
    // L[0-255] - Set laser intensity
    // P[1-20] - Set preset (applicable when M1)
    // S[1-2] - Set scaling (applicable when M1)
    // V[1-3] - Set speed (applicable when M1)
    // C0[0-Xmax,0-Ymax,0-1] - External control [X,Y,Laser]
    // C1[0-Xmax,0-Ymax] - External control [X,Y]
    // C2[0-1] - External control [Laser On, Laser Off]
    // Z - Request FW version

    if (msg[0] == 'R'); // Do nothing, just send status
    else if (msg[0] == 'H') {
        if (anim.getMode() == 1 || anim.getMode() == 2) anim.setMode(anim.getMode());
        else anim.home();
    }
    else if (msg[0] == 'M') {
        anim.setMode(atoi(msg + 1));
    }
    else if (msg[0] == 'L') {
        uint8_t intensity = atoi(msg + 1);
        laser.setMaxIntensity(intensity);
    }
    else if (msg[0] == 'P') {
        anim.setPreset(atoi(msg + 1));
    }
    else if (msg[0] == 'S') {
        anim.setScaling(atoi(msg + 1));
    }
    else if (msg[0] == 'V') {
        scanner.setSpeed(atoi(msg + 1));
    }
    else if (msg[0] == 'C') {
        if (msg[1] == '0') {
            char* ctrpacket = strtok(msg + 2, ",");
            uint8_t i = 0;
            uint16_t x = 0;
            uint16_t y = 0;
            uint8_t l = 0;
            while (ctrpacket != 0) {
                if (i == 0) x = atoi(ctrpacket);
                if (i == 1) y = atoi(ctrpacket);
                if (i == 2) l = atoi(ctrpacket);
                ctrpacket = strtok(0, ";"); // search for another
                i++;
            }
            laser.setState(l);
            scanner.setState(1);
            scanner.move(x, y);
            scanner.setState(0);
        }
        else if (msg[1] == '1') {
            char* ctrpacket = strtok(msg + 2, ",");
            uint8_t i = 0;
            uint16_t x = 0;
            uint16_t y = 0;
            while (ctrpacket != 0) {
                if (i == 0) x = atoi(ctrpacket);
                if (i == 1) y = atoi(ctrpacket);
                ctrpacket = strtok(0, ";"); // search for another
                i++;
            }
            scanner.setState(1);
            scanner.move(x, y);
            scanner.setState(0);
        }
        else if (msg[1] == '2') {
            laser.setState((uint8_t)atoi(msg + 2));
        }
    }
    else if (msg[0] == 'D') {
        scanner.home_offset_x = atoi(msg + 1);
        Serial.print(scanner.home_offset_x);
        Serial.print("\t");
        Serial.println(scanner.home_offset_y);
    }
    else if (msg[0] == 'E') {
        scanner.home_offset_y = atoi(msg + 1);
        Serial.print(scanner.home_offset_x);
        Serial.print("\t");
        Serial.println(scanner.home_offset_y);
    }
    else if (msg[0] == 'F') {
        anim.test_anim_x = atoi(msg + 1);
        Serial.print(anim.test_anim_x);
        Serial.print("\t");
        Serial.println(anim.test_anim_y);
    }
    else if (msg[0] == 'G') {
        anim.test_anim_y = atoi(msg + 1);
        Serial.print(anim.test_anim_x);
        Serial.print("\t");
        Serial.println(anim.test_anim_y);
    }
    else if (msg[0] == 'Z') {
        char s[10];
        sprintf(s, "Z%d.%d;", FW_VER_MAJ, FW_VER_MIN);
        ws.textAll(s);
    }
}

void processIncomingPacket() {
    if (process_flag == 0) return;
    char* packet = strtok((char*)incoming_packet, ";"); // split on ;
    while (packet != 0) {
        // Serial.println(packet);
        parseMessage(packet);
        packet = strtok(0, ";"); // search for another
    }
    sendStatus();
    process_flag = 0;
}

void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
    switch (type) {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
    {
        AwsFrameInfo* info = (AwsFrameInfo*)arg;
        // Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            data[len] = 0;
            strcpy(incoming_packet, (char*)data);
            process_flag = 1;
        }
        break;
    }
    case WS_EVT_ERROR:
        Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
        break;
    case WS_EVT_PONG:
        Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char*)data : "");
        break;
    }
}

uint8_t btnPressed(uint8_t pin) {
    return !digitalRead(pin);
}

void handleBtn() {
    // BTN1 pressed + BTN2 to change modes 0-2
    // BTN1 2s hold to mode 0 
    if (btnPressed(BTN1)) last_btn_press = millis();
    while (btnPressed(BTN1)) {
        laser.setState(0);
        if (btnPressed(BTN2)) {
            uint8_t next_mode = anim.getMode() + 1;
            if (next_mode > 2) next_mode = 0;
            anim.setMode(next_mode);
        }
        while (btnPressed(BTN2));
        if (millis() - last_btn_press >= 2000) {
            anim.setMode(0);
        }
    }

    if (btnPressed(BTN2)) {
        // In MAN mode, BTN2 to increment preset
        if (anim.getMode() == 1) {
            uint8_t next_preset = anim.getPreset() + 1;
            if (next_preset > anim.total_presets) next_preset = 1;
            anim.setPreset(next_preset);
            while (btnPressed(BTN2));
        }
        else anim.home();
    }

    last_btn_press = millis();
}

void setup() {
    Serial.begin(115200);

    Serial.println("LaserProjector V2");
    Serial.print("FW VER: ");
    Serial.print(FW_VER_MAJ);
    Serial.print(".");
    Serial.println(FW_VER_MIN);

    pinMode(BTN1, INPUT_PULLUP);
    pinMode(BTN2, INPUT_PULLUP);

    laser.init();
    hd.init();
    scanner.init();

    randomSeed(analogRead(2));

    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
        Serial.println("LittleFS Mount Failed");
        return;
    }

    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.softAP(soft_ap_ssid, soft_ap_password);
    WiFi.begin(ssid, password);

    unsigned long timeout = millis();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED && (millis() - timeout < 3000)) {
        Serial.print(".");
        delay(500);
    }
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.softAPIP());

    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(LittleFS, "/index.html", "text/html", false);
    });

    server.serveStatic("/", LittleFS, "/");

    AsyncElegantOTA.begin(&server);

    server.begin();
}

void loop() {
    ws.cleanupClients();
    handleBtn();
    handleIncomingPackets();
    processIncomingPacket();
    anim.update();
}