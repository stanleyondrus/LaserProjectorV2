#include "HomingDriver.h"

void HomingDriver::init() {
	pinMode(HOME_G, OUTPUT);
	digitalWrite(HOME_G, 0);
	pinMode(HOME_X, INPUT);
	pinMode(HOME_Y, INPUT);
}

void HomingDriver::setState(uint8_t state) {
	digitalWrite(HOME_G, state ? 1 : 0);
}

uint8_t HomingDriver::getDistance(uint16_t& x, uint16_t& y) {
	x = 0; y = 0;
	uint8_t flag[] = { 0,0 };
	uint8_t state[] = { 1,1 };
	pinMode(HOME_X, OUTPUT);
	pinMode(HOME_Y, OUTPUT);
	digitalWrite(HOME_X, 1);
	digitalWrite(HOME_Y, 1);
	delayMicroseconds(10);
	pinMode(HOME_X, INPUT);
	pinMode(HOME_Y, INPUT);
	long time = micros();
	while ((state[0] || state[1]) && (micros() - time < 3000)) {
		state[0] = digitalRead(HOME_X);
		state[1] = digitalRead(HOME_Y);
		if (!state[0] && !flag[0]) {
			x = micros() - time;
			flag[0] = 1;
		}
		if (!state[1] && !flag[1]) {
			y = micros() - time;
			flag[1] = 1;
		}
	}
	return (flag[0] && flag[1]) ? 0 : 1;
}

uint8_t HomingDriver::isHomed(uint8_t& x, uint8_t& y) {
	uint16_t x_distance = 0;
	uint16_t y_distance = 0;
	uint8_t ret = getDistance(x_distance, y_distance);
	if (ret) return 1; // error

	// Serial.print(x_distance);
	// Serial.print("\t");
	// Serial.println(y_distance);

	x = (x_distance <= HOME_THRESHOLD) ? 1 : 0;
	y = (y_distance <= HOME_THRESHOLD) ? 1 : 0;
	return 0;
}