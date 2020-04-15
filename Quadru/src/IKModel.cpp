#include "IKModel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void IKModel::setup(ModelConfigRef _config, ControleRef _controle, FKModelRef _fkModel)
{
	config = _config;
	controle=_controle;
	fkModel = _fkModel;
	reBuild();

}
void IKModel::reBuild() 
{
	legs.clear();

	FR = IKLeg::create();


	FR->setup(fkModel->FRLeg->hip1->baseMatrix, fkModel->FRLeg->hip2->baseMatrix, config);
	FR->hipOffsetZFlip = fkModel->FRLeg->hipOffsetZFlip;

	FL = IKLeg::create();
	FL->setup(fkModel->FLLeg->hip1->baseMatrix, fkModel->FLLeg->hip2->baseMatrix, config);
	FL->hipOffsetZFlip = fkModel->FLLeg->hipOffsetZFlip;
	FL->isLeft = true;

	BR = IKLeg::create();
	BR->setup(fkModel->BRLeg->hip1->baseMatrix, fkModel->BRLeg->hip2->baseMatrix, config);
	BR->hipOffsetZFlip = fkModel->BRLeg->hipOffsetZFlip;

	BL = IKLeg::create();
	BL->setup(fkModel->BLLeg->hip1->baseMatrix, fkModel->BLLeg->hip2->baseMatrix, config);
	BL->isLeft = true;
	BL->hipOffsetZFlip = fkModel->BLLeg->hipOffsetZFlip;
	BL->isLeft = true;

	legs.push_back(FR);
	legs.push_back(FL);
	legs.push_back(BR);
	legs.push_back(BL);

}
void IKModel::update()
{


	bodyMatrix = mat4();
	bodyMatrix = glm::translate(bodyMatrix, vec3(controle->bodyX, controle->bodyY, controle->bodyZ));

	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotX, vec3(1, 0, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotY, vec3(0, 1, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotZ, vec3(0, 0, 1));

	mat4 invBodyMatrix = glm::inverse(bodyMatrix);

	for (int i=0; i< controle->legs.size();i++) 
	{
		vec3 target = controle->legs[i]->targetPos;
		target.y += config->footRadius;
		legs[i]->resolve(target, invBodyMatrix);
	}
}