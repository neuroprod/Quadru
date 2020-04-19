#include "FKLeg.h"
using namespace ci;
using namespace ci::app;
using namespace std;
FKLegRef FKLeg::create()
{
	FKLegRef ref = std::make_shared<FKLeg>();
	return ref;
}

void FKLeg::setup(string name,FKNodeRef body, glm::vec3 pos, ModelConfigRef modelConfig, std::vector<FKNodeRef> &nodes)
{
	footRadius =modelConfig->footRadius;
	distToFoot = vec4(0, -modelConfig->underLegLength + modelConfig->footRadius, 0.f, 1.f);
	float  PI = glm::pi<float>();
	hipOffsetZFlip = 1;
	if (pos.x < 0 && pos.z>0)hipOffsetZFlip = -1;
	if (pos.x > 0 && pos.z<0)hipOffsetZFlip = -1;


	if (hipOffsetZFlip == 1)
	{
		hip1 = FKNode::create(name + "hip1", "hip1_mirror");
	}
	if (hipOffsetZFlip == -1)
	{
		hip1 = FKNode::create(name + "hip1", "hip1");
	}
	float hip1Rot = 0;
	if (pos.x < 0)hip1Rot = PI;
	hip1->setBase(pos,  vec3(0,hip1Rot,0));

	body->addChild(hip1);

	

	hip2 = FKNode::create(name+"hip2", "hip2");
	hip2->setBase(vec3(modelConfig->hipOffsetX,0 , modelConfig->hipOffsetZ*hipOffsetZFlip),vec3(0, -PI/2* hipOffsetZFlip,0));
	hip1->addChild(hip2);

	knee = FKNode::create(name+"knee", "knee");
	knee->setBase(vec3(0, -modelConfig->upperLegLength, 0), vec3(0, 0, 0));
	hip2->addChild(knee);


	nodes.push_back(hip1);
	nodes.push_back(hip2);
	nodes.push_back(knee);
}

ci::vec3 FKLeg::getBallPos() 
{
	

	vec4 ballPos = knee->globalMatrix * distToFoot;
	
	return vec3(ballPos.x, ballPos.y- footRadius, ballPos.z);

}