#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "OrbitCamera.h"
#include "FKModel.h"
#include "IKModel.h"
#include "Controle.h"
#include "SymbolBatches.h"

class SRenderer
{


public:
	SRenderer() {}
	void setup(FKModelRef _model, ControleRef _control, IKModelRef _IKmodel);
	void update();
	void draw();
	void drawGui(float fps);
	void startCamera();
	void stopCamera();
	void drawShadow();
	
	FKModelRef model;
	ControleRef controle;
	IKModelRef IKmodel;

	SymbolBatches symbols;
	OrbitCamera camera;
	

	ci::gl::FboRef			mFbo;
	ci::CameraPersp			mLightCam;
	ci::vec3				mLightPos;
	ci::gl::GlslProgRef		mGlsl;
	ci::gl::Texture2dRef	mShadowMapTex;
	int	fboSize = 2048;


	bool showMass = true;
	bool showMesh = true;
	bool showFloor = true;
	bool showJointSpace = true;

	bool showHomePos = false;

	bool showTargetPos = true;
};