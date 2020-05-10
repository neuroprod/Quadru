#include "QuadruDefines.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"
#include "SRenderer.h"
#include "FKModel.h"
#include "ModelConfig.h"
#include "MeshDataPool.h"
#include "Controle.h"
#include "IKModel.h"
#include "WalkControle.h"
#include "PhysicsWorld.h"
#include "PhysicsModel.h"
#include "AppSettings.h"
#include "PathPlanner.h"
#include "TorqueGraph.h"
#include "MotorControl.h"
#ifdef CONNECT_TO_ROBOT  //QuadruDefines.h
#include "IMU.h"
#endif

using namespace ci;
using namespace ci::app;
using namespace std;

class QuadruApp : public App {
  public:
	void setup() override;

	void mouseDown(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseWheel(MouseEvent event)override;

	void update() override;
	void draw() override;
	AppSettings appSettings;
	SRenderer renderer;
	FKModelRef fkModel;
	ModelConfigRef modelConfig;
	ControleRef controle;
	WalkControleRef walkControle;
	IKModelRef IKmodel;
	

	PhysicsWorldRef physicsWorld;
	PhysicsModelRef physicsModel;

	PathPlannerRef pathPlaner;
	TorqueGraph torqueGraph;

	MotorControl motorControl;

#ifdef CONNECT_TO_ROBOT
		IMU imu;
#endif
};

void QuadruApp::setup()
{
	setWindowSize(1920, 1080);
	setWindowPos(0, 0);
	gl::enableVerticalSync(false);
	setFrameRate(120);
	ui::initialize();


	modelConfig = ModelConfig::create();
	modelConfig->setup();
	
	MDP()->setup(modelConfig);
	
	physicsWorld = std::make_shared<PhysicsWorld>();
	physicsWorld->setup();
	physicsModel = std::make_shared<PhysicsModel>();
	physicsModel->setup(modelConfig,physicsWorld);


	fkModel = std::make_shared<FKModel>();
	fkModel->setup(modelConfig);


	controle = std::make_shared<Controle>();
	controle->setup(modelConfig);

	IKmodel = std::make_shared< IKModel>();
	IKmodel->setup(modelConfig, controle, fkModel);
	IKmodel->update();
	physicsModel->setDefaultAngles(IKmodel->angles);

	

	
	pathPlaner = std::make_shared< PathPlanner>();



	walkControle = std::make_shared< WalkControle>();
	walkControle->setup(controle, pathPlaner);
	renderer.setup(fkModel, controle, IKmodel);

	motorControl.setup();

#ifdef CONNECT_TO_ROBOT
	imu.start();
#endif
}

void QuadruApp::mouseDown(MouseEvent event)
{
	renderer.camera.mouseDown(event);
}
void  QuadruApp::mouseDrag(MouseEvent event)
{
	renderer.camera.mouseDrag(event);
}
void QuadruApp::mouseUp(MouseEvent event)
{
	renderer.camera.mouseUp(event);
}
void QuadruApp::mouseWheel(MouseEvent event)
{
	renderer.camera.mouseWheel(event);
}
void QuadruApp::update()
{
#ifdef CONNECT_TO_ROBOT
	vec3 e = imu.getEuler();
	console() <<e<< endl;

#endif

	appSettings.drawGui();
	if (appSettings.pathEditor) 
	{
		pathPlaner->drawGui();
	
	}
	else {


		float fps = getAverageFps();
		renderer.drawGui(fps);
		renderer.camera.drawGui();
		modelConfig->drawGui();
		controle->drawGui();
		physicsWorld->drawGui();
		walkControle->drawGui();
		motorControl.setGui();
	}
	

	//console() << fkModel->rotX << " " << fkModel->rotY << " " << fkModel->rotZ << endl;
	//walkControle->update(fkModel->rotX);
	
	walkControle->update(physicsModel->angleX, physicsModel->angleZ);

	controle->update();
	IKmodel->update();


	if (!appSettings.usePhysics) {
	
		fkModel->setPosition(IKmodel->bodyMatrix,IKmodel->angles);
		
	}
	else 
	{
		physicsModel->setMotorTargets( IKmodel->angles);
		
		physicsWorld->update();
		physicsModel->updateData();
		fkModel->setPosition(physicsModel->bodyMatrix, physicsModel->angles);
		torqueGraph.addData(physicsModel->FRLeg->torque, physicsModel->FLLeg->torque, physicsModel->BRLeg->torque, physicsModel->BLLeg->torque,vec3( (float)walkControle->stepCount, (float)walkControle->FRLeg->stepState, walkControle->heightBounce));
	}

	fkModel->update();
	
	renderer.update(physicsModel->bodyPos);
	
}

void QuadruApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	renderer.draw();
	torqueGraph.draw();
	if (appSettings.pathEditor)
	{
		pathPlaner->draw();
	}
}

CINDER_APP(QuadruApp, RendererGl(RendererGl::Options().msaa(16)));
