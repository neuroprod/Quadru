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

	targetHip1Local = invBaseMatrix *invBodyMatrix*vec4(target.x,target.y,target.z,1.f) ;

	targetHip1LocalFlat = vec3(0, targetHip1Local.y, targetHip1Local.z);
	//pythagoras theorem C2= A2+B2
	float C = glm::length(targetHip1LocalFlat);
	float B = conf->hipOffsetZ;
	float A = sqrtf(C*C - B*B);
;
	float angleCX = atan2f(targetHip1LocalFlat.y, targetHip1LocalFlat.z);

	//sine law
	float angleBC = asinf(A / (C / sinf(PI / 2)));

	if (isLeft) 
	{
		angleHip1 = ((angleCX - angleBC)+ PI)*hipRotScale;
	}
	else 
	{
		angleHip1 = (angleCX + angleBC)*hipRotScale;
	}

	float zScale = -1;
	if (isLeft)
	{
		zScale = 1;
	}

	mat4 hip1MatrixInv = mat4();
	hip1MatrixInv = glm::translate(hip1MatrixInv, vec3(conf->hipOffsetX*hipRotScale,0, conf->hipOffsetZ*zScale));
	hip1MatrixInv = glm::rotate(hip1MatrixInv, -angleHip1, vec3(1, 0, 0));

	targetHip2Local = hip1MatrixInv* targetHip1Local;
	//resolve in XY;
	vec2 targetHip1LocalFlat = vec2(targetHip2Local);
	C = glm::length(targetHip1LocalFlat);
	A = conf->upperLegLength;
	B = conf->underLegLength;

	angleCX = atan2f(targetHip1LocalFlat.y, targetHip1LocalFlat.x);

	//cos law 
	//b = aCos((B2 - A2 - C2) / − 2AC)
	float angleB = acosf((B*B - A*A - C*C) / (-2.f * A*C));

	angleHip2 =PI/2 + angleCX+ angleB ;
	
	 //c = aCos((C2 - A2 - B2) / − 2AB)
	angleKnee = PI  - (acosf((C*C - A*A - B*B) / (-2.f * A*B)) *-1);
	if (!isLeft)
	{
		angleHip2 =  ((angleHip2*-1.f)) ;
		angleKnee = ((angleKnee*-1.f));
		//console() <<angleKnee / PI * 180 << " " << angleHip2 / PI * 180 << endl;
	}
	
}