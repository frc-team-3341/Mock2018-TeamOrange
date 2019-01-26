#include "DriveForward.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include "../Robot.h"
using namespace std;

DriveForward::DriveForward(double _setpoint) : setpoint(_setpoint){
	time1 = 0;
	time2 = 0;
	velocity = 0;
	position_avg=0;

	Requires(Robot::drive);

}

void DriveForward::Initialize() {
	position_avg = fabs((Robot::drive->leftDistance() + Robot::drive->rightDistance()) / 2);
	Robot::drive->resetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute() {
	Robot::drive->tankDrive("magic",200, 200, 1000, 500);
	//drive->tankDrive("auto",velocity,velocity);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForward::IsFinished() {
	return fabs(position_avg - setpoint) < 3;
}

// Called once after isFinished returns true
void DriveForward::End() {
	std::cout << "error is finished and REACHED END " << fabs(position_avg - setpoint) << std::endl;
	Robot::drive->arcadeDrive(0, 0, 0.2);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForward::Interrupted() {
}
