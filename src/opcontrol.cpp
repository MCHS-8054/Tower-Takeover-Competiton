#include "main.h"
#include "globals.hpp"

bool torque = false;

bool intakePressed = false;
bool outtakePressed = false;
bool seqOut = false;

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

void stopMotors(Motorgroup group) {
  switch(group) {
    case DRIVE:
      sprockL.move(0);
      sprockR.move(0);
      gearL.move(0);
      gearR.move(0);
      break;
    case TILTER:
      flippyL.move(0);
      flippyR.move(0);
    case INTAKE:
      intakeL.move(0);
      intakeR.move(0);
  }
}

void drive(bool slow = false){
 	gearL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
 	gearR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

   if(slow) {
     sprockL.move(-30);
     sprockR.move(-30);
     gearL.move(-30);
     gearR.move(-30);
     delay(2000);
     stopMotors(DRIVE);
   }
   else {
   	if(torque) {
   		sprockL.move(master.get_analog(ANALOG_LEFT_Y));
   		sprockR.move(master.get_analog(ANALOG_RIGHT_Y));
   	} else {
   		gearL.move(-master.get_analog(ANALOG_LEFT_Y));
   		sprockL.move(-master.get_analog(ANALOG_LEFT_Y));

   		gearR.move(master.get_analog(ANALOG_RIGHT_Y));
   		sprockR.move(master.get_analog(ANALOG_RIGHT_Y));
   	}
   }
 }

 double ticksToDeg(double ticks) {
   return (ticks/1800)*360;
 }

 double degToTicks(double deg) {
   return (deg/360)*1800;
 }

 void in_n_out() {
	if(master.get_digital_new_press(DIGITAL_R1)) {
    outtakePressed = false;
    if(!intakePressed) {
 			intakeR.move_velocity(-100);
 			intakeL.move_velocity(100);
    } else {
      stopMotors(INTAKE);
    }
    intakePressed = !intakePressed;
 	}
 	else if(master.get_digital_new_press(DIGITAL_R2)) {
    intakePressed = false;
    if(!outtakePressed) {
    	intakeR.move_velocity(50);
 			intakeL.move_velocity(-50);
    } else {
      stopMotors(INTAKE);
    }
    outtakePressed = !outtakePressed;
 	}
}

void tilt() { //TODO check absolute positions
  if(master.get_digital(DIGITAL_UP)) {
    while(flippyL.get_position()<(vertAngle-5)){
      flippyR.move_absolute(vertAngle, 50); //vertical
      flippyL.move_absolute(vertAngle, 50); //vertical
    }
    intakeR.move_velocity(50);
    intakeL.move_velocity(-50);
  }
  if(master.get_digital(DIGITAL_DOWN)) {
    flippyR.move_absolute(0, 50); //tilted back
    flippyL.move_absolute(0, 50); //tilted back
    stopMotors(INTAKE);
  }
}

void outtakeSequence() {
  if(master.get_digital_new_press(DIGITAL_RIGHT)) {
    while(flippyL.get_position()<(vertAngle-5)) {
      flippyR.move_absolute(vertAngle, 50); //vertical
      flippyL.move_absolute(vertAngle, 50); //vertical
    }
    intakeR.move_velocity(50);
    intakeL.move_velocity(-50);
    delay(250);
    drive(true);
    flippyR.move_absolute(vertAngle-30, 50);
    flippyL.move_absolute(vertAngle-30, 50);
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
	if(master.get_digital_new_press(DIGITAL_L1)){
		torque = true;
		pros::lcd::print(1, "Drive mode: torque");
	}
	if(master.get_digital_new_press(DIGITAL_L2)){
		torque = false;
		pros::lcd::print(1, "Drive mode: speed");
	}
}

void opcontrol() {
  //pros::lcd::initialize();
  while(true) {
    //moveArm();
    tilt();
    in_n_out();
    drive();
    //outtakeSequence();
    pros::lcd::print(2, "Tilter angle: %f", flippyR.get_position()/7);
    delay(20);
    //pros::lcd::print(3, "Intake status: %f", (intakeR.get_actual_velocity() > 0) - (intakeR.get_actual_velocity() < 0));
  }
}
