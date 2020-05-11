#pragma once
#include "cinder/app/App.h"
#include "GraphData.h"
class GraphDataFloat;
typedef std::shared_ptr<GraphDataFloat> GraphDataFloatRef;

class GraphDataFloat :public GraphData
{
public:
	GraphDataFloat() {};

	void addData(float data);
	void draw();
	std::list<float> data;
	float scale;
};