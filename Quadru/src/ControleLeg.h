#pragma once
#include "cinder/app/App.h"

class ControleLeg;
typedef std::shared_ptr<ControleLeg  > ControleLegRef;

class ControleLeg 
{
public:
	ControleLeg() {};
	static ControleLegRef create();

	ci::vec3 homePos;
	ci::vec3 targetPos;


};