#include "PathPlanner.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"



using namespace ci;
using namespace ci::app;
using namespace std;


void PathPlanner::drawGui() 
{
	ui::ScopedWindow window("Walking Path");
	ui::Checkbox("debugMode", &debugMode);
	if (debugMode) 
	{
	
		ui::DragFloat("stepDist", &dStepDistance);
		ui::DragFloat("stepHeight", &dStepHeight);
	}



}
void PathPlanner::draw() 
{
	if (debugMode) {
		gl::clear(GL_DEPTH_BUFFER_BIT);
	
		gl::color(ColorA(0, 0, 0, 0.8));
		gl::drawSolidRect(Rectf(getWindowBounds()));
		gl::pushMatrices();
	
		gl::translate(getWindowWidth() / 2, getWindowHeight() / 2+200);
		gl::scale(4, 4);
		gl::color(Color(0.9, 0.9, 0.9));
		gl::drawLine(vec2(-dStepDistance/2, 0),vec2 ( dStepDistance / 2,0));
		gl::drawLine(vec2(0, 0), vec2(0, -dStepHeight));
		gl::popMatrices();
		
	}

}