#include "NodeData.h"
using namespace ci;
using namespace ci::app;
using namespace std;

NodeDataRef NodeData::create()
{
	NodeDataRef ref = std::make_shared<NodeData>();
	return ref;
}
void NodeData::setGlobalMatrix(ci::mat4 &_globalMatrix) 
{
	globalMatrix = _globalMatrix;

}