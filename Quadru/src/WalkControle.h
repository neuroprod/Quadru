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
	void update(float rotX,float rotZ) ;

	void drawGui() ;

	

	ControleRef controle;
	PathPlannerRef pathPlaner;
	PID pidX;
	PID pidZ;
	WalkLegRef FRLeg;
	WalkLegRef FLLeg;
	WalkLegRef BRLeg;
	WalkLegRef BLLeg;

	std::vector<WalkLegRef > legs;
	float xOffzet = 0;
	MOVESTATE currentState = MOVESTATE::STOP;

	int stepCount2 = 0;
	int stepCount = 0;
	int numSteps = 0;
	float heightBounce = 0;
	float bounceSize = 0;
	float bounceOffset = 1.6;


	float walkTime = 0.15;
	float walkDistance = 0;
};