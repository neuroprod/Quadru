#pragma once
#include "cinder/app/App.h"
#include "Mesh.h"
class NodeData;
typedef std::shared_ptr<NodeData> NodeDataRef;

class NodeData
{
public:
	NodeData() {};
	void setGlobalMatrix(ci::mat4 &globalMatrix);

	static NodeDataRef create();
	std::string type;
	glm::vec3 centerOfMass = glm::vec3(0, 0, 0);
	float mass = mass;
	std::vector<MeshRef> meshes;
	ci::mat4 globalMatrix;

	
};