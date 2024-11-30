#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

int drive_control = 0;
int auto_pro = 0;

pros::MotorGroup left_mg({-11, 12});    // Creates a motor group with motors connected to ports 11 and 12
pros::MotorGroup right_mg({-19, 20});   // Creates a motor group with motors connected to ports 19 and 20
pros::Motor intake(10);                  // Creates a motor connected to port 9
pros::Motor roller(9);                 // Creates a motor connected to port 10
pros::ADIDigitalOut claw('H');          // Creates a digital output connected to port H

void on_left_button() {
	if (drive_control == 1) {
		pros::lcd::set_text(1, "Kiwi");
		drive_control = 0;
	}
	else if (drive_control == 0) {
		pros::lcd::set_text(1, "Henry");
		drive_control = 1;
	}
}

void on_right_button() {
	if (auto_pro == 0) {
		pros::lcd::set_text(2, "Blue Left");
		auto_pro = 1;
	}
	else if (auto_pro == 1) {
		pros::lcd::set_text(2, "Blue Right");
		auto_pro = 2;
	}
	else if (auto_pro == 2) {
		pros::lcd::set_text(2, "Red Left");
		auto_pro = 3;
	}
	else if (auto_pro == 3) {
		pros::lcd::set_text(2, "Red Right");
		auto_pro = 0;
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, "Select Program:");
	// pros::lcd::set_text(2, "1. Program 1");
	// pros::lcd::set_text(3, "2. Program 2");
	pros::lcd::register_btn0_cb(on_left_button);
	// pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn2_cb(on_right_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//write your autonomous code here
}

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
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	int dir;
	int turn;
	int strafe;
	while (true) {
		// Arcade control scheme
		switch (drive_control)
		{
		case 0: //Kiwi
			dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
			turn = master.get_analog(ANALOG_LEFT_X);   // Gets the turn left/right from left joystick
			strafe = master.get_analog(ANALOG_RIGHT_X); // Gets the strafe forward/backward from right joystick
			left_mg.move(dir + turn + strafe);         // Sets left motor voltage
			right_mg.move(dir - turn + strafe);        // Sets right motor voltage
			break;
		case 1: //Henry
			dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
			turn = master.get_analog(ANALOG_LEFT_X);   // Gets the turn left/right from left joystick
			left_mg.move(dir + turn);                  // Sets left motor voltage
			right_mg.move(dir - turn);                 // Sets right motor voltage
			break;
		default:
			dir = 0;                                   // Default forward/backward value
			turn = 0;                                  // Default turn value
			left_mg.move(dir + turn);                  // Sets left motor voltage
			right_mg.move(dir - turn);                 // Sets right motor voltage
			break;
		}

		// Intake and Roller control
		if (master.get_digital(DIGITAL_R2)) {
			intake.move(90); // Move intake forward
			roller.move(127); // Move roller forward
		} else if (master.get_digital(DIGITAL_R1)) {
			intake.move(-90); // Move intake backward
			roller.move(-127); // Move roller backward
		} else {
			intake.move(0); // Stop intake
			roller.move(0); // Stop roller
		}

		// Claw control
		if (master.get_digital(DIGITAL_L1)) {
			claw.set_value(true); // Open claw
		} else if (master.get_digital(DIGITAL_L2)) {
			claw.set_value(false); // Close claw
		}

		pros::delay(20);                               // Run for 20 ms then update
	}
}
