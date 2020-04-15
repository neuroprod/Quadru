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

	void setup(glm::mat4 hip1Matrix, glm::mat4 hip2Matrix, ModelConfigRef _conf);
	void build();
	void resolve(glm::vec3 target, glm::mat4 invBodyMatrix);

	float PI;


	glm::vec3 pos;
	ModelConfigRef conf;

	glm::mat4 hip1Matrix;
	glm::mat4 invHip1Matrix;

	glm::mat4 hip2Matrix;
	glm::mat4 invHip2Matrix;

	glm::vec4 targetHip1Local;
	glm::vec3 targetHip1LocalFlat;

	glm::vec4 targetHip2Local;

	float hipOffsetZFlip = 1;
	bool isLeft = false;

	float angleHip1 = 0;
	float angleHip2 = 0;
	float angleKnee = 0;
};