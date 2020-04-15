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

	float motorHeight = 35;
	float motorRadius = 49;
};