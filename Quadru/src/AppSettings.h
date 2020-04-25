#pragma once
#include "cinder/app/App.h"

class AppSettings 
{

public:
	
	AppSettings() {}
	void drawGui();
	bool usePhysics = true;
	bool pathEditor = false;
};