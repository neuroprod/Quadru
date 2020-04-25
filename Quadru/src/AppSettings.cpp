#include "AppSettings.h"
#include "CinderImGui.h"
using namespace ci;
using namespace ci::app;
using namespace std;


void AppSettings::drawGui() 
{
	ui::ScopedWindow window("AppSettings");
	ui::Checkbox("use Physics", &usePhysics);
	ui::Checkbox("walking path editor", &pathEditor);
}

