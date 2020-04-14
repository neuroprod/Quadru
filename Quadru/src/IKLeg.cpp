#include "IKLeg.h"

using namespace ci;
using namespace ci::app;
using namespace std;


IKLegRef IKLeg::create() 
{
	return make_shared<IKLeg>();
}

void IKLeg::setup(glm::vec3 _pos, ModelConfigRef _conf)
{
	pos = _pos ;
	conf = _conf;

	PI = glm::pi<float>();

	build();
}
void IKLeg::build(){

	baseMatrix = mat4();
	baseMatrix = glm::translate(baseMatrix, pos);
	invBaseMatrix = glm::inverse(baseMatrix);
	


}
void IKLeg::resolve(glm::vec3 target, glm::mat4 invBodyMatrix) 
{

	targetHip1Local = invBodyMatrix* invBaseMatrix*vec4(target.x,target.y,target.z,1.f) ;

	targetHip1LocalFlat = vec3(0, targetHip1Local.y, targetHip1Local.z);
	//pythagoras theorem C2= A2+B2
	float C = glm::length(targetHip1LocalFlat);
	float B = conf->hipOffsetZ;
	float A = sqrtf(C*C - B*B);
;
	float angleCX = atan2f(targetHip1LocalFlat.y, targetHip1LocalFlat.z);

	//sineRule
	float angleBC = asinf(A / (C / sinf(PI / 2)));

	if (isLeft) 
	{
		angleHip1 = ((angleCX - angleBC)+ PI)*hipRotScale;
	}
	else 
	{
		angleHip1 = (angleCX + angleBC)*hipRotScale;
	}

	
	


}