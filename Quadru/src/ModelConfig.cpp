#include "ModelConfig.h"
#include "CinderImGui.h"
using namespace ci;
using namespace ci::app;
using namespace std;

ModelConfigRef ModelConfig::create()
{
	return std::make_shared<ModelConfig>();
}
void ModelConfig::setup() 
{


}
void ModelConfig::setDirty() 
{
	isDirty = true;
	needsRebuild = true;
}
void ModelConfig::drawGui()
{
	ui::ScopedWindow window("Config");
	if (ui::DragFloat("bodyY", &bodyY,1, 0, 1000)) setDirty();
	if (ui::DragFloat("bodyWidth", &bodyWidth, 1, 0, 1000)) setDirty();
	if (ui::DragFloat("bodyLength", &bodyLength, 1, 0, 1000)) setDirty();
	if (ui::DragFloat("hipOffsetX", &hipOffsetX, 1, 0, 200)) setDirty();
	if (ui::DragFloat("hipOffsetZ", &hipOffsetZ, 1, 0, 200)) setDirty();

	if (ui::DragFloat("upperLegLength", &upperLegLength, 1, 0, 200)) setDirty();
	if (ui::DragFloat("underLegLength", &underLegLength, 1, 0, 200)) setDirty();
	if (ui::DragFloat("footRadius", &footRadius, 1, 0, 200)) setDirty();
}