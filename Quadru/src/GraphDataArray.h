#pragma once
#include "cinder/app/App.h"
#include "GraphData.h"
class GraphDataArray;
typedef std::shared_ptr<GraphDataArray> GraphDataArrayRef;

class GraphDataArray :public GraphData
{
public:
	GraphDataArray() {};

	void addData(std::vector<float> data);
	void draw();
	std::list<std::vector<float>> data;
	int size;
	std::vector<float> scale;
	std::vector<ci::Color> color;
	std::vector<std::string> names;
};