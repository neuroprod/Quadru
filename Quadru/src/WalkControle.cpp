#include "WalkControle.h"

#include "CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
void WalkControle::setup(ControleRef _controle, PathPlannerRef _pathPlaner)
{
	pathPlaner = _pathPlaner;
	controle = _controle;
	FRLeg = std::make_shared<WalkLeg>();
	FLLeg = std::make_shared<WalkLeg>();
	BRLeg = std::make_shared<WalkLeg>();
	BLLeg = std::make_shared<WalkLeg>();

	legs.push_back(FRLeg);
	legs.push_back(FLLeg);
	legs.push_back(BRLeg);
	legs.push_back(BLLeg);

	for (int i=0;i< 4;i++ )
	{
		legs[i]->pathPlaner = _pathPlaner;

	}

}
void WalkControle::update(float rotX) 
{
	float delta = 1.f / 120.f;

	

	controle->bodyZ = pid.calculate(0, rotX);

	if (currentState == MOVESTATE::STOP) 
	{

		if (walkDistance > 0) 
		{
			currentState = MOVESTATE::STARTWALK;
			stepCount = 0;
			numSteps = 0;

		}
		else 
		{
			return;
		}
	}

	if (stepCount == numSteps) 
	{
		stepCount = 0;
		numSteps = walkTime / (1.f / 120.f);
		if (currentState == MOVESTATE::STARTWALK) 
		{
			//0 =rising to home, 1=faling to target ,2=gliding to home, 3=gliding to target
			FRLeg->setStepState(0,0.f, numSteps);
			BLLeg->setStepState(0, 0.f, numSteps);
			FLLeg->setStepState(2, 0.f, numSteps);
			BRLeg->setStepState(2, 0.f, numSteps);

			currentState = MOVESTATE::WALK;
		}
		else if (currentState == MOVESTATE::WALK)
		{
			for (WalkLegRef l : legs)
			{
				l->nextStepState(walkDistance,numSteps);

			}
		}

	}
	for (WalkLegRef l : legs)
	{
		l->update(stepCount);

	}
	stepCount++;
	
	for (int i =0;i<4;i++ )
	{
		controle->legs[i]->targetPos = controle->legs[i]->homePos + legs[i]->currentPos;
	}
}

void WalkControle::drawGui() 
{
	ui::ScopedWindow windoww("WalkControl");
	if (ui::DragFloat("walkTime", &walkTime, 0.01, 0.1, 5));
	if (ui::DragFloat("move Distance", &walkDistance, 1, 0, 445));
	if (ui::Button("test")) { walkDistance = 100.0f; }
	
	pid.drawGui();
}