#include "CommandBase.h"
#include <iostream>

#include <Commands/Scheduler.h>



// Initialize a single static instance of all of your subsystems. The following
// line should be repeated for each subsystem in the project.


//DriveTrain* CommandBase::drive = nullptr;
//Arm* CommandBase::arm = nullptr;
//std::unique_ptr<OI> CommandBase::oi;



CommandBase::CommandBase(const std::string &name) {

}



void CommandBase::initialize()
{

//	drive = new DriveTrain();
	std::cout << "drivetrain constructor completed" << std::endl;
	//arm = new Arm();
	//oi = std::make_unique<OI>();
	std::cout << "commandBase initialize completed" << std::endl;


}
