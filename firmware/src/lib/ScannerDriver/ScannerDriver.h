#ifndef SCANNER_DRIVER_H
#define SCANNER_DRIVER_H
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include "../HomingDriver/HomingDriver.h"

#define MOTOR_STEPS 200
#define MOTOR_RPM 50

#define DIR_X 22
#define STEP_X 21
#define DIR_Y 5
#define STEP_Y 17

#define EN 23

#define MODE1 18
#define MODE2 19

#define MICROSTEPS 1

#define POS_X_MIN 0
#define POS_X_MAX 20
#define POS_Y_MIN 0
#define POS_Y_MAX 20

#define POS_HOME_X_OFFSET 105
#define POS_HOME_Y_OFFSET 35

#define SPEED_1 100
#define SPEED_2 110
#define SPEED_3 120

#define SLOW_SCAN_SPEED 10

class ScannerDriver {
public:
	ScannerDriver(HomingDriver& hd_a) : hd(hd_a){}
	void init();
	void move(uint16_t x, uint16_t y);
	uint8_t execute_home();
	void setState(uint8_t state);
	uint8_t getState() { return digitalRead(EN); }
	void setSpeed(uint8_t speed, uint8_t slow_scan_x = 0, uint8_t slow_scan_y = 0);
	uint8_t getSpeed() { return current_speed; }
	uint16_t getX() { return pos_x; }
	uint16_t getY() { return pos_y; }
	uint16_t home_offset_x = POS_HOME_X_OFFSET;
	uint16_t home_offset_y = POS_HOME_Y_OFFSET;
private:
	HomingDriver& hd;
	uint8_t current_speed = 3;
	uint16_t current_rpm = MOTOR_RPM;
	uint16_t pos_x = 0;
	uint16_t pos_y = 0;
};
#endif // SCANNER_DRIVER_H