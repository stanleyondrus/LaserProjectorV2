[![](https://stanleyprojects.com/projects/laserprojector_v2/thumbnails/banner1.png)](https://stanleyprojects.com/projects/laserprojector_v2/)
[![](https://stanleyprojects.com/projects/laserprojector_v2/thumbnails/banner2.png)](https://stanleyprojects.com/projects/laserprojector_v2/)

## Introduction
LaserProjector V2 is a battery-powered, ESP32-based laser XY scanner using stepper motors to deflect the beam. It has auto-homing functionality, and can be controlled wirelessly (Wi-Fi & Bluetooth).

## Features
- Hybrid Wi-Fi operation mode (STA & AP)
- Webserver GUI with custom WebSocket protocol
- Concurrent multi-user control
- Automatic/Manual/External scanning mode
- Parallel auto-homing
- Battery-powered

## Links
- [Documentation [stanleyprojects.com]](https://stanleyprojects.com/projects/laserprojector_v2/)
- [Article [hackaday.com]](https://hackaday.com/2022/11/02/laser-project-relies-on-steppers-rather-than-galvanometers/)
- [Video [youtube.com]](https://youtu.be/w1O48Ysdiiw)
- [Project [hackaday.io]](https://hackaday.io/project/188046-laserprojector-v2)
- [Project [hackster.io]](https://www.hackster.io/stanleyprojects/laserprojector-v2-fa77cf)

## Design
![](https://stanleyprojects.com/projects/laserprojector_v2/spec_table.png)
![](https://stanleyprojects.com/projects/laserprojector_v2/layout_render.png)
![](https://stanleyprojects.com/projects/laserprojector_v2/schematic.png)

## How to build your own release
### Prerequisites
- Visual Studio Code with PlatformIO extension
- 3.3V USB to Serial (e.g. FT232RL)
### Building
1. Open __*firmware/src*__ folder in VSCode
2. In __*firmware/src/src/main.cpp*__ you can sustomize SSID and PASSWORD for Wi-Fi STA mode:
```cpp
const char* ssid = "<your_ssid>";
const char* password = "<your_pass>";
```
3. In __*firmware/src/platformio.ini*__ set the correct *_upload_port_*, or remove to auto-detect.

4. Build and upload the filesystem
    - PlatformIO > esp32serial > Platform > Build Filesystem Image
    - PlatformIO > esp32serial > Platform > Upload Filesystem Image

5. Build and upload the firmware
    - PlatformIO > esp32serial > General > Upload

## Pre-built binaries
The binary is fully contained (bootloader, firmware, and filesystem), so it can be flashed to address 0x0.

The easiest way is to use this web tool: https://stanleyprojects.com/projects/laserprojector_v2/install

After the firmware is loaded, any subsequent updates can be done OTA in browser by visiting _http://\<esp32-ip-address\>/update_

|Version|Firmware|
|-|-|
|0.1|[LaserProjectorV2_firmware_v0.1.bin](https://github.com/stanleyondrus/LaserProjectorV2/releases/download/v0.1/LaserProjectorV2_v0.1.bin)|


## Credits
- [A Beginner's Guide to the ESP8266](https://tttapa.github.io/ESP8266/Chap01%20-%20ESP8266.html)
- [ElegantOTA](https://github.com/ayushsharma82/ElegantOTA)
- [StepperDriver](https://github.com/laurb9/StepperDriver)
