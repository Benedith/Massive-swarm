#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

class SwarmMember
{
public:
	SwarmMember(Mesh* _mesh, Shader* _shader, Camera* _cam, Transform _transform);
	~SwarmMember();

	void Update();
	void Draw();

protected:
	Mesh* mesh;
	Transform transform;
	Shader* shader;
	Camera* cam;

};

