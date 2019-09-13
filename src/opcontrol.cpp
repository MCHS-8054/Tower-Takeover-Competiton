#include "main.h"
#include "globals.hpp"

bool torque = false;

bool intakePressed = false;
bool outtakePressed = false;

using namespace pros;
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

 double ticksToDeg(double ticks) {
   return (ticks/900)*360;
 }

 double degToTicks(double deg) {
   return (deg/360)*900;
 }

 void in_n_out() {
	if(master.get_digital_new_press(DIGITAL_L1)) {
    if(!intakePressed) {
 			intakeR.move_velocity(-100);
 			intakeL.move_velocity(100);
    } else {
      intakeR.move_velocity(0);
      intakeL.move_velocity(0);
    }
    intakePressed = !intakePressed;
 	}
 	else if(master.get_digital_new_press(DIGITAL_L2)) {
    if(!outtakePressed) {
    	intakeR.move_velocity(100);
 			intakeL.move_velocity(-100);
    } else {
      intakeR.move_velocity(0);
      intakeL.move_velocity(0);
    }
    outtakePressed = !outtakePressed;
 	}
}

void tilt() { //TODO check absolute positions
  if(master.get_digital(DIGITAL_UP)) {
    flippyR.move_absolute(degToTicks(90), 100); //vertical
    flippyL.move_absolute(degToTicks(90), 100); //vertical
  }
  if(master.get_digital(DIGITAL_DOWN)) {
    flippyR.move_absolute(degToTicks(135), 100); //tilted back
    flippyL.move_absolute(degToTicks(135), 100); //tilted back
  }
}

/*
void moveArm() { //TODO check absolute positions
  arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  if(master.get_digital(DIGITAL_B)) { //stow position
    arm.move_absolute(degToTicks(0), 100);
  } else if (master.get_digital(DIGITAL_A)) {
    arm.move_absolute(degToTicks(60), 100);
  } else if (master.get_digital(DIGITAL_X)) {
    arm.move_absolute(degToTicks(90), 100);
  }
}*/

void checkCurrent(int cur){
	if(master.get_digital_new_press(DIGITAL_R1)){
		torque = true;
		pros::lcd::print(1, "Drive mode: torque");
	}
	if(master.get_digital_new_press(DIGITAL_R2)){
		torque = false;
		pros::lcd::print(1, "Drive mode: speed");
	}
}

void drive(){
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

void opcontrol() {
  //pros::lcd::initialize();
  while(true) {
    //moveArm();
    tilt();
    in_n_out();
    drive();
    delay(20);
    pros::lcd::print(2, "Tilter angle: %f", flippyR.get_position());
    pros::lcd::print(3, "Intake status: %f", (intakeR.get_actual_velocity() > 0) - (intakeR.get_actual_velocity() < 0));
  }
}
