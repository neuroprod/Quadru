#pragma once
#include "cinder/app/App.h"
#include "FKNode.h"
#include "FKLeg.h"
#include "ModelConfig.h";
class FKModel;
typedef std::shared_ptr<FKModel> FKModelRef;

class FKModel
{
public:
	FKModel() {};
	void setup(ModelConfigRef config);
	void rebuild();
	void update();

	ModelConfigRef modelConfig;
	FKNodeRef root;
	FKNodeRef body;

	FKLegRef FRLeg;
	FKLegRef FLLeg;

	FKLegRef BRLeg;
	FKLegRef BLLeg;

	std::vector<FKNodeRef> nodes;
};