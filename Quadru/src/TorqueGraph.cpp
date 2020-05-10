#include "TorqueGraph.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"



using namespace ci;
using namespace ci::app;
using namespace std;

void TorqueGraph::addData(ci::vec3 FR, ci::vec3 FL, ci::vec3 BR, ci::vec3 BL, ci::vec3 stepInfo) 
{
	FRd.push_back(FR);
	FLd.push_back(FL);
	BRd.push_back(BR);
	BLd.push_back(BL);
	step.push_back(stepInfo);
	
	if (FRd.size() > 500) 
	{
		FRd.erase(FRd.begin());
		FLd.erase(FLd.begin());
		BRd.erase(BRd.begin());
		BLd.erase(BLd.begin());
		step.erase(step.begin());
	}
}
void TorqueGraph::draw() 
{
	gl::pushMatrices();
	gl::translate(100, 0);
	gl::color(ci::Color::gray(0.5));
	for (int i = 0; i < FRd.size(); i++)
	{
		if (step[i].x == 1) {
			gl::drawLine(vec2(i * 2, 0), vec2(i * 2, 1000));
			if (step[i].y == 0) 
			{
				gl::drawSolidCircle(vec2(i * 2, 100-50), 5);
				gl::drawSolidCircle(vec2(i * 2, 700 - 50), 5);
			}
			if (step[i].y == 2)
			{
				gl::drawSolidCircle(vec2(i * 2, 300 - 50), 5);
				gl::drawSolidCircle(vec2(i * 2, 500 - 50), 5);
			}
		
		}
		
		

	}
	
	gl::popMatrices();

	gl::pushMatrices();
	gl::translate(100, 150);
	gl::begin(GL_LINE_STRIP);
	gl::color(ci::Color::gray(1));
	for (int i = 0; i < step.size(); i++)
	{
		gl::vertex(vec2(i * 2, step[i].z));

	}
	gl::end();
	gl::popMatrices();


	gl::color(ci::Color(1,0,0));
	drawGraph(FRd, 0, 100);
	drawGraph(FLd, 0, 300);
	drawGraph(BRd, 0, 500);
	drawGraph(BLd, 0, 700);

	gl::color(ci::Color(0, 1, 0));
	drawGraph(FRd, 1, 100);
	drawGraph(FLd, 1, 300);
	drawGraph(BRd, 1, 500);
	drawGraph(BLd, 1, 700);

	gl::color(ci::Color(0, 0, 1));
	drawGraph(FRd, 2, 100);
	drawGraph(FLd, 2, 300);
	drawGraph(BRd, 2, 500);
	drawGraph(BLd, 2, 700);
	
}

void TorqueGraph::drawGraph(std::vector<ci::vec3>& vecData, int index, int posY) 
{
	gl::pushMatrices();
	gl::translate(100, posY);
	gl::begin(GL_LINE_STRIP);
	for (int i = 0; i < vecData.size(); i++)
	{
		gl::vertex(vec2(i * 2, vecData[i][index]));

	}
	gl::end();
	gl::popMatrices();


}