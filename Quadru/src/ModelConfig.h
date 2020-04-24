#pragma once
#include "cinder/app/App.h"


class ModelConfig;
typedef std::shared_ptr<ModelConfig > ModelConfigRef;

class ModelConfig 
{
public: 
	ModelConfig() {}
	static ModelConfigRef create();
	void setup();
	void drawGui();
	void setDirty();
	bool needsRebuild = false;
	bool isDirty = true;

	float bodyY = 400;

	float bodyLength = 500;
	float bodyWidth = 100;

	float hipOffsetX = 50;
	float hipOffsetZ = 70;
	float upperLegLength = 300;
	float underLegLength =300;

	float footRadius =15;

	float bodyMass = 4.f;
	ci::vec3 bodyCOM = ci::vec3(0, 0, 0);

	float hip1Mass = 1.f;
	ci::vec3 hip1COM = ci::vec3(50, 0, 0);

	float hip2Mass = 1.f;
	ci::vec3 hip2COM = ci::vec3(0, -120, 0);


	float kneeMass = 1.f;
	ci::vec3 kneeCOM = ci::vec3(0, -120,0);


	float footMass = 0.5f;
	ci::vec3 footCOM = ci::vec3(0, 0, 0);

	float motorHeight = 35;
	float motorRadius = 49;
};