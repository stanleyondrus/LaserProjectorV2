#ifndef ANIM_LIB_H
#define ANIM_LIB_H
#include <Arduino.h>
#include "../ScannerDriver/ScannerDriver.h"
#include "../LaserDriver/LaserDriver.h"

#define MAX_ANIM_POINTS 100

#define SCALING_1 1 // 1x
#define SCALING_2 2 // 0.5x

struct AnimPoint {
	uint16_t x;
	uint16_t y;
	uint8_t laser; // 0-OFF 1-ON
};

class AnimLib {
public:
	AnimLib(ScannerDriver& scanner_a, LaserDriver laser_a) : scanner(scanner_a), laser(laser_a) {}
	uint8_t home();
	uint8_t add_anim_point(uint16_t x, uint16_t y, uint8_t laser);
	void setMode(uint8_t mode);
	void setPreset(uint8_t preset);
	void incrementPreset();
	void setScaling(uint8_t scaling);
	uint8_t getMode() { return current_mode; }
	uint8_t getPreset() { return current_preset; };
	uint8_t getScaling() { return current_scaling; };
	void update();
	uint16_t test_anim_x = 20;
	uint16_t test_anim_y = 20;
	uint8_t total_presets = 14;
private:
	ScannerDriver& scanner;
	LaserDriver& laser;
	AnimPoint anim[MAX_ANIM_POINTS];
	uint16_t anim_count = 0; // animation count
	uint16_t anim_index = 0; // animation index
	uint8_t current_mode = 0;
	uint8_t current_preset = 1;
	uint8_t current_scaling = 1;
	uint8_t current_max_speed[2] = {3,3}; // max speed for S1,S2
	uint8_t current_slow_scan[2] = {0,0}; // 0-1 [x,y]
	uint8_t scaling_divider = 1;
	unsigned long last_change = 0;
	uint16_t random_delay = 1000;
	uint16_t scaled_points[2] = {0,0};
};
#endif // ANIM_LIB_H