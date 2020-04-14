#include "SRenderer.h"
#include "NodeDataPool.h"
#include "CinderImGui.h"
using namespace ci;
using namespace ci::app;
using namespace std;


void SRenderer::setup(FKModelRef _model,ControleRef _controle,IKModelRef _IKmodel)
{
	model = _model;
	controle = _controle;
	IKmodel = _IKmodel;
	symbols.setup();
	camera.setup();
	
	gl::Texture2d::Format depthFormat;
	depthFormat.setInternalFormat(GL_DEPTH_COMPONENT32F);
	depthFormat.setCompareMode(GL_COMPARE_REF_TO_TEXTURE);
	depthFormat.setMagFilter(GL_LINEAR);
	depthFormat.setMinFilter(GL_LINEAR);
	depthFormat.setWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	depthFormat.setCompareFunc(GL_LEQUAL);
	mShadowMapTex = gl::Texture2d::create(fboSize, fboSize, depthFormat);

	gl::Fbo::Format fboFormat;
	fboFormat.attachment(GL_DEPTH_ATTACHMENT, mShadowMapTex);
	mFbo = gl::Fbo::create(fboSize, fboSize, fboFormat);

	mLightPos = vec3(-1000.0f, 2000.0f, -1500.0f);
	mLightCam.setPerspective(60.0f, mFbo->getAspectRatio(), 10.f, 5000.0f);
	mLightCam.lookAt(mLightPos, vec3(0.0f));


	gl::enableDepthRead();
	gl::enableDepthWrite();
}
void SRenderer::update() {

	camera.update();


}
void SRenderer::drawGui(float fps) {


	ui::ScopedWindow window("Renderer");
	string fpss = to_string(fps) + "fps";
	ui::Text(fpss.c_str());

	ui::Checkbox("show Mesh", &showMesh);
	ui::Checkbox("show Floor", &showFloor);

	ui::Checkbox("show JointSpace", &showJointSpace);
	ui::Checkbox("show HomePos", &showHomePos);
	ui::Checkbox("show TargetPos", &showTargetPos);



}
////
void SRenderer::draw() {


	drawShadow();

	startCamera();
	gl::drawCoordinateFrame(1000);
	//hip1 resolve	
	/*for (auto l : IKmodel->legs)
		{
			gl::pushMatrices();
			gl::translate(l->targetHip1LocalFlat);
			symbols.targetBatch->draw();
			gl::popMatrices();

		}
	*/

	//hip2_Knee resolve	
	for (auto l : IKmodel->legs)
	{
	gl::pushMatrices();
	gl::translate(vec3(l->targetHip2Local));
	symbols.targetBatch->draw();
	gl::popMatrices();

	}
	

	//////////////////////home
	if (showHomePos) {
		for (auto l : controle->legs)
		{
			gl::pushMatrices();
			gl::translate(l->homePos);
			symbols.homeBatch->draw();
			gl::popMatrices();

		}
	}
	//////////////////////target
	if (showTargetPos) {
		for (auto l : controle->legs)
		{
			gl::pushMatrices();
			gl::translate(l->targetPos);
			symbols.targetBatch->draw();
			gl::popMatrices();

		}
	}


	//////////////////////nodes
	if (showJointSpace) {
		for (auto n : model->nodes)
		{
			gl::pushMatrices();
			gl::setModelMatrix(n->globalMatrix);
			symbols.coordinateFrame->draw();
			gl::popMatrices();

		}
	}
	//////////////////////mesh
	if (showMesh || showFloor) {
		gl::ScopedTextureBind texScope(mShadowMapTex, (uint8_t)0);
		vec3 mvLightPos = vec3(gl::getModelView() * vec4(mLightPos, 1.0f));
		mat4 shadowMatrix = mLightCam.getProjectionMatrix() * mLightCam.getViewMatrix();


		NDP()->mGlsl->uniform("uShadowMap", 0);
		NDP()->mGlsl->uniform("uLightPos", mvLightPos);
		NDP()->mGlsl->uniform("uShadowMatrix", shadowMatrix);
		NDP()->mGlsl->uniform("alpha", 1.f);
		if (showFloor) {
			gl::color(Color::gray(0.7));
			symbols.floorBatch->draw();
		}
		if (showMesh) {
			for (auto n : model->nodes)
			{
				gl::pushMatrices();
				gl::setModelMatrix(n->globalMatrix);
				for (auto m : n->nodeData->meshes)
				{
					m->draw();
				}
				gl::popMatrices();

			}
		}

	}



	stopCamera();


}
void SRenderer::drawShadow() 
{
	if (!showMesh && !showFloor) return;
	gl::pushMatrices();
	gl::enable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0f, 2.0f);

	gl::ScopedFramebuffer fbo(mFbo);
	gl::ScopedViewport viewport(vec2(0.0f), mFbo->getSize());
	gl::clear(Color::black());
	
	if (showMesh) {
		gl::color(Color::white());
		gl::setMatrices(mLightCam);



		for (auto n : model->nodes)
		{
			gl::pushMatrices();
			gl::setModelMatrix(n->globalMatrix);
			for (auto m : n->nodeData->meshes)
			{
				m->drawShadow();
			}
			gl::popMatrices();

		}
	}

	gl::disable(GL_POLYGON_OFFSET_FILL);

	gl::popMatrices();


}
void SRenderer::startCamera() {

	gl::pushMatrices();
	gl::setMatrices(camera.mCam);
}

void SRenderer::stopCamera() {

	gl::popMatrices();
	
}

