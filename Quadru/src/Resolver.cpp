#include <glm/gtx/matrix_decompose.hpp>
#include "Resolver.h"
#include "CinderImGui.h"
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

	if (!play && !step) return;

	step = false;
	float timeStep = (1.f / 6000.f);

	
	vec3 gravetyForce = mass * vec3(0, -10, 0) * timeStep;

	for (int i = 0; i < 100; i++) {

		currentSpeed += gravetyForce;

		transMat = glm::translate(transMat, currentSpeed * timeStep * 1000.f);
		model->root->baseMatrix = transMat;
		model->root->update();


		
		hits.clear();
		hitDepth = 0;

		checkHit(model->FRLeg->getBallPos());
		checkHit(model->FLLeg->getBallPos());
		checkHit(model->BRLeg->getBallPos());
		checkHit(model->BLLeg->getBallPos());
		if (hits.size() > 0) {
			hitDepth /= hits.size();

			float e = 0.1;
			// Calculate impulse scalar
			float j = -(1 + e) * currentSpeed.y;
			j /= 1.f / mass;

			vec3 impulse = j * vec3(0, 1, 0);
			vec3 vAdj = 1.f / mass * impulse;
		

			transMat = glm::translate(transMat, vAdj * timeStep * 1000.f);
			model->root->baseMatrix = transMat;
			model->root->update();
		
			currentSpeed += vAdj;
		}
	}
	

	
}
void Resolver::checkHit(glm::vec3 pos) 
{
	if (pos.y >= 0) return; //noHit
	hits.push_back(pos);
	hitDepth +=-pos.y/1000.f;



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

void  Resolver::drawGui() 
{
	ui::ScopedWindow window("PhysicsSimulation");

	if (ui::Button("play")) { play = true; } ui::SameLine();
	if (ui::Button("pauze")) { play = false; }ui::SameLine();
	if (ui::Button("step")) { step = true; }ui::SameLine();


	if (ui::Button("reset")) 
	{
	
		transMat = glm::mat4(1.0);
	
			
		model->root->baseMatrix = transMat;
		currentSpeed = vec3(0, 0, 0);
	}

}