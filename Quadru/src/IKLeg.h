#pragma once
#include "cinder/app/App.h"
#include "ModelConfig.h"

class IKLeg;
typedef std::shared_ptr<IKLeg> IKLegRef;
class IKLeg
{
public:
	IKLeg() {};
	static IKLegRef create();

	void setup(glm::vec3 _pos, ModelConfigRef _conf);
	void build();
	void resolve(glm::vec3 target, glm::mat4 invBodyMatrix);

	float PI;


	glm::vec3 pos;
	ModelConfigRef conf;

	glm::mat4 baseMatrix;
	glm::mat4 invBaseMatrix;


	glm::vec4 targetHip1Local;
	glm::vec3 targetHip1LocalFlat;
	float hipRotScale = 1;
	bool isLeft = false;
	float angleHip1 = 0;
};