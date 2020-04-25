#include "PathPlanner.h"
#include "cinder/gl/gl.h"
#include "CinderImGui.h"



using namespace ci;
using namespace ci::app;
using namespace std;


void PathPlanner::drawGui() 
{
	ui::ScopedWindow window("Walking Path");
	ui::Checkbox("debugMode", &debugMode);
	if (debugMode) 
	{
	
		if(ui::DragFloat("stepDist", &dStepDistance))isDirty = true;
		if(ui::DragFloat("stepHeight", &dStepHeight))isDirty =true;

		if (ui::Checkbox("startWalk", &startWalk)) { isDirty = true; stopWalk = false; };
		if (ui::Checkbox("stopWalk", &stopWalk)) { isDirty = true; startWalk = false;};


		if (ui::DragFloat("stepTime", &dStepTime,0.01,0.1,1)) {

			dDebugSteps = dStepTime/ (1.f / 120.f);
			isDirty = true;
		
		};
		string stepText = "steps " + to_string(dDebugSteps);
		ui::Text(stepText.c_str());
		if (ui::Checkbox("linearMode", &linear)) { isDirty = true; };
		
		if (ui::DragFloat("slowDown", &slowDown, 1, 1, 100))isDirty ;
		ui::Separator();
		if (ui::DragFloat("walkRisingIn", &walkRisingIn,0.01,0,1))isDirty = true;
		if (ui::DragFloat("walkRisingOut", &walkRisingOut, 0.01, 0, 1))isDirty = true;
		if (ui::DragFloat("walkRisingMidX", &walkRisingMidX, 0.01, 0, 1))isDirty = true;
		if (ui::DragFloat("walkRisingMidY", &walkRisingMidY, 0.01, 0, 1))isDirty = true;

		ui::Separator();
		if (ui::DragFloat("walkFalingIn", &walkFalingIn, 0.01, 0, 1))isDirty = true;
		if (ui::DragFloat("walkFalingOut", &walkFalingOut, 0.01, 0, 1))isDirty = true;
		if (ui::DragFloat("walkFalingMidX", &walkFalingMidX, 0.01, 0, 1))isDirty = true;
		if (ui::DragFloat("walkFalingMidY", &walkFalingMidY, 0.01, 0, 1))isDirty = true;
	}
	


}

void PathPlanner::updateDebugPaths() 
{
	float dStepDistanceL = dStepDistance;
	float dStepDistanceR = dStepDistance;
	if (startWalk)dStepDistanceL = 0;
	if (stopWalk)dStepDistanceR = 0;
	fullPath.clear();
	if (linear) {
		dPathRising = getPathWalkRisingL(dStepDistanceL, dStepHeight, dDebugSteps);
		dPathFaling = getPathWalkFalingL(dStepDistanceR, dStepHeight, dDebugSteps);
	}
	else {

		dPathRising = getPathWalkRising(dStepDistanceL, dStepHeight, dDebugSteps);
		dPathFaling = getPathWalkFaling(dStepDistanceR, dStepHeight, dDebugSteps);
	
	}

		dPathHome = getPathWalkHome(dStepDistanceR, dStepHeight, dDebugSteps);
		dPathStep = getPathWalkStep(dStepDistanceL, dStepHeight, dDebugSteps);
	
	fullPath.insert(fullPath.end(), dPathRising.begin(), dPathRising.end());
	fullPath.insert(fullPath.end(), dPathFaling.begin(),dPathFaling.end());
	fullPath.insert(fullPath.end(), dPathHome.begin(), dPathHome.end());
	fullPath.insert(fullPath.end(), dPathStep.begin(), dPathStep.end());
}

std::vector<ci::vec2> PathPlanner::getPathWalkHome(float stepDistance, float stepHeight, int numSteps) 
{
	vector<vec2> a;


	for (int i = 0; i < numSteps; i++)
	{
		a.push_back(vec2((stepDistance / 2) - ((stepDistance / 2 /numSteps)* (float)i), 0));
	}
	return a;

}


