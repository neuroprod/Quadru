#include "SRenderer.h"

using namespace ci;
using namespace ci::app;
using namespace std;


void SRenderer::setup(FKModelRef _model)
{
	model = _model;
	camera.setup();
	

}
void SRenderer::update() {

	camera.update();


}
void SRenderer::drawGui() {




}
////
void SRenderer::draw() {

	startCamera();
	for (auto n : model->nodes) 
	{
		gl::pushMatrices();
		gl::setModelMatrix(n->globalMatrix);
		gl::drawCoordinateFrame(50, 0, 0);
		gl::popMatrices();
	
	}







	stopCamera();


}

void SRenderer::startCamera() {

	gl::pushMatrices();
	gl::setMatrices(camera.mCam);
}

void SRenderer::stopCamera() {

	gl::popMatrices();
	
}

