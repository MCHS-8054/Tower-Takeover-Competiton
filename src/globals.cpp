#include "main.h"

using namespace pros;



Controller master(CONTROLLER_MASTER);

// auto driveR = master.get_analog(ANALOG_RIGHT_Y);
// auto driveL = master.get_analog(ANALOG_LEFT_Y);
//
// auto intake = master.get_digital(DIGITAL_R1);
// auto outtake = master.get_digital(DIGITAL_R2);
// auto tiltUp = master.get_digital(DIGITAL_L1);
// auto tiltBack = master.get_digital(DIGITAL_L2);

Motor gR(1);
Motor sR(2);
Motor gL(11);
Motor sL(12);

Motor intakeR(3);
Motor intakeL(13);

Motor flippyR(4, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
Motor flippyL(14, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

bool tiltUp = master.get_digital_new_press(DIGITAL_UP);
bool tiltDown = master.get_digital_new_press(DIGITAL_DOWN);

float vertAngle = 615;
