#include "AnimLib.h"

uint8_t AnimLib::home() {
	uint8_t laser_state_old = laser.getState();
	laser.setState(0);
	uint8_t ret = scanner.execute_home();
	if (laser_state_old) laser.setState(1);
	return ret;
}

uint8_t AnimLib::add_anim_point(uint16_t x, uint16_t y, uint8_t laser) {
	if (anim_count + 1 > MAX_ANIM_POINTS) return 1;
	AnimPoint p;
	p.x = x;
	p.y = y;
	p.laser = laser;
	anim[anim_count] = p;
	anim_count++;
	return 0;
}

// increment total_presets when adding new
void AnimLib::setPreset(uint8_t preset) {
	anim_count = 0;
	anim_index = 0;
	current_max_speed[0] = 3;
	current_max_speed[1] = 3;
	current_slow_scan[0] = 0;
	current_slow_scan[1] = 0;
	switch (preset) {
	case 1:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 1);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 1);
		current_max_speed[1] = 2;
		break;
	case 2:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX/2, POS_Y_MAX, 1);
		current_max_speed[0] = 2;
		current_max_speed[1] = 2;
		break;
	case 3:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 0);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 0);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 1);
		current_max_speed[1] = 2;
		break;
	case 4:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 0);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 1);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 0);
		current_max_speed[1] = 2;
		break;
	case 5:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 0);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX/2, 0);
		add_anim_point(POS_X_MIN, POS_Y_MAX/2, 1);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 0);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 1);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 0);
		add_anim_point(POS_X_MIN, POS_Y_MIN, 1);
		add_anim_point(POS_X_MIN, POS_Y_MAX/2, 0);
		add_anim_point(POS_X_MAX, POS_Y_MAX/2, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 0);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 1);
		current_max_speed[1] = 2;
		break;
	case 6:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 0);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 1);
		add_anim_point(POS_X_MAX/2, POS_Y_MAX, 0);
		add_anim_point(POS_X_MIN/2, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 0);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 1);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 0);
		add_anim_point(POS_X_MIN, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX/2, POS_Y_MIN, 0);
		add_anim_point(POS_X_MAX/2, POS_Y_MAX, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 0);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 1);
		current_max_speed[1] = 2;
		break;
	case 7:
		add_anim_point(POS_X_MIN, POS_Y_MAX/2, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX/2, 1);
		current_max_speed[0] = 2;
		current_max_speed[1] = 2;
		break;
	case 8:
		add_anim_point(POS_X_MAX/2, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX/2, POS_Y_MAX, 1);
		current_max_speed[0] = 2;
		current_max_speed[1] = 2;
		break;
	case 9:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 0);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 1);
		add_anim_point(POS_X_MIN, POS_Y_MAX, 0);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 1);
		current_max_speed[1] = 2;
		break;
	case 10:
		add_anim_point(POS_X_MIN, POS_Y_MIN, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 1);
		current_max_speed[0] = 2;
		current_max_speed[1] = 2;
		break;
	case 11:
		add_anim_point(POS_X_MIN, POS_Y_MAX, 1);
		add_anim_point(POS_X_MAX, POS_Y_MIN, 1);
		current_max_speed[0] = 2;
		current_max_speed[1] = 2;
		break;
	case 12:
		for (uint8_t i = 0; i <= 20; i++) {
			add_anim_point(POS_X_MIN, i, 1);
			add_anim_point(POS_X_MAX, i, 1);
		}
		for (uint8_t i = 0; i <= POS_X_MAX; i++) {
			add_anim_point(POS_X_MIN, POS_Y_MAX-i, 1);
			add_anim_point(POS_X_MAX, POS_Y_MAX-i, 1);
		}
		current_max_speed[0] = 2;
		current_max_speed[1] = 2;
		current_slow_scan[1] = 1;
		break;
	case 13:
		for (uint8_t i = 0; i <= POS_X_MAX; i++) {
			add_anim_point(i, POS_Y_MIN, 1);
			add_anim_point(i, POS_Y_MAX, 1);
		}
		for (uint8_t i = 0; i <= POS_X_MAX; i++) {
			add_anim_point(POS_X_MAX-i, POS_Y_MIN, 1);
			add_anim_point(POS_X_MAX-i, POS_Y_MAX, 1);
		}
		current_max_speed[0] = 2;
		current_max_speed[1] = 2;
		current_slow_scan[0] = 1;
		break;
	case 14:
		add_anim_point(0, 0, 0);
		add_anim_point(3, 0, 1);
		add_anim_point(POS_X_MAX, 0, 0);
		add_anim_point(POS_X_MAX, 3, 1);
		add_anim_point(POS_X_MAX, POS_Y_MAX, 0);
		add_anim_point(POS_X_MAX - 3, POS_Y_MAX, 1);
		add_anim_point(0, POS_Y_MAX, 0);
		add_anim_point(0, POS_Y_MAX - 3, 1);
		current_max_speed[1] = 2;
		break;
	default: return;
	}
	current_preset = preset;
}

void AnimLib::setMode(uint8_t mode) {
	if (mode == 1 || mode == 2) {
		laser.setIntensity(laser.getMaxIntensity());
		setScaling(1);
		setPreset(current_preset);
		scanner.setSpeed(3);
		AnimLib::home();
		scanner.setState(1);
	}
	else if (mode == 0 || mode == 3)  {
		if (scanner.getState()) scanner.move(0,0);
		scanner.setState(0);
		laser.setState(0);
	}
	else return;
	current_mode = mode;	
}

void AnimLib::setScaling(uint8_t scaling) {
	if (scaling == 1) scaling_divider = SCALING_1;
	else if (scaling == 2) scaling_divider = SCALING_2;
	else return;
	current_scaling = scaling;
}

void AnimLib::update() {
	if (current_mode == 1 || current_mode == 2) {
		if (current_mode == 2) {
			// randomly change speed, scaling, and preset
			if (millis() - last_change > random_delay) {
				setPreset(random(1, 14));
				setScaling((random(1, 5) < 4) ? 1 : 2);
				scanner.setSpeed(random(1, 4));
				random_delay = random(500, 2000);
				laser.setIntensity((random(1, 5) < 4) ? laser.getMaxIntensity() : (laser.getMaxIntensity()/2));
				last_change = millis();

				Serial.print(last_change);
				Serial.print("\t");
				Serial.print(getPreset());
				Serial.print("\t");
				Serial.print(getScaling());
				Serial.print("\t");
				Serial.print(scanner.getSpeed());
				Serial.print("\t");
				Serial.println(random_delay);
			}
		}
		 laser.setState((anim[anim_index].laser==1) ? 1 : 0);
		 if (scanner.getSpeed() > current_max_speed[getScaling() - 1]) scanner.setSpeed(current_max_speed[getScaling() - 1]);
		 scanner.setSpeed(scanner.getSpeed(), current_slow_scan[0], current_slow_scan[1]);
		 if (current_scaling == 1) scanner.move(anim[anim_index].x, anim[anim_index].y);
		 else {
			 scaled_points[0] = anim[anim_index].x / scaling_divider;
			 scaled_points[1] = anim[anim_index].y / scaling_divider;
			 scanner.move(scaled_points[0] + ((20 - scaled_points[0]) / 2), scaled_points[1] + ((20 - scaled_points[1]) / 2));
		 }
		 
		 anim_index = (anim_index + 1) % anim_count; // increment index counter with rollover
	}
}