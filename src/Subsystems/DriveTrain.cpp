#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Commands/TankDrive.h"
#include "iostream"
using namespace std;
#define max(x, y) (((x) > (y)) ? (x) : (y))
//All of these method calls are necessary for motion magic, velocity control, and percent output control modes
DriveTrain::DriveTrain() : Subsystem("DriveTrain"), left(new TalonSRX(kLeftMotor)), right(new TalonSRX(kRightMotor)) {
	//Motion magic config methods
	int kPIDLoopIdx = 0;
	int kTimeoutMs = 30;

	left->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,0,10);
	left->SetSensorPhase(true);
	//left->SetStatusFramePeriod(StatusFrameEnhanced.Status_10_MotionMagic,10,kTimeoutMs)
	//left->SetStatusFramePeriod(StatusFrameEnhanced.Status_13_base_PIDF0,10,kTimeoutMs);

	left->ConfigNominalOutputForward(0, kTimeoutMs);
	left->ConfigNominalOutputReverse(0, kTimeoutMs);
	left->ConfigPeakOutputForward(1, kTimeoutMs);
	left->ConfigPeakOutputReverse(-1, kTimeoutMs);

	left->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
	left->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	left->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	left->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

	// left->ConfigEncoderCodesPerRev(360);
	left->ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_10Ms,0);
	left->ConfigVelocityMeasurementWindow(64,0);
	left->SetSelectedSensorPosition(0,0,10);

	left->Set(ControlMode::Position, 0);

	left->ConfigMotionCruiseVelocity(15000, kTimeoutMs);
	left->ConfigMotionAcceleration(6000, kTimeoutMs);

	right->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,0,10);
	right->ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_10Ms,0);
	right->ConfigVelocityMeasurementWindow(64,0);
	// right->ConfigEncoderCodesPerRev(360);
	right->SetSelectedSensorPosition(0,0,10);
	right->SetSensorPhase(true);
	right->Set(ControlMode::Position, 0);

	right->ConfigNominalOutputForward(0, kTimeoutMs);
	right->ConfigNominalOutputReverse(0, kTimeoutMs);
	right->ConfigPeakOutputForward(1, kTimeoutMs);
	right->ConfigPeakOutputReverse(-1, kTimeoutMs);

	right->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
	right->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	right->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	right->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

	right->ConfigMotionCruiseVelocity(15000, kTimeoutMs);
	right->ConfigMotionAcceleration(6000, kTimeoutMs);

	std::cout<<"DriveTrain Constructor Successful" <<std::endl;
	right->SetInverted(false);
	left->SetInverted(true);
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	std::cout<<"DriveTrain InitDefaultCommand Successful" <<std::endl;
	SetDefaultCommand(new TankDrive());
}


double DriveTrain::Limit(double num, double max) {
	if (num > max)
		return max;

	if (num < -max)
		return -max;

	return num;
}

void DriveTrain::tankDrive(std::string s, double leftVal, double rightVal) {
	if (s == "magic"){
		//Motion Magic
		left->Set(ControlMode::MotionMagic, leftVal*4096/circumference); //Convert inches to ticks
		right->Set(ControlMode::MotionMagic, rightVal*4096/circumference);
	}
	else if(s == "velocity"){
		left->Set(ControlMode::Velocity, DriveTrain::Limit(-leftVal, 5000)); //Convert inches to ticks
		right->Set(ControlMode::Velocity, DriveTrain::Limit(rightVal, 5000));
	}
	else{
		//Percent Output
		left->Set(ControlMode::PercentOutput, DriveTrain::Limit(leftVal, 1));
		right->Set(ControlMode::PercentOutput, DriveTrain::Limit(rightVal, 1));
	}
	//cout << "left: " << leftVal << "  right: " << rightVal << endl;
}
void DriveTrain::tankDrive(std::string s, double leftVal, double rightVal, int cruiseVel, int cruiseAcc) {
	//Motion magic with more control over parameters
	left->ConfigMotionCruiseVelocity(cruiseVel, kTimeoutMs);
	left->ConfigMotionAcceleration(cruiseAcc, kTimeoutMs);
	right->ConfigMotionCruiseVelocity(cruiseVel, kTimeoutMs);
	right->ConfigMotionAcceleration(cruiseAcc, kTimeoutMs);
	if (s == "magic"){
		left->Set(ControlMode::MotionMagic, leftVal*4096/circumference);
		right->Set(ControlMode::MotionMagic, rightVal*4096/circumference);
	}
	else{
		left->Set(ControlMode::PercentOutput, DriveTrain::Limit(leftVal, 1));
		right->Set(ControlMode::PercentOutput, DriveTrain::Limit(rightVal, 1));
	}
	//cout << "left: " << leftVal << "  right: " << rightVal << endl;
}


