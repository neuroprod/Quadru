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

	



}