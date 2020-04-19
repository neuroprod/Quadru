#include "FKModel.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"
#include "NodeDataPool.h"
#include "Conv.h"

using namespace ci;
using namespace ci::app;
using namespace std;



void FKModel::setup(ModelConfigRef _config, PhysicsWorldRef _world) {

	world = _world;
	config = _config;
	root = FKNode::create("root","root");


	rebuild();
}
void FKModel::update() 
{

	if (!world->hasUpdate)return;
	
	
	body->baseMatrix = Conv::to(mMultiBody->getBaseWorldTransform());

	
	root->update();
}
void FKModel::rebuild()
{







	NDP()->clear();
	nodes.clear();
	legs.clear();
	root->removeAllChildren();
	nodes.push_back(root);

	body = FKNode::create("body", "body");
	body->setBase(vec3(0, 0, 0));
	nodes.push_back(body);
	root->addChild(body);

	
	int numLinks = 0;


	btVector3 baseHalfExtents((config->bodyLength - config->motorHeight * 2 - 20)/2000.f, 80.0f / 2000.f, config->bodyWidth / 2000.f);

	btVector3 basePosition = btVector3(0.f, config->bodyY/1000.f, 0.f);

	btVector3 baseInertiaDiag(0.f, 0.f, 0.f);
	float baseMass = body->nodeData->mass;
	if (baseMass)
	{
		//btCollisionShape *shape = new btSphereShape(baseHalfExtents[0]);// btBoxShape(btVector3(baseHalfExtents[0], baseHalfExtents[1], baseHalfExtents[2]));
		btCollisionShape* shape = new btBoxShape(btVector3(baseHalfExtents[0], baseHalfExtents[1], baseHalfExtents[2]));
		shape->calculateLocalInertia(baseMass, baseInertiaDiag);
		delete shape;
	}

	mMultiBody = new btMultiBody(numLinks, baseMass, baseInertiaDiag, false, false);
	btQuaternion baseOriQuat(0.f, 0.f, 0.f, 1.f);
	baseOriQuat.setEulerZYX(0,0,0);
	mMultiBody->setBasePos(basePosition);
	mMultiBody->setWorldToBaseRot(baseOriQuat);





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




	mMultiBody->finalizeMultiDof();
	world->m_dynamicsWorld->addMultiBody(mMultiBody);

	mMultiBody->setCanSleep(false);
	mMultiBody->setHasSelfCollision(false);
	//mbC->setUseGyroTerm(gyro);
	//

	mMultiBody->setLinearDamping(0.1f);
	mMultiBody->setAngularDamping(0.9f);
	btCollisionShape* shape = new btBoxShape(btVector3(baseHalfExtents[0], baseHalfExtents[1], baseHalfExtents[2]));  //new btSphereShape(baseHalfExtents[0]);
	

	btMultiBodyLinkCollider* col = new btMultiBodyLinkCollider(mMultiBody, -1);
	col->setCollisionShape(shape);

	mat4 m = mat4(1);
	m = glm::translate(vec3(0, config->bodyY / 1000.f, 0));
	col->setWorldTransform(Conv::to(m));
	
	
	int collisionFilterGroup =  int(btBroadphaseProxy::DefaultFilter) ;
	int collisionFilterMask =  int(btBroadphaseProxy::AllFilter);

	world->m_dynamicsWorld->addCollisionObject(col, collisionFilterGroup, collisionFilterMask);  //, 2,1+2);


	mMultiBody->setBaseCollider(col);


	
}