void DriveTrain::arcadeDrive(double moveVal, double rotateVal, double limit) {
	double leftMotorOutput, rightMotorOutput;

/*
	TalonSRX::FeedbackDeviceStatus sensorStatus = left->IsSensorPresent(CANTalon::CtreMagEncoder_Relative);
	TalonSRX::FeedbackDeviceStatus sensorStatus2 = right->IsSensorPresent(CANTalon::CtreMagEncoder_Relative);
	std::cout << "Left, Right: " << sensorStatus << "   " << sensorStatus2 << std::endl;
*/
	// Standard ArcadeDriveTrain algorithm from Google
	if (moveVal > 0.0) {
		if (rotateVal > 0.0) {
			leftMotorOutput = moveVal - rotateVal;
			rightMotorOutput = max(moveVal, rotateVal);
		} else {
			leftMotorOutput = max(moveVal, -rotateVal);
			rightMotorOutput = moveVal + rotateVal;
		}
	} else {
		if (rotateVal > 0.0) {
			leftMotorOutput = -max(-moveVal, rotateVal);
			rightMotorOutput = moveVal + rotateVal;
		} else {
			leftMotorOutput = moveVal - rotateVal;
			rightMotorOutput = -max(-moveVal, -rotateVal);
		}
	}

	left->Set(ControlMode::PercentOutput, DriveTrain::Limit(leftMotorOutput, limit));
	right->Set(ControlMode::PercentOutput, DriveTrain::Limit(rightMotorOutput, limit));
}




void DriveTrain::resetEncoders(){
	left->SetSelectedSensorPosition(0,0,10);
	right->SetSelectedSensorPosition(0,0,10);
	left->Set(ControlMode::Position, 0);
	right->Set(ControlMode::Position, 0);
	cout << left->HasResetOccurred() << endl;
	cout<<"reset enc"<<endl;
}

/* DriveTrain::setStartAbsTicks(){
	startAbsTicks = left->GetSensorCollection().GetPulseWidthPosition();
	cout << "Start: " << startAbsTicks << endl;
}*/

double DriveTrain::leftDistance() { //inches

	//double test = left->GetSensorCollection().GetPulseWidthPosition();
	double relativePosition = left->GetSensorCollection().GetQuadraturePosition(); // Return ticks

	relativePosition = ((relativePosition) / 4096) * circumference; // 4096 ticks per revolution
	//cout << "Abs: " << test << endl;
	//test = ((test)/ 4096) * circumference;

	//cout << "Start: " << startAbsTicks << endl;
	//cout<< "Relative Position: " << relativePosition <<std::endl;
	//cout<< "Absolute Position: " << test <<std::endl;

	return relativePosition;
}

double DriveTrain::rightDistance() { //inches

	// double relativePosition = (double) (right->GetSensorCollection().GetPulseWidthPosition()); This also works, but I don't know what is different
	double relativePosition = -(right->GetSensorCollection().GetQuadraturePosition()); // Negative sign makes sure that forwards is positive and backwards is negative
	relativePosition = (relativePosition / 4096) * circumference; // 4096 ticks per revolution
	// std::cout<< "Right Wheel Relative Position: " << relativePosition << std::endl;
	return relativePosition;


}

double DriveTrain::getSpeed(){
	return ((left->GetSensorCollection().GetPulseWidthVelocity()*10)/4096);
	//return left()*(10/4096) * circumference;
}
