/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoPath1.h"

AutoPath1::AutoPath1() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
	// TODO Auto-generated constructor stub
		AddSequential(new DriveForward(85));
		AddSequential(new AutoArmMove(4096));
		AddSequential(new Turn(90));
		AddSequential(new DriveForward(48));
		AddSequential(new Turn(-90));
		AddSequential(new AutoArmMove(4096));
		AddSequential(new DriveForward(-40));
		AddSequential(new Turn(75.69));
		AddSequential(new DriveForward(-99.08));
		AddSequential(new DriveForward(50));
		AddSequential(new Turn(-75.69));
		AddSequential(new DriveForward(24));
}
