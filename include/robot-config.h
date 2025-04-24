using namespace vex;

extern brain Brain;
extern controller Controller;

// Add your devices below, and don't forget to do the same in robot-config.cpp:
extern vex::motor intMot;
extern vex::motor arm1Mot;
extern vex::motor arm2Mot;

extern vex::digital_out clampPis;
extern vex::digital_out lDoinkerPis;
extern vex::digital_out rDoinkerPis;
extern vex::digital_out ptoPis;
extern vex::digital_out intLiftPis;
// sensors
extern vex::inertial Inertial;
// drivetrain
extern vex::motor l1Mot;
extern vex::motor l2Mot;
extern vex::motor l3Mot;
extern vex::motor r1Mot;
extern vex::motor r2Mot;
extern vex::motor r3Mot;

void vexcodeInit(void);