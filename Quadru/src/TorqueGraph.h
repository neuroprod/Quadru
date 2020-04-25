#pragma once
#include "cinder/app/App.h"
class TorqueGraph 
{
public:
	TorqueGraph() {};
	void addData(ci::vec3 FR, ci::vec3 FL, ci::vec3 BR, ci::vec3 BL, ci::vec2 stepInfo);
	void draw();
	void drawGraph(std::vector<ci::vec3>& vecData, int index, int posY);
	std::vector<ci::vec2> step;
	std::vector<ci::vec3> FRd;
	std::vector<ci::vec3> FLd;
	std::vector<ci::vec3> BRd;
	std::vector<ci::vec3> BLd;

	
};