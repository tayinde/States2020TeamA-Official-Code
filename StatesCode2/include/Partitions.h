using namespace vex;
using namespace std;
#include "ControllerAlternate.h"
extern brain Brain;
extern motor leftMotor;
extern motor rightMotor;
extern motor tray2;
extern motor intaker;
extern motor intakerTwo;
extern motor tray;
extern motor leftLift;
extern motor rightLift;
extern controller Controller1;
void usercontrol(void) {
		leftMotor.setVelocity(100, pct);
		rightMotor.setVelocity(100, pct);
		tray.setVelocity(20, pct);
		tray2.setVelocity(20, pct);
		leftLift.setVelocity(100, pct);
		rightLift.setVelocity(100, pct);
		double trayStartingPosition = tray.rotation(deg);
		double trayLimit = trayStartingPosition + 1480;
		double allow = true;
		double Left;
		double Right;
		double setBackVelocity;
    	int IAES = false;
		while (1) {
			// Interactive Acceleration Emending System
			Left = -(Controller1.Axis3.value());
			Right = (Controller1.Axis2.value());
			if (((Right + Left) >= 180) && (IAES == true)) {
				if (setBackVelocity <= 90) {
					setBackVelocity += 1;
				} else {
					setBackVelocity = 70;
				}
				Right = setBackVelocity;
       			Left = setBackVelocity;
				leftMotor.spin(reverse, Left, pct); //(Axis3+Axis4)/2;
				rightMotor.spin(reverse, Right, pct);//(Axis3-Axis4)/2;
			} else {
				leftMotor.spin(reverse, Left, pct); //(Axis3+Axis4)/2;
				rightMotor.spin(reverse, Right, pct);//(Axis3-Axis4)/2;
			}
		if (Controller1.ButtonR2.pressing()) { // out
			intakerTwo.setVelocity(100, pct);
			intaker.setVelocity(100, pct);
			intaker.spin(fwd);
			intakerTwo.spin(reverse);
		} else if (Controller1.ButtonR1.pressing()) {
			intaker.setVelocity(65, pct);
			intakerTwo.setVelocity(65, pct);
			intaker.spin(reverse);
			intakerTwo.spin(fwd);
		} else if (!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()) {
			intaker.setVelocity(0, pct);
			intakerTwo.setVelocity(0, pct);
			intakerTwo.setBrake(hold);
			intaker.setBrake(hold);
		}
		//--------------------------Lift controller code---------------------
		if (Controller1.ButtonB.pressing()) { 
      // Down
			leftLift.setVelocity(100,pct);
			rightLift.setVelocity(100,pct);
			leftLift.spin(reverse);
			rightLift.spin(fwd);
		} else if (Controller1.ButtonX.pressing()) { // Up
			leftLift.setVelocity(100, pct);
			rightLift.setVelocity(100, pct);
			leftLift.startRotateFor(fwd, 50, deg);
			rightLift.rotateFor(reverse, 50,  deg, false);
		} else if (!Controller1.ButtonX.pressing() && !Controller1.ButtonB.pressing()) {
			leftLift.setVelocity(0, pct);
			rightLift.setVelocity(0, pct);
			leftLift.setBrake(hold); // stay in place with hold
			rightLift.setBrake(hold);
		}
		if (Controller1.ButtonL2.pressing()) {
			tray.setVelocity(40, pct);
			tray2.setVelocity(40, pct);
			tray.spin(reverse);
			tray2.spin(reverse);
		} else if (Controller1.ButtonL1.pressing()) {
			tray.setVelocity(40, pct);
			tray2.setVelocity(40, pct);
			tray.spin(fwd); // Tray should move slowly
			tray2.spin(fwd); // Tray should move slowly
		} else if (!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing()) {
			tray.setVelocity(0, pct);
			tray2.setVelocity(0, pct);
			tray.setBrake(hold);
			tray2.setBrake(hold);
		}
		if (tray.rotation(deg) >= trayLimit) {
			allow = false;
		}
		wait(20, msec);
	}
}
void pre_auton() {} // Nothing needs to happen here