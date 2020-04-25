#pragma once
#include "cinder/app/App.h"
#include "Controle.h"
#include "WalkLeg.h"
#include "PathPlanner.h"
#include "PID.h"
class WalkControle;
typedef std::shared_ptr<WalkControle  >WalkControleRef;

class WalkControle
{
public:
	enum MOVESTATE { STOP, STARTWALK, WALK,STOPWALK };
	WalkControle() {  };
	void setup(ControleRef _controle, PathPlannerRef _pathPlaner) ;
	void update(float rotX) ;

	void drawGui() ;

	

	ControleRef controle;
	PathPlannerRef pathPlaner;
	PID pid;
	WalkLegRef FRLeg;
	WalkLegRef FLLeg;
	WalkLegRef BRLeg;
	WalkLegRef BLLeg;
	std::vector<WalkLegRef > legs;

	MOVESTATE currentState = MOVESTATE::STOP;


	int stepCount = 0;
	int numSteps = 0;


	float walkTime = 0.15;
	float walkDistance = 0;
};