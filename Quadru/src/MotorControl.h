#pragma once

#include "cinder/app/App.h"

#include "Motor.h"
class MotorControl
{

public:
	MotorControl() {}
	void setup();
	void setGui();
	std::vector<MotorRef> motors;


	
};