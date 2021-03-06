/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "Commands/DriveForward.h"
#include "Commands/AutoPath1.h"

#include <Commands/Scheduler.h>
#include <SmartDashboard/SmartDashboard.h>

ExampleSubsystem* Robot::m_subsystem;
OI* Robot::m_oi;
DriveTrain* Robot::drive;
Arm* Robot::arm;

void Robot::RobotInit() {
	//m_chooser.AddDefault("Default Auto", &m_defaultAuto);
	//m_chooser.AddObject("My Auto", &m_myAuto);
	//m_chooser.AddObject("DriveForward", new DriveForward(60));
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
	m_subsystem = new ExampleSubsystem();

		drive= new DriveTrain();
		arm = new Arm();
		m_oi = new OI();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
	// std::string autoSelected = frc::SmartDashboard::GetString(
	// 		"Auto Selector", "Default");
	// if (autoSelected == "My Auto") {
	// 	m_autonomousCommand = &m_myAuto;
	// } else {
	// 	m_autonomousCommand = &m_defaultAuto;
	// }

	//m_autonomousCommand = m_chooser.GetSelected();
	m_autonomousCommand = (new DriveForward(100));
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Start();
	} else {
		std::cout<<"Hi";
	}

}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
