#pragma once
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"



class SymbolBatches 
{

public:
	SymbolBatches() {
	
	};
	void setup();
	void makeFloor();
	void makeHome();
	void makeCoordinateFrame();
	void makeTarget();
	ci::gl::BatchRef floorBatch;
	ci::gl::BatchRef homeBatch;
	ci::gl::BatchRef targetBatch;
	ci::gl::BatchRef coordinateFrame;
};