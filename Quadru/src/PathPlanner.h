#pragma once
#include "cinder/app/App.h"
class PathPlanner;
typedef std::shared_ptr< PathPlanner>  PathPlannerRef;
class PathPlanner {

public:

	PathPlanner() {}
	void drawGui();
	void draw();
	bool debugMode = true;

	float dStepDistance=200;
	float dStepHeight=70;
};