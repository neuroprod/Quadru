#pragma once
#include "cinder/app/App.h"
#include "Controle.h"
class IKModel 
{
public:
	IKModel() {};
	void setup(ModelConfigRef _config ,ControleRef _controle);
	void update();
	
	ModelConfigRef config;
	ControleRef controle;
	glm::mat4 bodyMatrix;
};