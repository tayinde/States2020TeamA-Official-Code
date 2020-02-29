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
class states {
public:
	double robotWidth;
	double wheelDiameter;
	double robotTurnAbility;
	double pi = 3.1415926535897932384626433832795;
	states(double RobotWidth, double WheelDiameter) { // states initialization
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
	}
	void stopMotors(double time) { 
		// velocity: 0
		leftMotor.setVelocity(0, pct);
		rightMotor.setVelocity(0, pct);
		tray.setVelocity(0, pct);
		tray2.setVelocity(0, pct);
		rightLift.setVelocity(0, pct);
		leftLift.setVelocity(0, pct);
		leftMotor.setBrake(hold);
		rightMotor.setBrake(hold);
		tray.setBrake(hold);
		tray2.setBrake(hold);
		rightLift.setBrake(hold);
		leftLift.setBrake(hold);
    	wait(time, sec);
	}
  // 1830, -1255
	void stack(double vel) {
		tray.setVelocity(vel, pct);
		tray2.setVelocity(vel, pct);
		double degrees = degTurn(1490); // This is how much the tray should turn to get to an about 90 degree angle
		tray.startRotateFor(reverse, degrees, rev);
		tray2.rotateFor(reverse, degrees, rev, true);
    	wait(0.3,sec);
		leftMotor.spin(fwd);
		rightMotor.spin(reverse);
    	wait(0.6, sec);
      this -> forwards(100, 0.9);
 		tray.startRotateFor(fwd, degrees, rev);
		tray2.rotateFor(fwd, degrees, rev, true);
    this -> intake(100, "out", 0.2);
		this -> backward(50, 6.5);
	}
	void stop(motor Example) {
		Example.setVelocity(0, pct);
		Example.setBrake(hold);
	}
	void placeCube(string scoring) {
		if (scoring == "tower") {
			this -> backward(30, 5);
			this -> lift(81.5, 1, 70);
			this -> forwards(70, 3);
			this -> intake(100, "out", 0.7);
			this -> backward(100, 10);
			this -> lift(30, 0, 65);
		} else if (scoring == "goal" || scoring == "goalzone") {
			this -> stack(86); // Stacks cubes with 40% velocity
		}
	}
	void flipTray() {
		tray.spin(reverse, 100, pct);
		tray2.spin(reverse, 100, pct);
		wait(0.4, sec);
		tray.spin(fwd, 100, pct);
		tray2.spin(fwd, 100, pct);
		wait(0.9, sec);
    this -> stopMotors(0.1);
	}
	void intakeSpeed(double vel) {
		intaker.setVelocity(vel, pct);
		intakerTwo.setVelocity(vel, pct);
	}
	void auton(string team) {
		if (team == "blue left") {
			Controller1.Screen.print("please work auton");
			this -> intake(100, "in", 1);
			this -> consumeCubes(45, 48);
			this -> intakeSpeed(0);
			this -> stopMotors(0.2); // 0.2 seconds to give motors time to adjust
      this -> intake(100, "in", 0.5);
			this -> backward(50, 20);
			this -> left(50, 123.8);
      this -> intake(100, "in", 0.2);
			this -> forwards(40, 12.5);
			this -> stopMotors(0.5);
			this -> intake(100, "in", 0.3);
			this -> placeCube("goalzone"); // Essentially just the stacking system with other parts
		}	
		if (team == "red right") {
			Controller1.Screen.print("please work auton");
      this -> intake(100, "in", 1);
			this -> consumeCubes(45, 48);
			this -> intakeSpeed(0);
			this -> stopMotors(0.2); // 0.2 seconds to give motors time to adjust
      this -> intake(100, "in", 0.5);
			this -> backward(50, 20);
			this -> right(50, 123.8);
      this -> intake(100, "in", 0.2);
			this -> forwards(40, 12.5);
			this -> stopMotors(0.5);
			this -> intake(100, "in", 0.3);
			this -> placeCube("goalzone"); // Essentially just the stacking system with other parts
		}
		if (team == "blue right") {
			Controller1.Screen.print("um...");
			this -> flipTray();
			this -> consumeCubes(50, 15);
			this -> right(50, 90);
			this -> consumeCubes(50, 10);
			this -> right(50, 48);
			this -> intake(100,"out",0.165);
			this -> forwards(100, 3);
			this -> placeCube("goalzone");
		}
		if (team == "red left") {
			Controller1.Screen.print("uhhh..");
			this -> flipTray();
			this -> consumeCubes(50, 15);
			this -> intakeSpeed(0);
			this -> left(50, 90);
			this -> consumeCubes(50, 10);
			this -> left(50, 48);
			this -> forwards(100, 3);
			this -> intakeSpeed(100);
			this -> intake(100,"out",0.165);
			this -> placeCube("goalzone");
		}
		if (team == "skills") {
			Controller1.Screen.print("please work auton");
			this -> flipTray();
			this -> consumeCubes(40, 43.6);
			this -> intakeSpeed(30);
			this -> stopMotors(0.2); // 0.2 seconds to give motors time to adjust
			this -> backward(50, 20);
			this -> right(50, 119);
			this -> forwards(40, 11.64);
			this -> stopMotors(0.5);
			this -> intakeSpeed(100);
      		this -> intake(100,"out",0.14);
			this -> placeCube("goalzone"); // Essentially just the stacking system with other parts
		}
		if (team == "test") {
			this -> stack(40);
		}
	}
};
void vexcodeInit(void);