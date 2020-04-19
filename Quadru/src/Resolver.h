#pragma once
#include "FKModel.h"
#include "cinder/app/App.h"


class Resolver;
typedef std::shared_ptr<Resolver> ResolverRef;


class Resolver 
{
public:
	Resolver() {};
	void setup(FKModelRef _model);
	void update();
	void checkHit(ci::vec3 ballPos);
	float getMass();
	void drawGui();

	glm::vec4 getCenterOfMass();

	float hitDepth = 0;
	std::vector<glm::vec3>hits;

	FKModelRef model;

	glm::vec4 centerOfMass;
	float mass;
	float mass3;
	glm::vec3 currentSpeed;
	glm::mat4 transMat;


	bool play = false;
	bool step = false;
};