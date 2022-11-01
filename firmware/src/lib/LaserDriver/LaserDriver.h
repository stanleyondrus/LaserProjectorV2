#ifndef LASER_DRIVER_H
#define LASER_DRIVER_H
#include <Arduino.h>

#define LASER_PIN 26

#define PWM_CH 0 // PWM Channel
#define PWM_F 200 // 200Hz frequency
#define PWM_R 8 // 8bit resolution

class LaserDriver {
public:
	void init();
	void setState(uint8_t state);
	void setIntensity(uint8_t intensity);
	void setMaxIntensity(uint8_t intensity);
	uint8_t getIntensity();
	uint8_t getMaxIntensity();
	uint8_t getState() { return current_state; }
private:
	uint8_t current_state = 0;
};
#endif // LASER_DRIVER_H