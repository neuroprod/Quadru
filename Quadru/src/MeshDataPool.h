#pragma once
#include "Singleton.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include "MeshData.h"
#include "ModelConfig.h"
class MeshDataPool
{

public:
	MeshDataPool();
	void setup(ModelConfigRef _config);
	MeshDataRef getMesh(std::string type);
	void clear();
	

	ModelConfigRef config;
	std::vector<MeshDataRef> pool;
	ci::gl::GlslProgRef mGlsl;

};

typedef Singleton<MeshDataPool > NodeDataPoolSingleton;

inline MeshDataPool * MDP() {
	return  NodeDataPoolSingleton::Instance();
}
