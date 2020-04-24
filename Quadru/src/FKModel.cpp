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

/*
void FKModel::setIKModel(IKModelRef model)
{
	body->baseMatrix = model->bodyMatrix;
	for (int i = 0; i < model->legs.size(); i++)
	{
		auto IKleg = model->legs[i];
		auto FKleg = legs[i];

		FKleg->hip1->setRotation(IKleg->angleHip1);
		FKleg->hip2->setRotation(IKleg->angleHip2);
		FKleg->knee->setRotation(IKleg->angleKnee);
	}


}
void FKModel::setPhysicsModel(PhysicsModelRef model) 
{
	int p = 0;
	auto mMultiBody = model->mMultiBody;
	body->baseMatrix = Conv::to(mMultiBody->getBaseWorldTransform());



	legs[0]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[0]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[0]->knee->setRotation(mMultiBody->getJointPos(p++));
	p++;
	legs[1]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[1]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[1]->knee->setRotation(mMultiBody->getJointPos(p++));
	p++;
	legs[2]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[2]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[2]->knee->setRotation(mMultiBody->getJointPos(p++));
	p++;
	legs[3]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[3]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[3]->knee->setRotation(mMultiBody->getJointPos(p++));


	btVector3 pos = mMultiBody->getBaseWorldTransform().getOrigin();


}

*/
void FKModel::update() 
{
	/*
	if (!world->hasUpdate)return;
	
	int p = 0;
	body->baseMatrix = Conv::to(mMultiBody->getBaseWorldTransform());

	

	legs[0]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[0]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[0]->knee->setRotation(mMultiBody->getJointPos(p++));
	p++;
	legs[1]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[1]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[1]->knee->setRotation(mMultiBody->getJointPos(p++));
	p++;
	legs[2]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[2]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[2]->knee->setRotation(mMultiBody->getJointPos(p++));
	p++;
	legs[3]->hip1->setRotation(mMultiBody->getJointPos(p++));
	legs[3]->hip2->setRotation(mMultiBody->getJointPos(p++));
	legs[3]->knee->setRotation(mMultiBody->getJointPos(p++));

	
	btVector3 pos  =mMultiBody->getBaseWorldTransform().getOrigin();
	bodyPos.x = pos.getX()*1000.f;
	bodyPos.y = pos.getY() * 1000.f;
	bodyPos.z = pos.getZ() * 1000.f;
	btScalar rZ,rY,rX;
	mMultiBody->getBaseWorldTransform().getRotation().getEulerZYX(rZ,rY,rX);
	rotX = rX;
	rotY = rY;
	rotZ = rZ;
	*/
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

