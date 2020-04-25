#include "WalkLeg.h"


using namespace ci;
using namespace ci::app;
using namespace std;
void WalkLeg::setStepState(int state, float dist, int numsteps)
{
	stepState = state;
	//0 =rising to home, 1=faling to target ,2=gliding to home, 3=gliding to target
	if (stepState == 0)
	{
		positions =pathPlaner->getPathWalkRising(dist, 50, numsteps);
	}
	else if (stepState == 1)
	{
		positions = pathPlaner->getPathWalkFaling(dist, 50, numsteps);
	}
	else if (stepState == 2)
	{
		positions = pathPlaner->getPathWalkHome(dist, 50, numsteps);
	}
	else if (stepState == 3)
	{
		positions = pathPlaner->getPathWalkStep(dist, 50, numsteps);
	}
}
void WalkLeg::nextStepState(float dist,int numsteps) 
{
	stepState++;
	setStepState(stepState % 4, dist, numsteps);

	

}
void WalkLeg::update(int p) 
{

	vec2 pos = positions[p];
	currentPos.x = pos.x;
	currentPos.y = -pos.y;
	currentPos.z = 0;

	
}