#pragma once
#include "cinder/app/App.h"

class GraphData;
typedef std::shared_ptr<GraphData> GraphDataRef;

class GraphData 
{
public:
	GraphData() {};
	virtual void draw() {};
	std::string name;
	
	bool visible = true;

};