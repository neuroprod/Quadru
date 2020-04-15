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
	glm::vec4 centerOfMass = glm::vec4(0, 0, 0,1);
	float mass = 0;
	float mass3 = 0;
	std::vector<MeshRef> meshes;
	ci::mat4 globalMatrix;
	glm::vec4 centerOfMassGlobal;
	
};