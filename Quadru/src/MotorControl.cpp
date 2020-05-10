#include "MotorControl.h"

#include "CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
//115200
void MotorControl::setup() 
{
	MotorRef FRHip = Motor::create();
	FRHip->setup(1, "FRHip","COM13");
	motors.push_back(FRHip);	
}

void MotorControl::setGui()
{
	ui::ScopedWindow window("Motor");

	for (auto m : motors)
	{
		m->drawGui();
	}
}

