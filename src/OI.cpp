/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"
#include <WPILib.h>

OI::OI()
	:joyLeft(new Joystick(2)), joyRight(new Joystick(4)), joyArm(new Joystick(3))

{

}


Joystick* OI::getjoyStickLeft(){
	return joyLeft;
}
Joystick* OI::getjoyStickRight(){
	return joyRight;
}
Joystick* OI::getjoyStickArm(){
	return joyArm;
}



