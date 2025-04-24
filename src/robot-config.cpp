#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;
controller Controller;

vex::motor intMot = vex::motor(vex::PORT17, false);
vex::motor arm1Mot = vex::motor(vex::PORT18, true);
vex::motor arm2Mot = vex::motor(vex::PORT19, false);

vex::digital_out clampPis = vex::digital_out(Brain.ThreeWirePort.A);
vex::digital_out lDoinkerPis = vex::digital_out(Brain.ThreeWirePort.B);
vex::digital_out rDoinkerPis = vex::digital_out(Brain.ThreeWirePort.C);
vex::digital_out ptoPis = vex::digital_out(Brain.ThreeWirePort.D);
vex::digital_out intLiftPis = vex::digital_out(Brain.ThreeWirePort.E);

vision colorSensor = vision(PORT6);
vex::inertial Inertial = vex::inertial(vex::PORT14);

vex::motor l1Mot = vex::motor(vex::PORT10, false);
vex::motor l2Mot = vex::motor(vex::PORT8, true);
vex::motor l3Mot = vex::motor(vex::PORT15, true);
vex::motor r1Mot = vex::motor(vex::PORT11, true);
vex::motor r2Mot = vex::motor(vex::PORT16, false);
vex::motor r3Mot = vex::motor(vex::PORT9, false);

void vexcodeInit(void)
{
    // nothing to initialize
}