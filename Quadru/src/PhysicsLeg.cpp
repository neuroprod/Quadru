#include "PhysicsLeg.h"
using namespace ci;
using namespace ci::app;
using namespace std;
PhysicsLegRef PhysicsLeg::create()
{
	PhysicsLegRef ref = std::make_shared<PhysicsLeg>();
	return ref;
}
void PhysicsLeg::updateData() 
{
	tHip1 = motorHip1->getAppliedImpulse(0) * 120;
	tHip2 = motorHip2->getAppliedImpulse(0) * 120;
	tKnee = motorKnee->getAppliedImpulse(0) * 120;
	
	torque.x = tHip1;
	torque.y = tHip2;
	torque.z = tKnee;
}
void PhysicsLeg::setup(std::string name, glm::vec3 pos, ModelConfigRef modelConfig, btMultiBody* multiBody, int linkIndex)
{
	
	float  PI = glm::pi<float>();

	float hipOffsetZFlip = 1;
	if (pos.x < 0 && pos.z>0)hipOffsetZFlip = -1;
	if (pos.x > 0 && pos.z < 0)hipOffsetZFlip = -1;

	float hip1Rot = 0;
	if (pos.x < 0)hip1Rot = PI;

	//hip1

	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = modelConfig->hip1Mass;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;
		c = glm::rotate(c, hip1Rot, vec3(0, 1, 0));
		btVector3 hingeJointAxis(1, 0, 0);
		btVector3 parentComToCurrentPivot(pos.x / 1000.f, pos.y / 1000.f, pos.z / 1000.f);
		vec3 com = modelConfig->hip1COM;
		btVector3 currentPivotToCurrentCom(com.x / 1000.f, com.y / 1000.f, com.z / 1000.f);


		multiBody->setupRevolute(linkIndex, linkMass, linkInertiaDiag, -1,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}
	//hip2

	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = modelConfig->hip2Mass;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;
		c = glm::rotate(c, -PI / 2 * hipOffsetZFlip, vec3(0, 1, 0));
		btVector3 hingeJointAxis(-1, 0, 0);
		vec3 com1 = modelConfig->hip1COM;
		vec3 comAdj = (vec3(modelConfig->hipOffsetX, 0, modelConfig->hipOffsetZ * hipOffsetZFlip) - com1);

		btVector3 parentComToCurrentPivot(comAdj.x / 1000.f, comAdj.y / 1000.f, comAdj.z / 1000.f);

		vec3 com2 = modelConfig->hip2COM;
		btVector3 currentPivotToCurrentCom(com2.x / 1000.f, com2.y / 1000.f, com2.z / 1000.f);


		multiBody->setupRevolute(linkIndex + 1, linkMass, linkInertiaDiag, linkIndex,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}


	//knee
	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = modelConfig->kneeMass;;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;
		//c = glm::rotate(c, -PI / 2 * hipOffsetZFlip, vec3(0, 1, 0));
		btVector3 hingeJointAxis(-1, 0, 0);
		vec3 com1 = modelConfig->hip2COM;;

		com1.y = (modelConfig->upperLegLength + com1.y) * -1;


		btVector3 parentComToCurrentPivot(com1.x / 1000.f, com1.y / 1000.f, com1.z / 1000.f);

		vec3 com2 = modelConfig->kneeCOM;
		btVector3 currentPivotToCurrentCom(com2.x / 1000.f, com2.y / 1000.f, com2.z / 1000.f);


		multiBody->setupRevolute(linkIndex + 2, linkMass, linkInertiaDiag, linkIndex + 1,
			btQuaternion(c.x, c.y, c.z, c.w),
			hingeJointAxis,
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}
	///foot
	{
		btVector3 linkInertiaDiag(0.f, 0.f, 0.f);
		btCollisionShape* shape = 0;
		btVector3 linkHalfExtents(0.05, 0.05, 0.05);
		float linkMass = modelConfig->footMass;
		shape = new btBoxShape(btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));  //
		shape->calculateLocalInertia(0.6, linkInertiaDiag);
		delete shape;

		ci::quat c;

		vec3 com1 = vec3();

		com1.y = (modelConfig->upperLegLength + modelConfig->kneeCOM.y - modelConfig->footRadius) * -1;


		btVector3 parentComToCurrentPivot(com1.x / 1000.f, com1.y / 1000.f, com1.z / 1000.f);

		vec3 com2 = modelConfig->kneeCOM;
		btVector3 currentPivotToCurrentCom(0, 0, 0);


		multiBody->setupFixed(linkIndex + 3, linkMass, linkInertiaDiag, linkIndex + 2,
			btQuaternion(c.x, c.y, c.z, c.w),
			parentComToCurrentPivot,
			currentPivotToCurrentCom, false);
	}

	
	////////////////////////////////////////////






}

