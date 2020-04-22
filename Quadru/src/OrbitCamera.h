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
	void setBodyPos(ci::vec3 pos);



	ci::CameraPersp	mCam;

	ci::vec2 rotateStart;
	ci::vec2 rotateEnd;
	float cameraDistance = 2360;
	float targetCameraDistance = cameraDistance;
	float dampingFactor = 0.1;

	float phi = 0.891;
	float theta = 1.162;
	float fov = 30;
	
	float deltaTheta =0;
	float deltaPhi=0;

	ci::vec3 targetPos =ci::vec3(0,0,0);
	ci::vec3 offsetPos = ci::vec3(0, 0, 0);
};