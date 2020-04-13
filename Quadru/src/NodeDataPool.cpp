#include "NodeDataPool.h"
using namespace ci;
using namespace ci::app;
using namespace std;


NodeDataPool::NodeDataPool() {

}
void NodeDataPool::setup(ModelConfigRef _config)
{
	config = _config;
	mGlsl = gl::GlslProg::create(loadAsset("shaders/mainShader.vert.glsl"), loadAsset("shaders/mainShader.frag.glsl"));

}
void  NodeDataPool::clear()
{
	pool.clear();
}
NodeDataRef NodeDataPool::getData(std::string type)
{
	for (auto data : pool)
	{
		if (data->type == type) return data;
	}

	NodeDataRef m = NodeData::create();
	m->type = type;
	console() << type << endl;

	pool.push_back(m);
	return m;
}

