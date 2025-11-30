/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       geoso                                                     */
/*    Created:      8/17/2025, 10:03:42 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller1;
motor leftfront(PORT2, ratio6_1, true);
motor leftrear(PORT3, ratio6_1, true);
motor leftrear_stacked(PORT1, ratio6_1, false);
motor rightfront(PORT9, ratio6_1, true);
motor rightrear(PORT8, ratio6_1, true);
motor rightrear_stacked(PORT10, ratio6_1, false);
inertial inertialsensor = inertial(PORT4);
vision aiVision = vision(PORT11);
motor_group left_drive = motor_group(leftfront, leftrear, leftrear_stacked);
motor_group right_drive = motor_group(rightfront, rightrear, rightrear_stacked);
motor intake_bottom_front(PORT19, ratio18_1, true);
motor intake_rear_bottom(PORT21, ratio18_1, false);
motor intake_front_right(PORT20, ratio18_1, false);
motor_group intake = motor_group(intake_bottom_front, intake_rear_bottom, intake_front_right);
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  // toggles for intake
  bool r1Toggle = false;
  bool r2Toggle = false;
  bool lastR1 = false;
  bool lastR2 = false;

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    // Drive control
    left_drive.spin(forward, Controller1.Axis3.position(percent), percent);
    right_drive.spin(reverse, Controller1.Axis2.position(percent), percent);
    // read current R button states and handle toggle on press edge
    bool curR1 = Controller1.ButtonR1.pressing();
    bool curR2 = Controller1.ButtonR2.pressing();
    if (curR1 && !lastR1) {
      // toggle R1 mode; turning one on turns the other off
      r1Toggle = !r1Toggle;
      if (r1Toggle) r2Toggle = false;
    }
    if (curR2 && !lastR2) {
      r2Toggle = !r2Toggle;
      if (r2Toggle) r1Toggle = false;
    }
    lastR1 = curR1;
    lastR2 = curR2;

    // Middle-goal control (L1/L2): spin bottom and front-right opposite each other.
    // Priority: middle-goal (L) overrides tall-goal (R).
    if (Controller1.ButtonL1.pressing()) {
    // L1: middle intake — switched directions: bottom front runs reverse,
    // front right runs forward
  intake_bottom_front.spin(reverse, 100, percent);
    intake_front_right.spin(forward, 100, percent);
    intake_rear_bottom.spin(forward, 100, percent);
  } else if (Controller1.ButtonL2.pressing()) {
    // L2: middle outtake (reverse of L1) — switched directions
  intake_bottom_front.spin(forward, 100, percent);
    intake_front_right.spin(reverse, 100, percent);
    intake_rear_bottom.spin(reverse, 100, percent);
    } else if (r1Toggle) {
      // Tall-goal intake toggled on
      intake.spin(forward, 100, percent);
    } else if (r2Toggle) {
      // Tall-goal outtake toggled on
      intake.spin(reverse, 100, percent);
  } else {
    // Stop all intake motors when no buttons are pressed
    intake.stop();
    intake_bottom_front.stop();
    intake_front_right.stop();
    intake_rear_bottom.stop();
  }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
