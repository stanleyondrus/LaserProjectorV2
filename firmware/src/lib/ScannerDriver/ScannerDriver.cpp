#include "ScannerDriver.h"

BasicStepperDriver stepperX(MOTOR_STEPS, DIR_X, STEP_X);
BasicStepperDriver stepperY(MOTOR_STEPS, DIR_Y, STEP_Y);

// MultiDriver controller(stepperX, stepperY);
SyncDriver controller(stepperX, stepperY);

void ScannerDriver::init() {
	pinMode(EN, OUTPUT);
	digitalWrite(EN, LOW);
	pinMode(MODE1, OUTPUT);
	digitalWrite(MODE1, LOW);
	pinMode(MODE2, OUTPUT);
	digitalWrite(MODE2, LOW);
	stepperX.begin(MOTOR_RPM, MICROSTEPS);
	stepperY.begin(MOTOR_RPM, MICROSTEPS);
	setSpeed(current_speed);
}

void ScannerDriver::move(uint16_t x, uint16_t y) {
	int16_t to_move_x = -(((x <= POS_X_MIN) ? POS_X_MIN : (x >= POS_X_MAX) ? POS_X_MAX : x) - pos_x); // invert motor direction 
	int16_t to_move_y = ((y <= POS_Y_MIN) ? POS_Y_MIN : (y >= POS_Y_MAX) ? POS_Y_MAX : y) - pos_y;

	// Serial.printf("%u\t%u\t%d\t%d\n", x, y, to_move_x, to_move_y);

	controller.move(to_move_x, to_move_y);
	pos_x = x;
	pos_y = y;
}

uint8_t ScannerDriver::execute_home() {
	uint8_t x = 0;
	uint8_t y = 0;
	uint8_t flag = 0;

	uint8_t current_speed_old = current_speed;

	unsigned long timeout_start = millis();

	hd.setState(1);
	if (hd.isHomed(x, y)) { hd.setState(0); return 1; } // error

	setSpeed(2);
	setState(1);
	if (x) controller.move(-50 * MICROSTEPS, 0);
	if (y) controller.move(0, 50 * MICROSTEPS);
	while ((!x || !y) && !flag) {
		if (!x && !y) controller.move(-1 * MICROSTEPS, 1 * MICROSTEPS);
		else if (!x) controller.move(-1 * MICROSTEPS, 0);
		else if (!y) controller.move(0, 1 * MICROSTEPS);
		if (hd.isHomed(x, y) || millis() - timeout_start >= 3000) flag = 1;
	}
	hd.setState(0);

	if (flag) { // error
		setState(0);
		return 1;
	}

	setSpeed(1);
	// controller.move(POS_HOME_X_OFFSET * MICROSTEPS, POS_HOME_Y_OFFSET * MICROSTEPS);
	controller.move(-home_offset_x * MICROSTEPS, home_offset_y * MICROSTEPS);
	setState(0);
	setSpeed(current_speed_old);
	// set current position as origin (0,0)
	pos_x = 0;
	pos_y = 0;

	return 0;
}

void ScannerDriver::setState(uint8_t state) {
	digitalWrite(EN, state ? 1 : 0);
}

void ScannerDriver::setSpeed(uint8_t speed, uint8_t slow_scan_x, uint8_t slow_scan_y) {
	if (speed == 1) current_rpm = SPEED_1;
	else if (speed == 2) current_rpm = SPEED_2;
	else if (speed == 3) current_rpm = SPEED_3;
	else return;
	current_speed = speed;
	stepperX.setRPM((slow_scan_x) ? SLOW_SCAN_SPEED : current_rpm);
	stepperY.setRPM((slow_scan_y) ? SLOW_SCAN_SPEED : current_rpm);
}