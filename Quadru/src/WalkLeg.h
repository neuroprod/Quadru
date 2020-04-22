#pragma once
#include "cinder/app/App.h"

class WalkLeg;
typedef std::shared_ptr<WalkLeg> WalkLegRef;

class WalkLeg
{

public:
	WalkLeg() {};
	void update(float time);
	float stepHeight =70;

	int stepState = 0;  //0 =rising to home, 1=faling to target ,2=gliding to home, 3=gliding to target
	float moveDistance;
	ci::vec3 currentPos =ci::vec3(0,0,0);


};