#include "WalkLeg.h"


using namespace ci;
using namespace ci::app;
using namespace std;

void WalkLeg::update(float p) 
{
	//0 =rising to home, 1=faling to target ,2=gliding to home, 3=gliding to target
	float eTime = 0;
	if (p < 0.5)
	{
		eTime = 4 * p * p * p;
	}
	else
	{
		float f = ((2 * p) - 2);
		eTime = 0.5 * f * f * f + 1;
	}
	if (stepState == 0) 
	{
		currentPos.y = stepHeight * eTime;
	}
	if (stepState == 1)
	{
		currentPos.y = stepHeight *(1.f- eTime);
	}
	
}