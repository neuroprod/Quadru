#pragma once
#include "cinder/app/App.h"
#include "ModelConfig.h"
#include "ControleLeg.h"
class Controle;
typedef std::shared_ptr<Controle  > ControleRef;

class Controle 
{
public: 
	Controle() {};
	void setup(ModelConfigRef _config);
	void setBase();
	void update();
	void drawGui();
	ModelConfigRef config;


	float bodyX = 50;
	float bodyY = 0;
	float bodyZ = 0;

	float bodyRotX = 0;
	float bodyRotY = 0;
	float bodyRotZ = 0;

	ControleLegRef FR;
	ControleLegRef FL;
	ControleLegRef BR;
	ControleLegRef BL;

	std::vector<ControleLegRef> legs;
	bool doReset = false;
};