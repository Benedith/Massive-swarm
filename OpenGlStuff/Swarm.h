#pragma once
#include "Mesh.h"

class Swarm : public Mesh
{
public:
	Swarm(int swarmNum, Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	~Swarm();

	virtual void Update() override;

	virtual void Draw() override;

private:
	std::vector<Vector3> instPositions;

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INSTANCED_POSITION_VB,
		INDEX_VB,

		NUM_INSTANCED_BUFFERS
	};

};

