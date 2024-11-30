# VEX Robotics Project

## Introduction

This project is a VEX Robotics control program written in C++. It uses the PROS (Purdue Robotics Operating System) library to manage the robot's motors, sensors, and controller inputs. The code is designed to handle both autonomous and operator control modes, with an LCD interface for selecting programs.

## Features

**Motor Control:** Controls the left and right motor groups, roller, and intake motors.

**LCD Interface:** Allows the user to select different autonomous routines and switch driver modes using the LCD buttons.

**Autonomous Modes:** Includes multiple autonomous routines selectable through the LCD.

**Operator Control:** Supports multiple control schemes for different drivers.

## Code Overview

### Main Components


**Motor Groups:** Defined for left and right drive motors.

**LCD Callbacks:** Functions for handling button presses on the LCD.

**Initialization:** Sets up the LCD and registers button callbacks.

**Autonomous:** Selects and runs the appropriate autonomous routine based on the user selection.

**Operator Control:** Runs the main control loop, allowing the user to control the robot during the match.

### Key Functions:
```cpp
void on_left_button();
void on_right_button();
void initialize();
void disabled();
void competition_initialize();
void autonomous();
void opcontrol();
```
### Example Code

Here is a snippet of the code:
```cpp
MotorGroup left_mg({-11, 12});
MotorGroup right_mg({-19, 20});
Motor roller(9);
Motor intake(10);
ADIDigitalOut clamp('H');

void on_left_button() {
    if (drive_control == 1) {
        lcd::set_text(1, "Driver: Kiwi");
        drive_control = 0;
    } else if (drive_control == 0) {
        lcd::set_text(1, "Driver: Henry");
        drive_control = 1;
    }
}

void on_right_button() {
    if (auto_pro == 3) {
        lcd::set_text(2, "Run: Blue Left");
        auto_pro = 0;
    } else if (auto_pro == 0) {
        lcd::set_text(2, "Run: Blue Right");
        auto_pro = 1;
    } else if (auto_pro == 1) {
        lcd::set_text(2, "Run: Red Left");
        auto_pro = 2;
    } else if (auto_pro == 2) {
        lcd::set_text(2, "Run: Red Right");
        auto_pro = 3;
    }
}

void initialize() {
    lcd::initialize();
    lcd::set_text(0, "Select Program:");
    lcd::register_btn0_cb(on_left_button);
    lcd::register_btn2_cb(on_right_button);
}

void autonomous() {
    switch (auto_pro) {
        case 0:
            lcd::set_text(3, "Running auton: Blue Left");
            break;
        case 1:
            lcd::set_text(3, "Running auton: Blue Right");
            break;
        case 2:
            lcd::set_text(3, "Running auton: Red Left");
            break;
        case 3:
            lcd::set_text(3, "Running auton: Red Right");
            break;
        default:
            lcd::set_text(3, "Running auton: Default");
            break;
    }
}
```

### Usage

**Initialization:** Set up the motors, sensors, and LCD interface.

**Autonomous Mode:** Select and run an autonomous routine using the LCD buttons.

**Operator Control:** Use the controller to manually drive the robot and operate mechanisms.

## Contributing

Feel free to contribute to this project by submitting issues or pull requests. Your contributions are highly appreciated!

## License

[PROS 1](https://github.com/S123MR/Pros-1) © 2024 by [S123MR](https://github.com/S123MR) is licensed under [CC BY-NC-ND 4.0](https://creativecommons.org/licenses/by-nc-nd/4.0/?ref=chooser-v1)
