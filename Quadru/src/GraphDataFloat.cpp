#include "GraphDataFloat.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void GraphDataFloat::addData(float _data)
{
	
	data.push_back(_data);
	if (data.size() > 500) 
	{
		data.pop_front();
	}
}
void GraphDataFloat::draw() 
{

	gl::pushMatrices();
	gl::translate(100, 100);
	
	gl::drawString(name, vec2(0, 0));
	gl::color(1, 1, 1);
	gl::begin(GL_LINE_STRIP);


	int pos = 0;
	for (auto const& val : data) {
	
		gl::vertex(vec2(pos, val*scale)); 
		pos += 2;
	}
	gl::end();
	gl::popMatrices();
}

