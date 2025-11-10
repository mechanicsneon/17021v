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
motor_group left_drive = motor_group(leftfront, leftrear, leftrear_stacked);
motor_group right_drive = motor_group(rightfront, rightrear, rightrear_stacked);
motor intake_rear_top(PORT19, ratio18_1, false);
motor intake_rear_bottom(PORT21, ratio18_1, false);
motor intake_front_left(PORT11, ratio18_1, false);
motor intake_front_right(PORT20, ratio18_1, false);
motor_group intake = motor_group(intake_rear_top, intake_rear_bottom, intake_front_left, intake_front_right);
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
    // High goal intake control
    intake_front_left.spin(reverse, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    intake_front_right.spin(forward, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    intake_rear_bottom.spin(forward, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    intake_rear_top.spin(reverse, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    // Low goal intake control and outtake controls
    intake_front_left.spin(forward, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    intake_front_right.spin(reverse, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    intake_rear_bottom.spin(reverse, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    intake_rear_top.spin(forward, Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing() * 100, percent);
    // Middle goal intake control
    intake_front_left.spin(reverse, Controller1.ButtonL1.pressing() - Controller1.ButtonL2.pressing() * 100, percent);
    intake_front_right.spin(forward, Controller1.ButtonL1.pressing() - Controller1.ButtonL2.pressing() * 100, percent);
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
