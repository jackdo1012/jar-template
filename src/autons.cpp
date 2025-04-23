#include "vex.h"

void default_constants()
{
    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_drive_constants(12, 8.5, 0, 15, 0);
    chassis.set_heading_constants(7, 6, 0, 13, 0);
    chassis.set_turn_constants(12, 5.5, .05, 35, 15);
    chassis.set_swing_constants(12, 4.5, 0, 45, 15);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1, 300, 5000);
    chassis.set_turn_exit_conditions(1, 300, 3000);
    chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_test()
{
    chassis.set_coordinates(0, 0, 0);
    while (1)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(5, 20, "X: %f", chassis.get_X_position());
        Brain.Screen.printAt(5, 40, "Y: %f", chassis.get_Y_position());
        Brain.Screen.printAt(5, 60, "Heading: %f", chassis.get_absolute_heading());
        Brain.Screen.printAt(5, 80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
        Brain.Screen.printAt(5, 100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
        task::sleep(20);
    }
}

void baker_blue()
{
}

void baker_red()
{
}

void ring_rush_blue()
{
}

void ring_rush_red()
{
}

void solo_awp()
{
}