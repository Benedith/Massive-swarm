#include "Simulation.h"
#include <math.h>


//This is the start for the simulation code which will all be platform independent because we hide all the platform
//specific code in main and the equivalent of the GLUT that i'll write

//We cannot use normal main because that will override WinMain loading
//Fake starting point
Simulation::Simulation()
{
	camera = new Camera(Vector3(0, 0, -30), 1.0f, (float)800 / (float)600, 0.01f, 1000.0f);

	std::cout << "HI";
	shader = new Shader(std::string("./stuff/shaders/basicShader"));
	instShader = new Shader(std::string("./stuff/shaders/basicInstancedShader"));


	Vertex vertices[] = { Vertex(Vector3(-0.5, -0.5, 0), Vector2(0.0, 0.0)),
							Vertex(Vector3(0, 0.5, 0)    , Vector2(1.0, 0.0)),
							Vertex(Vector3(0.5, -0.5, 0) , Vector2(0.0, 1.0)) };
	unsigned int indices[]{ 0, 1, 2 };
	mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	swarm = new Swarm(10, vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	
	transform = new Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	for (int i = 0; i < 100; i++)
	{
		swarmMembers.push_back(new SwarmMember(mesh, shader, camera, Transform(Vector3(i, i, i))));
	}
	
}

Simulation::~Simulation()
{

}

void Simulation::Tick()
{
	swarm->Update();
}
float counter = 0.0f;

void Simulation::Draw()
{
	float sinCount = sin(counter);
	float cosCount = cos(counter);
	transform->SetPosition(Vector3(sinf(counter), 0, 0));
	//transform->SetRotation(Vector3(cosCount, sinCount, 0));
	//transform->SetScale(Vector3(cosCount, cosCount, cosCount));

	camera->Update();

	shader->Bind();
	shader->Update(*transform, *camera);
	mesh->Draw();

	for (int i = 0; i < swarmMembers.size() ; i++)
	{
		swarmMembers[i]->Draw();
	}

	//instShader->Bind();
	//instShader->Update(*transform, *camera);
	//swarm->Draw();

	counter += 0.01f;
}