std::vector<ci::vec2> PathPlanner::getPathWalkStep(float stepDistance, float stepHeight, int numSteps) 
{
	vector<vec2> a;


	for (int i = 0; i < numSteps; i++)
	{
		a.push_back(vec2( (-stepDistance/2/ numSteps) * (float)i, 0));
	}
	return a;
}




vector<vec2> PathPlanner::getPathWalkRising(float stepDistance, float stepHeight, int numSteps)
{
	vector<vec2> a;
	vector<vec2>		mPoints;

	mPoints.push_back(vec2(-stepDistance / 2, 0));
	mPoints.push_back(vec2(-stepDistance / 2 - stepDistance* walkRisingIn, 0));
	mPoints.push_back(vec2(-stepDistance*walkRisingMidX, -stepHeight*walkRisingMidY));
	mPoints.push_back(vec2(-stepHeight * walkRisingOut, -stepHeight));
	mPoints.push_back(vec2(0, -stepHeight));

	


	BSpline2f spline(mPoints, 3, false, true);
	float totalLength = spline.getLength(0, 1);
	float totalFlatdistance = stepDistance / 2;
	float startDistance = stepDistance / 2 / numSteps;

	float lengthDif = totalLength - totalFlatdistance;

	//1+2+3+4+.. =(n*(n+1))/2
	float d = (numSteps * (numSteps + 1)) / 2;
	float adj = lengthDif / d;



	float posTime = 0;
	for (int i = 0; i < numSteps; i++)
	{
		
		float ti = spline.getTime(posTime);
		posTime += startDistance + (i+1) * adj;
		a.push_back(spline.getPosition(ti));
	}
	return a;

}
vector<vec2> PathPlanner::getPathWalkFaling(float stepDistance, float stepHeight, int numSteps)
{
	vector<vec2> a;
	vector<vec2>		mPoints;

	mPoints.push_back(vec2(0, -stepHeight));
	mPoints.push_back(vec2(stepHeight * walkFalingOut, -stepHeight));
	mPoints.push_back(vec2(stepDistance * walkFalingMidX, -stepHeight * walkFalingMidY));
	mPoints.push_back(vec2(stepDistance / 2 + stepDistance * walkFalingIn, 0));
	mPoints.push_back(vec2(stepDistance / 2, 0));
	
	BSpline2f spline(mPoints, 3, false, true);
	float totalLength = spline.getLength(0, 1);
	float totalFlatdistance = stepDistance / 2;
	float startDistance = stepDistance / 2 / numSteps;

	float lengthDif = totalLength - totalFlatdistance;

	//1+2+3+4+.. =(n*(n+1))/2
	float d = (numSteps * (numSteps + 1)) / 2;
	float adj = lengthDif / d;
	float posTime = 0;



	

	for (int i = 0; i < numSteps; i++)
	{
		float ti = spline.getTime(posTime);
		posTime += startDistance + (numSteps-i ) * adj;
		a.push_back(spline.getPosition(ti));

	}
	return a;
}
void PathPlanner::draw() 
{
	
	if (debugMode) {
		

		if (isDirty) 
		{
			updateDebugPaths();

			isDirty = false;
		}
		gl::clear(GL_DEPTH_BUFFER_BIT);
	
		gl::color(ColorA(0, 0, 0, 0.8));
		gl::drawSolidRect(Rectf(getWindowBounds()));
		gl::pushMatrices();
	
		gl::translate(getWindowWidth() / 2, getWindowHeight() / 2);
		gl::scale(4, 4);


		gl::color(Color::gray(0.1));
		drawVector(fullPath);
		if (getElapsedFrames() % (int)slowDown == 0) {
			stepCount++;
		}
		stepCount %= fullPath.size();

		float gray = 0.4;
		gl::color(Color::gray(gray));
		for (int i = 0; i < fullPath.size();i++) {
			if (i == stepCount) 
			{
				gl::color(Color(1,1,1));
				gl::drawSolidCircle(fullPath[i], 2, 16);
				gl::color(Color::gray(gray));
			}
			else 
			{
			
				gl::drawSolidCircle(fullPath[i], 1, 8);
			}
			
		}
		
		gl::popMatrices();
		
	


	gl::pushMatrices();
	float w = 500.f / fullPath.size();
	gl::translate(getWindowWidth() / 2-500, getWindowHeight() / 2 + 400);
	gl::begin(GL_LINE_STRIP);
	for (int i = 0; i < fullPath.size()-1; i++) {
		auto pos1 = fullPath[i];
		auto pos2 = fullPath[i+1];
		float d =glm::distance(pos1, pos2);
		gl::vertex(vec2(i*w,-d*20));
	}
	for (int i = 0; i < fullPath.size() - 1; i++) {
		auto pos1 = fullPath[i];
		auto pos2 = fullPath[i + 1];
		float d = glm::distance(pos1, pos2);
		gl::vertex(vec2((i+ fullPath.size()) * w, -d * 20));
	}
	gl::end();


	auto pos1 = fullPath[stepCount];
	int stepCountM = (stepCount + 1)%fullPath.size();
	auto pos2 = fullPath[stepCountM];
	float d = glm::distance(pos1, pos2);
	gl::color(Color(1, 1, 1));
	gl::drawSolidCircle(vec2(stepCount * w, -d * 20), 4, 16);
	gl::drawSolidCircle(vec2((stepCount + fullPath.size()) * w, -d * 20), 4, 16);
	gl::color(Color::gray(1));

	gl::popMatrices();

	}
}
void PathPlanner::drawVector(vector<vec2>& path) 
{
	gl::begin(GL_LINE_STRIP);
	for (auto v : path) {
		gl::vertex(v);
	}
	gl::end();

}




