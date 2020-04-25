#pragma once
#include "cinder/app/App.h"
#include "cinder/BSpline.h"
class PathPlanner;
typedef std::shared_ptr< PathPlanner>  PathPlannerRef;
class PathPlanner {

public:

	PathPlanner() {}

	void updateDebugPaths();

	std::vector<ci::vec2> getPathWalkRising(float stepDistance, float stepHeight, int numSteps);
	std::vector<ci::vec2> getPathWalkRisingL(float stepDistance, float stepHeight, int numSteps);
	std::vector<ci::vec2> dPathRising;

	std::vector<ci::vec2> getPathWalkFaling(float stepDistance, float stepHeight, int numSteps);
	std::vector<ci::vec2> getPathWalkFalingL(float stepDistance, float stepHeight, int numSteps);
	std::vector<ci::vec2> dPathFaling;

	std::vector<ci::vec2> getPathWalkHome(float stepDistance, float stepHeight, int numSteps);
	std::vector<ci::vec2> dPathHome;

	std::vector<ci::vec2> getPathWalkStep(float stepDistance, float stepHeight, int numSteps);
	std::vector<ci::vec2> dPathStep;

	std::vector< ci::vec2> fullPath;

	void drawVector(std::vector<ci::vec2>& path);



	void drawGui();
	void draw();


	bool debugMode = true;
	float slowDown = 1;
	bool linear = false;

	bool startWalk = false;
	bool stopWalk = false;

	int stepCount = 0;
	float dStepDistance=200;
	float dStepHeight=70;
	bool isDirty = true;

	int dDebugSteps = 18;
	float dStepTime = 150;

	float walkRisingIn = 0.1;
	float walkRisingOut = 0.4;
	float walkRisingMidX = 0.5;
	float  walkRisingMidY = 0.5;

	float walkFalingIn = 0.1;
	float walkFalingOut = 0.4;
	float walkFalingMidX = 0.6;
	float  walkFalingMidY = 0.5;
};