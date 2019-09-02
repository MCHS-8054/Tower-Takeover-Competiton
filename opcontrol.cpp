#include "main.h"
#include "globals.hpp"

bool torque = false;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 void in_n_out() {
 	while(master.get_digital(DIGITAL_L1)) {
 		if(!master.get_digital(DIGITAL_L1)) {
 			intakeR.move_velocity(-100);
 			intakeL.move_velocity(100);
 			break;
 		}
 	}
 	while(master.get_digital(DIGITAL_L2)) {
 		if(!master.get_digital(DIGITAL_L2)) {
 			intakeR.move_velocity(25);
 			intakeL.move_velocity(-25);
 			break;
 		}
 	}
}

void tilt() { //TODO check absolute positions
  while(master.get_digital(DIGITAL_UP)) {
    if(!master.get_digital(DIGITAL_UP)) {
      flippy.move_absolute(90, 25); //vertical
      break;
    }
  }
  while(master.get_digital(DIGITAL_DOWN)) {
    if(!master.get_digital(DIGITAL_DOWN)) {
      flippy.move_absolute(135, 25); //tilted back
    }
  }
}

void moveArm() { //TODO check absolute positions
  arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  if(master.get_digital(DIGITAL_B)) { //stow position
    arm.move_absolute(-45, 25);
  } else if (master.get_digital(DIGITAL_A)) {
    arm.move_absolute(30, 25);
  } else if (master.get_digital(DIGITAL_X)) {
    arm.move_absolute(60, 25);
  }
}

void checkCurrent(int cur){
	if(master.get_digital_new_press(DIGITAL_R1)){
		torque = true;
		pros::lcd::print(4, "torque");
	}
	if(master.get_digital_new_press(DIGITAL_R2)){
		torque = false;
		pros::lcd::print(4, "speed");
	}
}

void drive(){
  while (true) {
		gL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		gR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

		if(torque){
			sL.move(master.get_analog(ANALOG_LEFT_Y));
			sR.move(master.get_analog(ANALOG_RIGHT_Y));
		} else {
			gL.move(-master.get_analog(ANALOG_LEFT_Y));
			sL.move(-master.get_analog(ANALOG_LEFT_Y));

			gR.move(master.get_analog(ANALOG_RIGHT_Y));
			sR.move(master.get_analog(ANALOG_RIGHT_Y));
		}
  }
}

void opcontrol() {
	moveArm();
}
