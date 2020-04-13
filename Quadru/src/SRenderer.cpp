#include "SRenderer.h"
#include "NodeDataPool.h"
using namespace ci;
using namespace ci::app;
using namespace std;


void SRenderer::setup(FKModelRef _model)
{
	model = _model;
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

	mLightPos = vec3(500.0f, 1000.0f, 0.0f);
	mLightCam.setPerspective(60.0f, mFbo->getAspectRatio(), 10.f, 2000.0f);
	mLightCam.lookAt(mLightPos, vec3(0.0f));


	gl::enableDepthRead();
	gl::enableDepthWrite();
}
void SRenderer::update() {

	camera.update();


}
void SRenderer::drawGui() {




}
////
void SRenderer::draw() {


	drawShadow();

	startCamera();
	for (auto n : model->nodes) 
	{
		gl::pushMatrices();
		gl::setModelMatrix(n->globalMatrix);
		gl::drawCoordinateFrame(50, 0, 0);
		gl::popMatrices();
	
	}
	gl::ScopedTextureBind texScope(mShadowMapTex, (uint8_t)0);
	vec3 mvLightPos = vec3(gl::getModelView() * vec4(mLightPos, 1.0f));
	mat4 shadowMatrix = mLightCam.getProjectionMatrix() * mLightCam.getViewMatrix();


	NDP()->mGlsl->uniform("uShadowMap", 0);
	NDP()->mGlsl->uniform("uLightPos", mLightPos);
	NDP()->mGlsl->uniform("uShadowMatrix", shadowMatrix);
	NDP()->mGlsl->uniform("alpha", 1.f);
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






	stopCamera();


}
void SRenderer::drawShadow() 
{
	gl::pushMatrices();
	gl::enable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0f, 2.0f);

	gl::ScopedFramebuffer fbo(mFbo);
	gl::ScopedViewport viewport(vec2(0.0f), mFbo->getSize());
	gl::clear(Color::black());
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

