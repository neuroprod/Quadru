#pragma once
#include "cinder/app/App.h"
#include "ModelConfig.h";
#include "PhysicsWorld.h";
#include "PhysicsLeg.h";
class PhysicsModel;
typedef std::shared_ptr< PhysicsModel>  PhysicsModelRef;

class PhysicsModel
{
public:
	PhysicsModel() {};
	void setup(ModelConfigRef config, PhysicsWorldRef _world);
	void setMotorTargets(std::vector<float> targets);
	void rebuild();
	void update();

	PhysicsWorldRef world;
	ModelConfigRef config;

	PhysicsLegRef FRLeg;
	PhysicsLegRef FLLeg;
	PhysicsLegRef BRLeg;
	PhysicsLegRef BLLeg;



	std::vector<PhysicsLegRef> legs;
	btMultiBody* mMultiBody;


	glm::mat4 bodyMatrix;
	std::vector<float> angles;
}; 
