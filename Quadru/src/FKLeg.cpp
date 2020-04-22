#include "FKLeg.h"
using namespace ci;
using namespace ci::app;
using namespace std;
FKLegRef FKLeg::create()
{
	FKLegRef ref = std::make_shared<FKLeg>();
	return ref;
}

void FKLeg::setup(string name,FKNodeRef body, glm::vec3 pos, ModelConfigRef modelConfig, std::vector<FKNodeRef> &nodes, btMultiBody* multiBody, int linkIndex)
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
	body->update();
	/////////////////////////////////////////////////////


	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = 1.6;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;
		c = glm::rotate(c, hip1Rot, vec3(0, 1, 0));
		btVector3 hingeJointAxis(1, 0, 0);
		btVector3 parentComToCurrentPivot(pos.x / 1000.f, pos.y / 1000.f, pos.z / 1000.f);
		vec3 com =hip1->nodeData->centerOfMass;
		btVector3 currentPivotToCurrentCom(com.x/ 1000.f, com.y / 1000.f, com.z /  1000.f);


		multiBody->setupRevolute(linkIndex, linkMass, linkInertiaDiag, -1,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}
	///////////////////////////////////////////////////
	hip2 = FKNode::create(name+"hip2", "hip2");
	hip2->setBase(vec3(modelConfig->hipOffsetX,0 , modelConfig->hipOffsetZ*hipOffsetZFlip),vec3(0, -PI/2* hipOffsetZFlip,0));
	hip1->addChild(hip2);
	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = 1.6;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;
		c = glm::rotate(c, -PI / 2 * hipOffsetZFlip, vec3(0, 1, 0));
		btVector3 hingeJointAxis(-1, 0, 0);
		vec3 com1 = hip1->nodeData->centerOfMass;
		vec3 comAdj =( vec3(modelConfig->hipOffsetX, 0, modelConfig->hipOffsetZ * hipOffsetZFlip) - com1);

		btVector3 parentComToCurrentPivot(comAdj.x / 1000.f, comAdj.y / 1000.f, comAdj.z / 1000.f);
		
		vec3 com2 = hip2->nodeData->centerOfMass;
		btVector3 currentPivotToCurrentCom(com2.x / 1000.f, com2.y / 1000.f, com2.z / 1000.f);


		multiBody->setupRevolute(linkIndex+1, linkMass, linkInertiaDiag, linkIndex,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}
	///////////////////////////////////////////////////



	knee = FKNode::create(name+"knee", "knee");
	knee->setBase(vec3(0, -modelConfig->upperLegLength, 0), vec3(0, 0, 0));
	hip2->addChild(knee);

	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = 0.6;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;
		//c = glm::rotate(c, -PI / 2 * hipOffsetZFlip, vec3(0, 1, 0));
		btVector3 hingeJointAxis(-1, 0, 0);
		vec3 com1 = hip2->nodeData->centerOfMass;
	
		com1.y = (modelConfig->upperLegLength+ com1.y)*-1;
		

		btVector3 parentComToCurrentPivot(com1.x / 1000.f, com1.y / 1000.f, com1.z / 1000.f);

		vec3 com2 = knee->nodeData->centerOfMass;
		btVector3 currentPivotToCurrentCom(com2.x / 1000.f, com2.y / 1000.f, com2.z / 1000.f);


		multiBody->setupRevolute(linkIndex + 2, linkMass, linkInertiaDiag, linkIndex+1,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}

	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = 0.2;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;
		
		vec3 com1 = vec3();

		com1.y =( modelConfig->upperLegLength+ knee->nodeData->centerOfMass.y - modelConfig->footRadius)*-1;


		btVector3 parentComToCurrentPivot(com1.x / 1000.f, com1.y / 1000.f, com1.z / 1000.f);

		vec3 com2 = knee->nodeData->centerOfMass;
		btVector3 currentPivotToCurrentCom(0, 0, 0);


		multiBody->setupFixed(linkIndex + 3, linkMass, linkInertiaDiag, linkIndex + 2,
			btQuaternion(c.x, c.y, c.z, c.w),
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}

	nodes.push_back(hip1);
	nodes.push_back(hip2);
	nodes.push_back(knee);
	////////////////////////////////////////////


	



}

ci::vec3 FKLeg::getBallPos() 
{
	

	vec4 ballPos = knee->globalMatrix * distToFoot;
	
	return vec3(ballPos.x, ballPos.y- footRadius, ballPos.z);

}