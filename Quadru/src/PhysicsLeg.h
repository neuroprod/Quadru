#pragma once
#include "cinder/app/App.h"
#include "FKNode.h"
#include "ModelConfig.h"
#include "PhysicsWorld.h";

class PhysicsLeg;
typedef std::shared_ptr<PhysicsLeg> PhysicsLegRef;

class PhysicsLeg
{

public:

	PhysicsLeg() {};
	static PhysicsLegRef create();
	void setup(std::string name, glm::vec3 pos, ModelConfigRef modelConfig, btMultiBody* multiBody, int linkIndex);
	

	
	btMultiBodyJointMotor* motorHip1;
	btMultiBodyJointMotor* motorHip2;
	btMultiBodyJointMotor* motorKnee;
}; 
