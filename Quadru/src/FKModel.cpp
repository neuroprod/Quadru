#include "FKModel.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"
#include "MeshDataPool.h"
#include "Conv.h"

using namespace ci;
using namespace ci::app;
using namespace std;



void FKModel::setup(ModelConfigRef _config) {

	
	config = _config;
	root = FKNode::create("root","root");


	rebuild();
	root->update();
}

void FKModel::setPosition(mat4 bodyMatrix,vector<float> &jointAngles) 
{
	body->baseMatrix = bodyMatrix;
	for (int i = 0; i < legs.size(); i++)
	{
		int index = i * 3;
		auto FKleg = legs[i];

		FKleg->hip1->setRotation(jointAngles[index]);
		FKleg->hip2->setRotation(jointAngles[index+1]);
		FKleg->knee->setRotation(jointAngles[index+2]);
	}
}


void FKModel::update() 
{

	root->update();
}
void FKModel::rebuild()
{



	MDP()->clear();
	nodes.clear();
	legs.clear();
	root->removeAllChildren();
	nodes.push_back(root);

	body = FKNode::create("body", "body");
	body->setBase(vec3(0, 0, 0));
	nodes.push_back(body);
	root->addChild(body);




	FRLeg = FKLeg::create();
	FRLeg->setup("FR",body, vec3(config->bodyLength / 2, 0, config->bodyWidth / 2), config, nodes);
	legs.push_back(FRLeg);

	FLLeg = FKLeg::create();
	FLLeg->setup("FL", body, vec3(config->bodyLength / 2, 0, -config->bodyWidth / 2), config, nodes);
	legs.push_back(FLLeg);

	BRLeg = FKLeg::create();
	BRLeg->setup("BR", body, vec3(-config->bodyLength / 2, 0, config->bodyWidth / 2), config, nodes);
	legs.push_back(BRLeg);

	BLLeg = FKLeg::create();
	BLLeg->setup("BL", body, vec3(-config->bodyLength / 2, 0, -config->bodyWidth / 2), config, nodes);
	legs.push_back(BLLeg);


}

