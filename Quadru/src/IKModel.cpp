#include "IKModel.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void IKModel::setup(ModelConfigRef _config, ControleRef _controle)
{
	config = _config;
	controle=_controle;
	

}
void IKModel::update()
{
	bodyMatrix = mat4();
	bodyMatrix = glm::translate(bodyMatrix, vec3(controle->bodyX, controle->bodyY, controle->bodyZ));

	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotX, vec3(1, 0, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotY, vec3(0, 1, 0));
	bodyMatrix = glm::rotate(bodyMatrix, controle->bodyRotZ, vec3(0, 0, 1));
}