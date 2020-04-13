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

	FKModelRef model;
	OrbitCamera camera;


};