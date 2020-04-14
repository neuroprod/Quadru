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
};

void QuadruApp::setup()
{
	setWindowSize(1920, 1080);
	setWindowPos(0, 0);
	gl::enableVerticalSync(false);
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
	

	fkModel = std::make_shared<FKModel>();
	fkModel->setup(modelConfig);


	controle = std::make_shared<Controle>();
	controle->setup(modelConfig);

	IKmodel = std::make_shared< IKModel>();
	IKmodel->setup(modelConfig, controle);



	renderer.setup(fkModel, controle, IKmodel);
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
	controle->update();
	IKmodel->update();


	fkModel->body->baseMatrix = IKmodel->bodyMatrix;
	for (int i = 0; i < IKmodel->legs.size() ; i++) 
	{
		auto IKleg = IKmodel->legs[i];
		auto FKleg = fkModel->legs[i];

		FKleg->hip1->setRotation(IKleg->angleHip1);
		FKleg->hip2->setRotation(IKleg->angleHip2);
		FKleg->knee->setRotation(IKleg->angleKnee);
	}


	float fps = getAverageFps();
	//console() << fps << endl;

	fkModel->update();
	renderer.update();


	renderer.drawGui(fps);
	renderer.camera.drawGui();
	modelConfig->drawGui();
	controle->drawGui();
}

void QuadruApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	renderer.draw();
	
}

CINDER_APP(QuadruApp, RendererGl(RendererGl::Options().msaa(16)));
