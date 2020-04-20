#include "QuadruDefines.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"
#include "SRenderer.h"
#include "FKModel.h"
#include "ModelConfig.h"
#include "NodeDataPool.h"
#include "Controle.h"
#include "IKModel.h"

#include "PhysicsWorld.h"

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

	SRenderer renderer;
	FKModelRef fkModel;
	ModelConfigRef modelConfig;
	ControleRef controle;

	IKModelRef IKmodel;
	

	PhysicsWorldRef physicsWorld;

#ifdef CONNECT_TO_ROBOT
		IMU imu;
#endif
};

void QuadruApp::setup()
{
	setWindowSize(1920, 1080);
	setWindowPos(0, 0);
	gl::enableVerticalSync(true);
	setFrameRate(60);
	ui::initialize();
	ui::GetStyle().WindowRounding = 0.0f;
	ui::GetStyle().ChildRounding = 0.0f;
	ui::GetStyle().FrameRounding = 0.0f;
	ui::GetStyle().GrabRounding = 0.0f;
	ui::GetStyle().PopupRounding = 0.0f;
	ui::GetStyle().ScrollbarRounding = 0.0f;



	modelConfig = ModelConfig::create();
	modelConfig->setup();
	
	NDP()->setup(modelConfig);
	
	physicsWorld = std::make_shared<PhysicsWorld>();
	physicsWorld->setup();

	fkModel = std::make_shared<FKModel>();
	fkModel->setup(modelConfig, physicsWorld);


	controle = std::make_shared<Controle>();
	controle->setup(modelConfig);

	IKmodel = std::make_shared< IKModel>();
	IKmodel->setup(modelConfig, controle, fkModel);
	IKmodel->update();
	for (int i = 0; i < IKmodel->legs.size(); i++)
	{
		auto IKleg = IKmodel->legs[i];
		 fkModel->mMultiBody->setJointPos(i*4, IKleg->angleHip1);
		 fkModel->mMultiBody->setJointPos(i * 4+1, IKleg->angleHip2);
		 fkModel->mMultiBody->setJointPos(i * 4+2, IKleg->angleKnee);
		
	}

	IKmodel->update();

	renderer.setup(fkModel, controle, IKmodel);

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
	float fps = getAverageFps();
	renderer.drawGui(fps);
	renderer.camera.drawGui();
	modelConfig->drawGui();
	controle->drawGui();
	physicsWorld->drawGui();


	controle->update();
	IKmodel->update();

	/*
	fkModel->body->baseMatrix = IKmodel->bodyMatrix;
	for (int i = 0; i < IKmodel->legs.size() ; i++) 
	{
		auto IKleg = IKmodel->legs[i];
		auto FKleg = fkModel->legs[i];

		FKleg->hip1->setRotation(IKleg->angleHip1);
		FKleg->hip2->setRotation(IKleg->angleHip2);
		FKleg->knee->setRotation(IKleg->angleKnee);
	}




	*/
	float kp = 1.f;


	for (int i = 0; i < IKmodel->legs.size(); i++)
	{
		auto IKleg = IKmodel->legs[i];
		auto FKleg = fkModel->legs[i];
		
		//FKleg->motorHip1->setVelocityTarget(10.f, 1.f);µ
		int in = i * 4;

		/*fkModel->mMultiBody->setJointPos(in, IKmodel->legs[0]->angleHip1);
		fkModel->mMultiBody->setJointPos(in+1, IKmodel->legs[0]->angleHip2);
		fkModel->mMultiBody->setJointPos(in+2, IKmodel->legs[0]->angleKnee);
		*/
		FKleg->motorHip1->setPositionTarget(IKleg->angleHip1,kp);
		FKleg->motorHip2->setPositionTarget(IKleg->angleHip2,kp);
		FKleg->motorKnee->setPositionTarget(IKleg->angleKnee,kp);
		
	
	}
	
	physicsWorld->update();



	fkModel->update();
	


	renderer.update();


	
}

void QuadruApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	renderer.draw();
	
}

CINDER_APP(QuadruApp, RendererGl(RendererGl::Options().msaa(16)));
