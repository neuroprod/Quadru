#pragma once
#include "cinder/app/App.h"
class PID 
{
public:
    PID() {};
    float calculate(float target,float current);
    void drawGui();
	float dt = 1.0f/120.f;
	float max = 50;
	float min = -10;
	float Kp =500;
	float Ki = 0.0;
	float Kd =0;
	float error = 0;;
	float pre_error = 0;
	float integral = 0;
	std::vector<float> errors;
};