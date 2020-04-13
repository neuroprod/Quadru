#include "Controle.h"
#include "CinderImGui.h"

using namespace ci;
using namespace ci::app;
using namespace std;


void Controle::setup(ModelConfigRef _config)
{

	config = _config;

	FR = ControleLeg::create();
	FL = ControleLeg::create();
	BR = ControleLeg::create();
	BL = ControleLeg::create();

	legs.push_back(FR);
	legs.push_back(FL);
	legs.push_back(BR);
	legs.push_back(BL);

	setBase();

}

void Controle::setBase() 
{
	bodyX = 0;
	bodyY = config->bodyY;
	bodyZ = 0;

	bodyRotX = 0;
	bodyRotY = 0;
	bodyRotZ = 0;


	FR->homePos = FR->targetPos = vec3(config->bodyLength / 2 +config->hipOffsetX, 0, config->bodyWidth / 2 + config->hipOffsetZ);
	FL->homePos = FL->targetPos = vec3(config->bodyLength / 2 + config->hipOffsetX, 0, -config->bodyWidth / 2- config->hipOffsetZ);
	BR->homePos = BR->targetPos = vec3(-config->bodyLength / 2 - config->hipOffsetX, 0, config->bodyWidth / 2 + config->hipOffsetZ);
	BL->homePos = BL->targetPos = vec3(-config->bodyLength / 2 - config->hipOffsetX, 0, -config->bodyWidth / 2 - config->hipOffsetZ);

	

}

void Controle::update()
{
	if (config->needsRebuild)setBase();

}
void Controle::drawGui() 
{
	ui::ScopedWindow window("Control");


	
	ui::DragFloat("body X", &bodyX, 1, -100, 100) ;
	ui::DragFloat("body Y", &bodyY, 1, 0, 700);
	ui::DragFloat("body Z", &bodyZ, 1, -100, 100);

	ui::DragFloat("body rotX", &bodyRotX, 0.01, -3.1415, 3.1415);
	ui::DragFloat("body rotY", &bodyRotY, 0.01, -3.1415, 3.1415) ;
	ui::DragFloat("body rotZ", &bodyRotZ, 0.01, -3.1415, 3.1415) ;

	ui::Separator();
	ui::DragFloat3("FR Target", &FR->targetPos[0], 1.f,-1000, 1000);
	ui::DragFloat3("FL Target", &FL->targetPos[0], 1.f, -1000, 1000);

	ui::DragFloat3("BR Target", &BR->targetPos[0], 1.f, -1000, 1000);
	ui::DragFloat3("BL Target", &BL->targetPos[0], 1.f, -1000, 1000);

}