#include "OrbitCamera.h"
#include "CinderImGui.h"
using namespace ci;
using namespace ci::app;
using namespace std;


void OrbitCamera::setup()
{
	update();
}
void OrbitCamera::drawGui()
{
	ui::ScopedWindow window("camera");

	if (ui::DragFloat("fov", &fov, 1, 5, 170));
	if (ui::DragFloat("theta", &theta, 0.01, 0.001, 3.1415 / 2)) ;
	if (ui::DragFloat("phi", &phi, 0.01, 0, 3.1415*2)) ;
	if (ui::DragFloat("distance", &cameraDistance, 1)) ;


}
void OrbitCamera::update()
{
	
	
	phi += deltaPhi;
	phi = glm::mod(phi, 3.1415f*2);
	theta += deltaTheta;

	theta = glm::clamp(theta, 0.01f, 3.1415f / 2);

	
	float x = cameraDistance * sinf(theta)*cosf(phi);
	float z = cameraDistance * sinf(theta)*sinf(phi);
	float y = cameraDistance * cosf(theta);

	mCam.lookAt(vec3(x, y , z), vec3(0, 0, 0));
	mCam.setPerspective(fov, getWindowAspectRatio(), 20, 10000);

	deltaPhi *= (1 - dampingFactor);
	deltaTheta *= (1 - dampingFactor);
	
	cameraDistance += ( targetCameraDistance- cameraDistance ) *dampingFactor;


}
void OrbitCamera::mouseDown(MouseEvent event)
{
	rotateStart = event.getPos();
}
void  OrbitCamera::mouseDrag(MouseEvent event)
{
	vec2 temp = event.getPos();
	if (temp == rotateEnd)return;
	rotateEnd =  event.getPos();
	
	vec2 rotateDelta = rotateEnd - rotateStart;

	deltaPhi=2 * 3.1415 * rotateDelta.x / 1024.f;
	deltaTheta=-2 * 3.1415 * rotateDelta.y / 1024.f;

	phi += deltaPhi;
	theta += deltaTheta;

	rotateStart = rotateEnd;
	
}
void OrbitCamera::mouseUp(MouseEvent event)
{
	
}
void OrbitCamera::mouseWheel(MouseEvent event)
{
	int inc =  event.getWheelIncrement() ;
	if (inc > 0) 
	{
		targetCameraDistance*=0.9;
	}
	else 
	{
		targetCameraDistance/=0.9;
	}
	
}