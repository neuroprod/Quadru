#include "Graph.h"
#include "GraphDataFloat.h"
#include "GraphDataArray.h"
#include "CinderImGui.h"
using namespace ci;
using namespace ci::app;
using namespace std;


void Graph::prepData(std::string name, int size, vector<float> scale,  std::vector<ci::Color> color, std::vector<std::string> names)
{
	auto it = gData.find(name);
	if (it != gData.end())
	{

		return;
	}
	else
	{
		GraphDataArrayRef r = std::make_shared<GraphDataArray>();
		r->scale = scale;
		r->color = color;
		r->names = names;
		r->name = name;
		r->size = size;
		gData.insert(std::pair<string, GraphDataRef>(name, r));
	}
}

void Graph::prepData(std::string name, float data, float scale)
{

	auto it = gData.find(name);
	if (it != gData.end())
	{

		return;
	}
	else
	{
		GraphDataFloatRef r = std::make_shared<GraphDataFloat>();
		r->scale = scale;
		r->name = name;
		gData.insert(std::pair<string, GraphDataRef>(name, r));
	}


}
void Graph::addData(std::string name, vector<float> data)
{

	auto it = gData.find(name);
	if (it != gData.end())
	{

		GraphDataArrayRef r = std::static_pointer_cast<GraphDataArray>(it->second);
		r->addData(data);
	}



}
void Graph::addData(std::string name, float data) 
{

	auto it = gData.find(name);
	if (it != gData.end()) 
	{
	
		GraphDataFloatRef r =std::static_pointer_cast<GraphDataFloat>(it->second);
		r->addData(data);
	}
	


}
void Graph::drawGui() 
{
	ui::ScopedWindow window("Graph");
	for (auto const& [key, val] : gData)
	{
		ui::Checkbox(key.c_str(), &val->visible);
	}
}
void Graph::draw() 
{
	for (auto const& [key, val] : gData)
	{
		if(val->visible)
		{
			val->draw();
		}

	}
}