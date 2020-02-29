//GMU Verified Code
#include "vex.h"
competition Competition;
#include "Partitions.h"
using namespace std;
using namespace vex;
states States(16, 4); // Robot width, Wheel diameter inserted into the constructor function
void autonomous(void) {
	/* OPTIONS:
	red right
	red left
	blue right
	blue left */
	States.auton("red right");
}
int main() {
	pre_auton();
	Controller1.ButtonUp.pressed(Committeth(16,4).ControllerStack);
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);
	while (true) {
		wait(100,msec);
	}
}
// Interactive Acceleration Emending System