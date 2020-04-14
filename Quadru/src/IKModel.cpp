#include "IKModel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void IKModel::setup(ModelConfigRef _config, ControleRef _controle)
{
	config = _config;
	controle=_controle;
	
	reBuild();

}
void IKModel::reBuild() 
{
	legs.clear();

	FR = IKLeg::create();
	FR->setup(vec3(config->bodyLength / 2, 0, config->bodyWidth / 2), config);
	FR->hipRotScale = -1;

	FL = IKLeg::create();
	FL->setup(vec3(config->bodyLength / 2, 0, -config->bodyWidth / 2), config);
	FL->isLeft = true;
	FL->hipRotScale = -1;

	BR = IKLeg::create();
	BR->setup(vec3(-config->bodyLength / 2, 0, config->bodyWidth / 2), config);

	BL = IKLeg::create();
	BL->setup(vec3(-config->bodyLength / 2, 0, -config->bodyWidth / 2), config);
	BL->isLeft = true;

	legs.push_back(FR);
	legs.push_back(FL);
	legs.push_back(BR);
	legs.push_back(BL);

}
void IKModel::update()
{
	if (config->needsRebuild) 
	{
		reBuild();
	
	}

	bodyMatrix = mat4();
	bodyMatrix = glm::translate(bodyMatrix, vec3(controle->bodyX, controle->bodyY, controle->bodyZ));

	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotX, vec3(1, 0, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotY, vec3(0, 1, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotZ, vec3(0, 0, 1));

	mat4 invBodyMatrix = glm::inverse(bodyMatrix);

	for (int i=0; i< controle->legs.size();i++) 
	{
	
		legs[i]->resolve(controle->legs[i]->targetPos, invBodyMatrix);
	}
}