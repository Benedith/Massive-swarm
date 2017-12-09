#include "Swarm.h"



Swarm::Swarm(int swarmNum, Vertex * vertices, unsigned int numVertices, unsigned int * _indices, unsigned int numIndices)
{
	m_vertexArrayBuffers = new GLuint[NUM_INSTANCED_BUFFERS];
	m_drawCount = numIndices;

	//create vertex array
	glGenVertexArrays(1, &m_vertexArrayObject);
	//load vertex array
	glBindVertexArray(m_vertexArrayObject);

	/*std::vector<Vector3> positions;
	std::vector<Vector2> texCoords;*/

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}
	//std::vector<unsigned int> indices;
	for (int i = 0; i < numIndices; i++)
	{
		indicies.push_back(_indices[i]);
	}

	for (int i = 0; i < 100; i++)
	{
		instPositions.push_back(Vector3(i, i, i));
	}

	glGenBuffers(NUM_INSTANCED_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[INSTANCED_POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, instPositions.size() * sizeof(instPositions[0]), &instPositions[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indicies[0]), &indicies[0], GL_DYNAMIC_DRAW);

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same vertices -> 0
	glVertexAttribDivisor(1, 0); // texCoords : in case you want it NOt instanced -> 0
	glVertexAttribDivisor(2, 1); // inst positions : one per member -> 1

	//clear loaded vertex array
	glBindVertexArray(0);

}

Swarm::~Swarm()
{
}

void Swarm::Update()
{
	//instPositions.clear();
	//for (int i = 0; i < 100; i++)
	//{
	//	instPositions.push_back(Vector3(i, i, i));
	//}

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[INSTANCED_POSITION_VB]);
	//glBufferData(GL_ARRAY_BUFFER, instPositions.size() * sizeof(instPositions[0]), &instPositions[0], GL_DYNAMIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Swarm::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElementsInstanced(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, NULL, instPositions.size());

	glBindVertexArray(0);
}
