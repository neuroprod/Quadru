#pragma once

#include "cinder/app/App.h"
#include "GraphData.h"
#include <map>
class Graph 
{
public:
	Graph() {}


	void prepData(std::string name, int length, std::vector<float> scale, std::vector<ci::Color> color, std::vector<std::string> names);
	void prepData(std::string name, float data, float scale);

	void addData(std::string name, float data);
	void addData(std::string name, std::vector<float> data);
	void drawGui();
	void draw();
	std::map<std::string, GraphDataRef> gData;
};