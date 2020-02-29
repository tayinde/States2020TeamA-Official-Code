using namespace vex;
using namespace std;
#include <string>
extern brain Brain;
extern motor leftMotor;
extern motor rightMotor;
extern motor tray2;
extern motor intaker;
extern motor leftLift;
extern motor intakerTwo;
extern motor tray;
extern motor rightLift;
extern controller Controller1;
class Committeth {
public:
	double robotWidth;
	double wheelDiameter;
	double robotTurnAbility;
	double pi = 3.141592653589793238462643383279502884197165399375105;
	Committeth(double RobotWidth, double WheelDiameter) {
		robotWidth = RobotWidth;
		wheelDiameter = WheelDiameter;
		robotTurnAbility = RobotWidth *  pi;
	}
	double inchToRev(double inches) {
		inches /= (pi * wheelDiameter);
		return inches;
	}
	double degTurn(double degrees) {
		return (robotWidth / (360 / degrees)) / (wheelDiameter);
	}
	void forwards(double speed, double revolutions) {
		revolutions = inchToRev(revolutions); // revolutions parameter is inserted as inches but gets converted to revolutions by this function
		leftMotor.setVelocity(speed, pct);
		rightMotor.setVelocity(speed, pct);
		leftMotor.startRotateFor(fwd, revolutions, rev);
		rightMotor.rotateFor(reverse, revolutions, rev, true);
	}
	void backward(double speed, double revolutions) {
		revolutions = inchToRev(revolutions); // revolutions parameter is inserted as inches but gets converted to revolutions by this function
		leftMotor.setVelocity(speed, pct);
		rightMotor.setVelocity(speed, pct);
		leftMotor.startRotateFor(reverse, revolutions, rev);
		rightMotor.rotateFor(fwd, revolutions, rev, true);
	}
	void right(double speed, double degrees) {
		degrees = degTurn(degrees);
		leftMotor.setVelocity(speed, pct);
		rightMotor.setVelocity(speed, pct);
		leftMotor.startRotateFor(fwd, degrees, rev);
		rightMotor.rotateFor(fwd, degrees, rev, true);
	}
	void left(double speed, double degrees) {
		degrees = degTurn(degrees);
		leftMotor.setVelocity(speed, pct);
		rightMotor.setVelocity(speed, pct);
		leftMotor.startRotateFor(reverse, degrees, rev);
		rightMotor.rotateFor(reverse, degrees, rev, true);
	}
	void intake(double speed, string cube, double time) {
		intaker.setVelocity(speed, pct);
		intakerTwo.setVelocity(speed, pct);
		if (cube == "out") { // exporting cube out
			intaker.spin(reverse);
			intakerTwo.spin(fwd);
			wait(time,sec);
			intaker.stop();
			intakerTwo.stop();
		} else if (cube == "in") { // taking cube in
			intaker.spin(fwd);
			intakerTwo.spin(reverse);
			wait(time,sec);
			intaker.stop();
			intakerTwo.stop();
		}
	}
	void lift(double speed, double dir, double degrees) {
		degrees = degTurn(degrees);
		leftLift.setVelocity(speed, pct);
		rightLift.setVelocity(speed, pct);
		if (dir == 1) { // 1 is ascending
			leftLift.startRotateFor(reverse, degrees, rev);
			rightLift.rotateFor(fwd, degrees, rev, true);
			leftLift.setVelocity(0, pct);
		} if (dir == 0) {
			Brain.Screen.print("The lift shall descend.");
			leftLift.startRotateFor(fwd, degrees, rev);
			rightLift.rotateFor(reverse, degrees, rev, true);
		}
	}
	void consumeCubes(double vel, double revolutions) {
		revolutions = inchToRev(revolutions);
		intaker.setVelocity(100,pct);
		intakerTwo.setVelocity(100,pct);
		leftMotor.setVelocity(vel, pct);
		rightMotor.setVelocity(vel,pct);
		intaker.spin(fwd);
		intakerTwo.spin(reverse);
		leftMotor.startRotateFor(fwd, revolutions, rev);
		rightMotor.rotateFor(reverse, revolutions, rev, true);
		intakerTwo.setVelocity(0,pct);
		intakerTwo.setBrake(hold);
	}
	void stopMotors(double time) { 
		// velocity: 0
		intaker.setVelocity(0, pct);
		intakerTwo.setVelocity(0, pct);
		leftMotor.setVelocity(0, pct);
		rightMotor.setVelocity(0, pct);
		tray.setVelocity(0, pct);
		tray2.setVelocity(0, pct);
		rightLift.setVelocity(0, pct);
		leftLift.setVelocity(0, pct);
		intaker.setBrake(hold);
		intakerTwo.setBrake(hold);
		leftMotor.setBrake(hold);
		rightMotor.setBrake(hold);
		tray.setBrake(hold);
		tray2.setBrake(hold);
		rightLift.setBrake(hold);
		leftLift.setBrake(hold);
    	wait(time, sec);
	}
	void stack(double vel) {
		if (!vel) {
			vel = 20;
		}
		tray.setVelocity(vel, pct);
		tray2.setVelocity(vel, pct);
		double degrees = degTurn(99.5) * 4; // This is how much the tray should turn to get to an about 90 degree angle
		tray.startRotateFor(fwd, degrees, rev);
		tray.rotateFor(fwd, degrees, rev, false);
	}
  static void ControllerStack() {
	  double vel = 40;
		tray.setVelocity(vel, pct);
		tray2.setVelocity(vel, pct);
		double degrees = Committeth(16, 4).degTurn(1485); // This is how much the tray should turn to get to an about 90 degree angle
		tray.startRotateFor(reverse, degrees, rev);
		tray2.rotateFor(reverse, degrees, rev);
	}
	static void Tower() {
		Committeth(16, 4).backward(30, 5);
		Committeth(16, 4).lift(81.5, 1, 70);
		Committeth(16, 4).forwards(70, 3);
		Committeth(16, 4).intake(100, "out", 0.7);
		Committeth(16, 4).backward(100, 5);
		Committeth(16, 4).lift(30, 0, 65);
	}
};
void vexcodeInit(void);