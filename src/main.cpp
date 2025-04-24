#include "vex.h"

using namespace vex;
competition Competition;

Drive chassis(PORT14, 2.75, 1, 360, PORT10, -PORT8, -PORT15, -PORT11, PORT16, PORT9, PORT12, 2.75, -0.5, PORT13, -2.75,
              1.83);

// ----------------------
// |      Intake        |
// ----------------------

int intakeState = 0;

void runIntake()
{
    if (intakeState != 1)
    {
        intMot.spin(vex::forward, 12, vex::volt);
        intakeState = 1;
    }
    else
    {
        intMot.stop();
        intakeState = 0;
    }
}

void reverseIntake()
{
    if (intakeState != -1)
    {
        intMot.spin(vex::reverse, 12, vex::volt);
        intakeState = -1;
    }
    else
    {
        intMot.stop();
        intakeState = 0;
    }
}

// ----------------------
// |        Arm         |
// ----------------------
float armPos[] = {0, 85.5, 420};
int numOfArmPos = sizeof(armPos) / sizeof(armPos[0]);
int armState = 0;
float armTarget = 0;
float armPrevErr = 0;
bool autoArm = true;

void armMode()
{
    autoArm = !autoArm;
    if (autoArm)
    {
        armState = 0;
        armTarget = armPos[armState];
    }
}

int armControlTask()
{
    while (1)
    {
        float kP = .5;
        float kD = 0;
        float err = armTarget - (arm1Mot.position(vex::rotationUnits::rev) * 360);
        float output = kP * err + kD * (err - armPrevErr);
        armPrevErr = err;
        output = clamp(-100, output, 100);
        if (autoArm)
        {
            arm1Mot.spin(vex::forward, output, vex::percent);
            arm2Mot.spin(vex::forward, output, vex::percent);
        }
        task::sleep(10);
    }
    return 0;
}

void armUp()
{
    if (autoArm)
    {
        if (armState < numOfArmPos - 1)
        {
            armState++;
            armTarget = armPos[armState];
        }
    }
    else
    {
        arm1Mot.spin(vex::forward, 100, vex::percent);
        arm2Mot.spin(vex::forward, 100, vex::percent);
    }
}

void armDown()
{
    if (autoArm)
    {
        if (armState > 0)
        {
            armState--;
            armTarget = armPos[armState];
        }
    }
    else
    {
        arm1Mot.spin(vex::reverse, 100, vex::percent);
        arm2Mot.spin(vex::reverse, 100, vex::percent);
    }
}

void armReleased()
{
    if (!autoArm)
    {
        arm1Mot.stop(vex::hold);
        arm2Mot.stop(vex::hold);
    }
}

// ----------------------
// |       Clamp        |
// ----------------------

bool clampState = false;
void clamp()
{
    clampState = !clampState;
    clampPis = clampState;
}

// ----------------------
// |      Doinker       |
// ----------------------

bool lDoinkerState = false;
bool rDoinkerState = false;
void lDoinker()
{
    lDoinkerState = !lDoinkerState;
    lDoinkerPis = lDoinkerState;
}
void rDoinker()
{
    rDoinkerState = !rDoinkerState;
    rDoinkerPis = rDoinkerState;
}

// ----------------------
// |      Main Task     |
// ----------------------

void placeholder()
{
}

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton()
{
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();
    default_constants();

    wait(100, msec);

    task armTask(armControlTask);

    // while (!auto_started)
    // {
    //     Brain.Screen.clearScreen();
    //     Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
    //     Brain.Screen.printAt(5, 40, "Battery Percentage:");
    //     Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    //     Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
    //     Brain.Screen.printAt(5, 100, "%f", chassis.get_absolute_heading());
    //     Brain.Screen.printAt(5, 120, "Selected Auton:");
    //     switch (current_auton_selection)
    //     {
    //         case 0:
    //             Brain.Screen.printAt(5, 140, "Baker Blue");
    //             break;
    //         case 1:
    //             Brain.Screen.printAt(5, 140, "Baker Red");
    //             break;
    //         case 2:
    //             Brain.Screen.printAt(5, 140, "Ring Rush Blue");
    //             break;
    //         case 3:
    //             Brain.Screen.printAt(5, 140, "Ring Rush Red");
    //             break;
    //         case 4:
    //             Brain.Screen.printAt(5, 140, "Solo AWP");
    //             break;
    //     }
    //     if (Brain.Screen.pressing())
    //     {
    //         while (Brain.Screen.pressing())
    //         {
    //         }
    //         current_auton_selection++;
    //     }
    //     else if (current_auton_selection == 5)
    //     {
    //         current_auton_selection = 0;
    //     }
    //     task::sleep(10);
    // }
}

void autonomous(void)
{
    auto_started = true;
    switch (current_auton_selection)
    {
        case 0:
            baker_blue();
            break;
        case 1:
            baker_red();
            break;
        case 2:
            ring_rush_blue();
            break;
        case 3:
            ring_rush_red();
            break;
        case 4:
            solo_awp();
            break;
    }
}
void usercontrol(void)
{
    Controller.ButtonL1.pressed(runIntake);
    Controller.ButtonL2.pressed(reverseIntake);
    Controller.ButtonR1.pressed(armUp);
    Controller.ButtonR2.pressed(armDown);
    Controller.ButtonR1.released(armReleased);
    Controller.ButtonR2.released(armReleased);
    Controller.ButtonA.pressed(clamp);
    Controller.ButtonLeft.pressed(lDoinker);
    Controller.ButtonRight.pressed(rDoinker);
    Controller.ButtonX.pressed(armMode);

    while (1)
    {
        chassis.control_arcade();

        wait(20, msec);
    }
}

int main()
{
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    pre_auton();

    while (true)
    {
        wait(100, msec);
    }
}
