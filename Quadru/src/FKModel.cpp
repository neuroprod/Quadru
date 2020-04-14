#include "FKModel.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"
#include "NodeDataPool.h"
using namespace ci;
using namespace ci::app;
using namespace std;



void FKModel::setup(ModelConfigRef config) {

	modelConfig = config;
	root = FKNode::create("root","root");


	rebuild();
}
void FKModel::update() 
{
	if (modelConfig->needsRebuild)
	{
		rebuild();
	}







	root->update();
}
void FKModel::rebuild()
{
	NDP()->clear();
	nodes.clear();
	legs.clear();
	root->removeAllChildren();

	body = FKNode::create("body", "body");
	body->setBase(vec3(0, 0, 0));
	nodes.push_back(body);
	root->addChild(body);

	FRLeg = FKLeg::create();
	FRLeg->setup("FR",body, vec3(modelConfig->bodyLength / 2, 0, modelConfig->bodyWidth / 2), modelConfig, nodes);
	legs.push_back(FRLeg);

	FLLeg = FKLeg::create();
	FLLeg->setup("FL", body, vec3(modelConfig->bodyLength / 2, 0, -modelConfig->bodyWidth / 2), modelConfig, nodes);
	legs.push_back(FLLeg);

	BRLeg = FKLeg::create();
	BRLeg->setup("BR", body, vec3(-modelConfig->bodyLength / 2, 0, modelConfig->bodyWidth / 2), modelConfig, nodes);
	legs.push_back(BRLeg);

	BLLeg = FKLeg::create();
	BLLeg->setup("BL", body, vec3(-modelConfig->bodyLength / 2, 0, -modelConfig->bodyWidth / 2), modelConfig, nodes);
	legs.push_back(BLLeg);
}

