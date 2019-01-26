/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoArmMove.h"
#include "../Robot.h"

AutoArmMove::AutoArmMove(double setpoint) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	//pos = setpoint;
	Requires(Robot::arm);
	pos = setpoint;
}

// Called just before this Command runs the first time
void AutoArmMove::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoArmMove::Execute() {
	Robot::arm->move(.8);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoArmMove::IsFinished() {
	if(Robot::arm->getPosition() - pos <=30) return true;
	else return false;
}

// Called once after isFinished returns true
void AutoArmMove::End() {
	Robot::arm->resetEncoders();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoArmMove::Interrupted() {

}
