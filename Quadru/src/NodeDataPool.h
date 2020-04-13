#pragma once
#include "Singleton.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include "NodeData.h"
#include "ModelConfig.h"
class NodeDataPool
{

public:
	NodeDataPool();
	void setup(ModelConfigRef _config);
	NodeDataRef getData(std::string type);
	void clear();
	ModelConfigRef config;
	std::vector<NodeDataRef> pool;
	ci::gl::GlslProgRef mGlsl;

};

typedef Singleton<NodeDataPool > NodeDataPoolSingleton;

inline NodeDataPool * NDP() {
	return  NodeDataPoolSingleton::Instance();
}
