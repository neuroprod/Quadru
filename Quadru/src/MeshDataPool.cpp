#include "MeshDataPool.h"
#include "Mesh.h"
using namespace ci;
using namespace ci::app;
using namespace std;


MeshDataPool::MeshDataPool() {

}
void MeshDataPool::setup(ModelConfigRef _config)
{
	config = _config;
	mGlsl = gl::GlslProg::create(loadAsset("shaders/mainShader.vert.glsl"), loadAsset("shaders/mainShader.frag.glsl"));

}
void  MeshDataPool::clear()
{
	pool.clear();
}
MeshDataRef MeshDataPool::getMesh(std::string type)
{
	
	Color baseColor = Color(0.3, 0.3, 0.3);
	Color feetColor = Color(1,0, 0);
	Color motorColor = Color(0.8, 0.0, 0.0);

	MeshDataRef nd = MeshData::create();
	nd->type = type;
	if (type == "body") 
	{
		
		MeshRef m = Mesh::create();
		m->setup(geom::Cube().size(config->bodyLength- config->motorHeight*2-20, 80.0f, config->bodyWidth), vec3(0, 0, 0), baseColor, mGlsl);
		nd->meshes.push_back(m);


		MeshRef motor1 = Mesh::create();
		motor1->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(1, 0, 0)).origin(vec3(0, 0, 0)), vec3(-config->bodyLength/2, 0, -config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor1);

		MeshRef motor2 = Mesh::create();
		motor2->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(1, 0, 0)).origin(vec3(0, 0, 0)), vec3(-config->bodyLength / 2, 0, +config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor2);


		MeshRef motor3 = Mesh::create();
		motor3->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(-1, 0, 0)).origin(vec3(0, 0, 0)), vec3(config->bodyLength / 2, 0, -config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor3);

		MeshRef motor4 = Mesh::create();
		motor4->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(-1, 0, 0)).origin(vec3(0, 0, 0)), vec3(config->bodyLength / 2, 0, +config->bodyWidth / 2), motorColor, mGlsl);
		nd->meshes.push_back(motor4);


	}
	if (type == "knee")
	{
		
		MeshRef m = Mesh::create();
		m->setup(geom::Cone().base(20).apex(5).height(config->underLegLength-config->footRadius).direction(vec3(0,-1,0)), vec3(0, 0, 0), baseColor, mGlsl);
		nd->meshes.push_back(m);

		MeshRef m2 = Mesh::create();
		m2->setup(geom::Sphere().radius(config->footRadius), vec3(0, -config->underLegLength + config->footRadius, 0), feetColor, mGlsl);
		nd->meshes.push_back(m2);
	}
	if (type == "hip2")
	{
	
		MeshRef m = Mesh::create();
		m->setup(geom::Capsule().radius(22).length(config->upperLegLength ).center(vec3(0,-config->upperLegLength/2,0)), vec3(0, 0, 0), baseColor, mGlsl);
		nd->meshes.push_back(m);

	
		MeshRef motor = Mesh::create();
		motor->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(1,0,0)).origin(vec3(-config->hipOffsetZ +20, 0, 0)), vec3(0, 0, 0), motorColor, mGlsl);
		nd->meshes.push_back(motor);


	}
	if (type == "hip1_mirror")
	{
	
	
		MeshRef motor = Mesh::create();
		motor->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(0, 0, -1)).origin(vec3(config->hipOffsetX, 0, 0)), vec3(0, 0, 0), motorColor, mGlsl);
		nd->meshes.push_back(motor);


	}
	if (type == "hip1")
	{



		MeshRef motor = Mesh::create();
		motor->setup(geom::Cylinder().radius(config->motorRadius).height(config->motorHeight).direction(vec3(0, 0, 1)).origin(vec3(config->hipOffsetX, 0, 0)), vec3(0, 0, 0), motorColor, mGlsl);
		nd->meshes.push_back(motor);


	}
	pool.push_back(nd);
	return nd;
}

