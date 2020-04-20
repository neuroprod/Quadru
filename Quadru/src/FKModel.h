#pragma once
#include "cinder/app/App.h"
#include "FKNode.h"
#include "FKLeg.h"
#include "ModelConfig.h";
#include "PhysicsWorld.h";
class FKModel;
typedef std::shared_ptr<FKModel> FKModelRef;

class FKModel
{
public:
	FKModel() {};
	void setup(ModelConfigRef config, PhysicsWorldRef _world);
	void rebuild();
	void update();
	PhysicsWorldRef world;
	ModelConfigRef config;
	FKNodeRef root;
	FKNodeRef body;

	FKLegRef FRLeg;
	FKLegRef FLLeg;

	FKLegRef BRLeg;
	FKLegRef BLLeg;

	std::vector<FKNodeRef> nodes;
	std::vector<FKLegRef> legs;

	std::vector<glm::vec3> testPos;
	btMultiBody* mMultiBody;
};