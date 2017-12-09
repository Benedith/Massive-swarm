#pragma once

#include <vector>
#include <sstream>

#include <GL\glew.h>

#include "Bmath.h"
#include "Shader.h"

class Vertex
{
public:
	Vertex()
	{
	}

	Vertex(const Vector3& _Position)
	{
		this->Position = _Position;
	}

	Vertex(const Vector3& _Position, const Vector2& _TexCoords)
	{
		this->Position = _Position;
		this->TexCoords = _TexCoords;
	}

	Vertex(const Vector3& _Position, const Vector2& _TexCoords, const Vector3& _Normal)
	{
		this->Position = _Position;
		this->TexCoords = _TexCoords;
		this->Normal = _Normal;
	}

	inline Vector3* GetPos() { return &Position; }
	inline Vector2* GetTexCoord() { return &TexCoords; }
	inline Vector3* GetNormal() { return &Normal; }

	inline void SetPos(Vector3 &_p) { Position = _p; }
	inline void SetTexCoord(Vector2 &_tc) { TexCoords = _tc; }
	inline void SetNormal(Vector3 &_n) { Normal = _n; }

private:
	Vector3 Position;
	Vector2 TexCoords;
	Vector3 Normal;
};

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	virtual ~Mesh();

	virtual void Draw();
	virtual void Update();

protected:

	Mesh(const Mesh& otehr);
	void operator=(const Mesh& otehr);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	std::vector<Vector3> positions;
	std::vector<Vector2> texCoords;
	std::vector<GLuint> indicies;

	GLuint m_vertexArrayObject;
	GLuint* m_vertexArrayBuffers;
	unsigned int m_drawCount;
private:
};
