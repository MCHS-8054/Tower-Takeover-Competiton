#include "main.h"

using namespace pros;

extern Controller master;

// extern auto driveR;
// extern auto driveL;
//
// extern auto intake;
// extern auto outtake;
// extern auto tiltUp;
// extern auto tiltBack;

extern Motor gearR;
extern Motor sprockR;
extern Motor gearL;
extern Motor sprockL;

extern Motor intakeR;
extern Motor intakeL;

extern Motor flippyR;
extern Motor flippyL;

extern bool tiltUp;
extern bool tiltDown;


extern float vertAngle;

enum Motorgroup {DRIVE, TILTER, INTAKE};
