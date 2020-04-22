#include "WalkControle.h"

#include "CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;
void WalkControle::setup(ControleRef _controle)
{
	controle = _controle;
	FRLeg = std::make_shared<WalkLeg>();
	FLLeg = std::make_shared<WalkLeg>();
	BRLeg = std::make_shared<WalkLeg>();
	BLLeg = std::make_shared<WalkLeg>();

	legs.push_back(FRLeg);
	legs.push_back(FLLeg);
	legs.push_back(BRLeg);
	legs.push_back(BLLeg);

}
void WalkControle::update(float rotX) 
{
	float delta = 1.f / 120.f;
	controle->bodyZ = pid.calculate(0, rotX);

	if (currentState == MOVESTATE::STOP) 
	{
		if (stepDistance > 0) 
		{
			currentState = MOVESTATE::WALK;
			time = 0;

			FRLeg->stepState=0;
			FRLeg->moveDistance = stepDistance;
		
			BLLeg->stepState = 0;
			BLLeg->moveDistance = stepDistance;


			FLLeg->stepState = 2;
			FLLeg->moveDistance = stepDistance;
		
			BRLeg->stepState = 2;
			BRLeg->moveDistance = stepDistance;

		}
		else 
		{
			return;
		}
	}
	time += delta;

	if (time > stepTime) {
		time = 0;
	
		for (WalkLegRef l : legs)
		{
			l->stepState += 1;
			if (l->stepState > 3) l->stepState = 0;
		}
	
	}
	float nTime = time / stepTime;
	
	for (WalkLegRef l : legs)
	{
		l->update(nTime);
		
	}
	
	for (int i =0;i<4;i++ )
	{
		controle->legs[i]->targetPos = controle->legs[i]->homePos + legs[i]->currentPos;
	}
}

void WalkControle::drawGui() 
{
	ui::ScopedWindow windoww("WalkControl");
	if (ui::DragFloat("stepTime", &stepTime, 0.01, 0.1, 5));
	if (ui::DragFloat("move Distance", &stepDistance, 1, 0, 45));
	if (ui::Button("test")) { stepDistance = 1.0f; }
	
	pid.drawGui();
}