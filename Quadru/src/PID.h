#pragma once
#include "cinder/app/App.h"
class PID 
{
public:
    PID() {};
    float calculate(float target,float current);
    void drawGui();
	float dt = 1.0f/120.f;
	float max =20;
	float min = -20;
	float Kp =55;
	float Ki = 0.0;
	float Kd =1.4;
	float error = 0;;
	float pre_error = 0;
	float integral = 0;
	bool inv = false;
	std::vector<float> errors;
};