///linear


vector<vec2> PathPlanner::getPathWalkRisingL(float stepDistance, float stepHeight, int numSteps)
{
	vector<vec2> a;
	vector<vec2>		mPoints;

	mPoints.push_back(vec2(-stepDistance / 2, 0));
	mPoints.push_back(vec2(-stepDistance / 2 - stepDistance * walkRisingIn, 0));
	mPoints.push_back(vec2(-stepDistance * walkRisingMidX, -stepHeight * walkRisingMidY));
	mPoints.push_back(vec2(-stepHeight * walkRisingOut, -stepHeight));
	mPoints.push_back(vec2(0, -stepHeight));

	BSpline2f spline(mPoints, 3, false, true);
	float l = spline.getLength(0, 1);
	float t = l / numSteps;

	for (int i = 0; i < numSteps; i++)
	{
		float ti = spline.getTime(t * i);
		a.push_back(spline.getPosition(ti));
	}
	return a;

}
vector<vec2> PathPlanner::getPathWalkFalingL(float stepDistance, float stepHeight, int numSteps)
{
	vector<vec2> a;
	vector<vec2>		mPoints;

	mPoints.push_back(vec2(0, -stepHeight));
	mPoints.push_back(vec2(stepHeight * walkFalingOut, -stepHeight));
	mPoints.push_back(vec2(stepDistance * walkFalingMidX, -stepHeight * walkFalingMidY));
	mPoints.push_back(vec2(stepDistance / 2 + stepDistance * walkFalingIn, 0));
	mPoints.push_back(vec2(stepDistance / 2, 0));

	BSpline2f spline(mPoints, 3, false, true);
	float l = spline.getLength(0, 1);
	float t = l / numSteps;

	for (int i = 0; i < numSteps; i++)
	{
		float ti = spline.getTime(t * i);
		a.push_back(spline.getPosition(ti));

	}
	return a;
}