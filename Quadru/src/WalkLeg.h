#pragma once
#include "cinder/app/App.h"
#include "PathPlanner.h"
class WalkLeg;
typedef std::shared_ptr<WalkLeg> WalkLegRef;

class WalkLeg
{

public:
	WalkLeg() {};
	void update(int time);

	int stepState = 0;  //0 =rising to home, 1=faling to target ,2=gliding to home, 3=gliding to target
	void setStepState(int state, float dist,int numsteps);
	void nextStepState( float dist, int numsteps);
	PathPlannerRef pathPlaner;
	std::vector<ci::vec2> positions;

	ci::vec3 currentPos;
};