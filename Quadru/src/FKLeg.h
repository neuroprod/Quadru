#pragma once
#include "cinder/app/App.h"
#include "FKNode.h"
#include "ModelConfig.h"
class FKLeg;
typedef std::shared_ptr<FKLeg> FKLegRef;

class FKLeg
{

public:

	FKLeg() {};
	static FKLegRef create();
	void setup(std::string name,FKNodeRef body,glm::vec3 pos, ModelConfigRef modelConfig, std::vector<FKNodeRef> &nodes);
	ci::vec3 getBallPos();

	ci::vec4 distToFoot;
	float footRadius = 0;
	float hipOffsetZFlip;
	FKNodeRef hip1;
	FKNodeRef hip2;
	FKNodeRef knee;


};