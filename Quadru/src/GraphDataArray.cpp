#include "GraphDataArray.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;
using namespace std;

void GraphDataArray::addData(std::vector<float> _data)
{
	
	data.push_back(_data);
	if (data.size() > 500)
	{
		data.pop_front();
	}
}
void  GraphDataArray::draw()
{
	gl::pushMatrices();
	gl::translate(100, 100);
	gl::drawStringRight(name, vec2(0, -90), Color(1, 1, 1), Font("Arial",30));

	for (int i = 0; i < size; i++) {

		gl::drawStringRight(names[i] , vec2(0,-90+ 30+i*20), color[i], Font("Arial", 24));
		gl::color(color[i]);
		gl::begin(GL_LINE_STRIP);
		int pos = 0;
		for (auto const& val : data) {

			gl::vertex(vec2(pos, val[i] * scale[i]));
			pos += 2;
		}
		gl::end(); 


	}

	gl::popMatrices();
}

