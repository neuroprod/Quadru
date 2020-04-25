#pragma once
#include "cinder/app/App.h"

class AppSettings 
{

public:
	
	AppSettings() {}
	void drawGui();
	bool usePhysics = false;
	bool pathEditor = true;
};