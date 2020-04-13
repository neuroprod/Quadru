#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
class OrbitCamera
{
public:
	OrbitCamera() {}
	void setup();
	void update();
	void drawGui();
	void mouseDown(ci::app::MouseEvent event) ;
	void mouseDrag(ci::app::MouseEvent event) ;
	void mouseUp(ci::app::MouseEvent event);
	void mouseWheel(ci::app::MouseEvent event);

	ci::CameraPersp	mCam;

	ci::vec2 rotateStart;
	ci::vec2 rotateEnd;
	float cameraDistance = 4000;
	float targetCameraDistance = cameraDistance;
	float dampingFactor = 0.1;

	float phi = -2.72396;
	float theta = 0.700061;
	float fov = 30;
	
	float deltaTheta =0;
	float deltaPhi=0;
};