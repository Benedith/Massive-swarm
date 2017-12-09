#include "SwarmMember.h"


SwarmMember::SwarmMember(Mesh * _mesh, Shader * _shader, Camera * _cam, Transform _transform = Transform())
	:mesh(_mesh), shader(_shader), cam(_cam), transform(_transform)
{

}

SwarmMember::~SwarmMember()
{
}

void SwarmMember::Update()
{
	transform.SetPosition(Vector3(rand() % 100, rand() % 100, rand() % 100));

}

void SwarmMember::Draw()
{
	shader->Bind();
	shader->Update(transform, *cam);
	mesh->Draw();
}
