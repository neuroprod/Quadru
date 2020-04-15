
#include "Resolver.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void Resolver::setup(FKModelRef _model)
{
	model = _model;
	mass = getMass();
	mass3 = glm::pow(mass,1.f/3.f);
	centerOfMass = getCenterOfMass();

}
void Resolver::update() 
{
	centerOfMass = getCenterOfMass();

}

float Resolver::getMass()
{
	float m = 0;
	for (auto n : model->nodes)
	{

		m += n->nodeData->mass;


	}
	return m;
}
glm::vec4 Resolver::getCenterOfMass() 
{
	vec4 c =vec4(0,0,0,0);
	for (auto n : model->nodes)
	{
		
		c+=n->nodeData->mass *n->nodeData->centerOfMassGlobal;
		

	}
	c /= mass;
	return c;
}