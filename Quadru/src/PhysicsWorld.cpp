#include "PhysicsWorld.h"
#include "CinderImGui.h"
#include "Conv.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void PhysicsWorld::setup() {
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();
	m_filterCallback = new MyOverlapFilterCallback2();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_pairCache = new btHashedOverlappingPairCache();

	m_pairCache->setOverlapFilterCallback(m_filterCallback);

	m_broadphase = new btDbvtBroadphase(m_pairCache);  //btSimpleBroadphase();

	m_solver = new btMultiBodyConstraintSolver;

	m_dynamicsWorld = new btMultiBodyDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);

	m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

	m_dynamicsWorld->getSolverInfo().m_jointFeedbackInWorldSpace = true;
	m_dynamicsWorld->getSolverInfo().m_jointFeedbackInJointFrame = true;


	vec3 mSize = vec3(20, 5, 20);
	btCollisionShape* colShape = new btBoxShape(btVector3(mSize.x / 2, mSize.y / 2, mSize.z / 2));
	mat4 m;
	m = glm::translate(m, vec3(0, -2.5, 0));
	/// Create Dynamic Objects
	btTransform startTransform = Conv::to(m);


	btScalar btmass(0);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (btmass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		colShape->calculateLocalInertia(btmass, localInertia);

	btDefaultMotionState* myMotionState;
	btRigidBody* body;
	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(btmass, myMotionState, colShape, localInertia);
	body = new btRigidBody(rbInfo);
	body->setActivationState(DISABLE_DEACTIVATION);

	body->setFriction(1.f);
	m_dynamicsWorld->addRigidBody(body);



};
void PhysicsWorld::update() {
	hasUpdate = false;
	if (!play && !step) return;

	step = false;
	m_dynamicsWorld->stepSimulation(1. / 240, 0);
	hasUpdate = true;
};

void  PhysicsWorld::drawGui()
{
	ui::ScopedWindow window("PhysicsSimulation");

	if (ui::Button("play")) { play = true; } ui::SameLine();
	if (ui::Button("pauze")) { play = false; }ui::SameLine();
	if (ui::Button("step")) { step = true; }ui::SameLine();


	

}