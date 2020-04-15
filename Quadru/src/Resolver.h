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
	float getMass();
	glm::vec4 getCenterOfMass();

	FKModelRef model;

	glm::vec4 centerOfMass;
	float mass;
	float mass3;
};