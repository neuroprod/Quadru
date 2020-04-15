#pragma once
#include "cinder/app/App.h"
#include "Controle.h"
#include "IKLeg.h"
#include "FKModel.h"
class IKModel;
typedef std::shared_ptr<IKModel> IKModelRef;

class IKModel 
{
public:
	IKModel() {};
	void setup(ModelConfigRef _config ,ControleRef _controle, FKModelRef _fkModel);
	void update();
	void reBuild();
	ModelConfigRef config;
	ControleRef controle;
	FKModelRef fkModel;

	glm::mat4 bodyMatrix;

	std::vector<IKLegRef> legs;


	IKLegRef FR;
	IKLegRef FL;
	IKLegRef BR;
	IKLegRef BL;
};