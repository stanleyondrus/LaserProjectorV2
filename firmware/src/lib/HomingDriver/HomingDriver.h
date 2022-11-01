#ifndef HOMING_DRIVER_H
#define HOMING_DRIVER_H
#include <Arduino.h>

#define HOME_G 27
#define HOME_X 13
#define HOME_Y 14

#define HOME_THRESHOLD 200

class HomingDriver {
public:
	void init();
	void setState(uint8_t state);
	uint8_t getDistance(uint16_t &x, uint16_t &y);
	uint8_t isHomed(uint8_t &x, uint8_t &y);
};
#endif // HOMING_DRIVER_H