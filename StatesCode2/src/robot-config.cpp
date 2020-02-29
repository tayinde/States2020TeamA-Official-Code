#include "vex.h"
using namespace vex;
using namespace std;
using signature = vision::signature;
using code = vision::code;
brain  Brain;
/* BURNED OUT:
4
7
20
*/
motor leftMotor /* 2 */ = motor(PORT2, ratio18_1, false);
motor rightMotor /* 5 */ = motor(PORT5, ratio18_1, false);
motor tray2 /* 19 */ = motor(PORT19, ratio6_1, true); // HIGH STRENGTH
motor tray /* 18 */ = motor(PORT11, ratio6_1, false); // HIGH STRENGTH
motor intaker /* 1 */ = motor(PORT1, ratio18_1, false);
motor intakerTwo /* 6 */ = motor(PORT6, ratio18_1, false);
motor leftLift /* 11 */ = motor(PORT18, ratio18_1, false);
motor rightLift /* 12 */ = motor(PORT12, ratio18_1, false);
controller Controller1 = controller(primary);
void vexcodeInit( void ) {}