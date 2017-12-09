#pragma once
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Swarm.h"
#include "SwarmMember.h"


class Simulation
{
public:
	Simulation();
	~Simulation();

	void Tick();
	void Draw();
private:
	Shader* shader;
	Shader* instShader;
	Transform* transform;
	Mesh* mesh;

	Swarm* swarm;

	std::vector<SwarmMember*> swarmMembers;

	Camera* camera;
	
};
