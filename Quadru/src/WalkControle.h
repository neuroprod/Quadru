#pragma once
#include "cinder/app/App.h"
#include "Controle.h"
#include "WalkLeg.h"
#include "PID.h"
class WalkControle;
typedef std::shared_ptr<WalkControle  >WalkControleRef;

class WalkControle
{
public:
	enum MOVESTATE { STOP, STARTWALK, WALK,STOPWALK };
	WalkControle() {  };
	void setup(ControleRef _controle) ;
	void update(float rotX) ;

	void drawGui() ;
	float time=0;
	float stepTime =0.15;
	float stepDistance = 0;
	ControleRef controle;
	PID pid;
	WalkLegRef FRLeg;
	WalkLegRef FLLeg;
	WalkLegRef BRLeg;
	WalkLegRef BLLeg;
	std::vector<WalkLegRef > legs;

	MOVESTATE currentState = MOVESTATE::STOP;
};