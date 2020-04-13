#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "OrbitCamera.h"
#include "FKModel.h"
class SRenderer
{


public:
	SRenderer() {}
	void setup(FKModelRef _model );
	void update();
	void draw();
	void drawGui();
	void startCamera();
	void stopCamera();
	void drawShadow();
	FKModelRef model;
	OrbitCamera camera;

	ci::gl::FboRef			mFbo;
	ci::CameraPersp			mLightCam;
	ci::vec3				mLightPos;
	ci::gl::GlslProgRef		mGlsl;
	ci::gl::Texture2dRef	mShadowMapTex;
	int	fboSize = 2048;
};