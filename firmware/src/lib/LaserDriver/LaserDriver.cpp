#include "LaserDriver.h"

uint8_t current_intensity = 255;
uint8_t max_intensity = 255;

void LaserDriver::init() {
	ledcSetup(PWM_CH, PWM_F, PWM_R);
	ledcAttachPin(LASER_PIN, PWM_CH);
	ledcWrite(PWM_CH, 0);
}

void LaserDriver::setState(uint8_t state) {
	if (state == 0) {
		ledcWrite(PWM_CH, 0);
		current_state = 0;
	}
	else if (state == 1) {
		  ledcWrite(PWM_CH, current_intensity);
		current_state = 1;
	}
}

void LaserDriver::setIntensity(uint8_t intensity) {
	current_intensity = intensity;
	if (current_state == 1) ledcWrite(PWM_CH, current_intensity);
}

void LaserDriver::setMaxIntensity(uint8_t intensity) {
	max_intensity = intensity;
	setIntensity(intensity);
}

uint8_t LaserDriver::getIntensity() {
	return current_intensity;
}

uint8_t LaserDriver::getMaxIntensity() {
	return max_intensity;
}