#pragma once
#include "Bmath.h"
using namespace BMath;
class Transform
{
public:
	Transform(Vector3& _pos = Vector3(0, 0, 0), Vector3& _rot = Vector3(0, 0, 0), Vector3& _scale = Vector3(1, 1, 1)) :
		Position(_pos), Rotation(_rot), Scale(_scale)
	{}
	~Transform()
	{}

	inline void SetPosition(Vector3& _pos) { Position = _pos; }
	inline void SetRotation(Vector3& _rot) { Rotation = _rot; }
	inline void SetScale(Vector3& _scale) { Scale = _scale; }

	inline Vector3& GetPosition() { return Position; }
	inline Vector3& GetRotation() { return Rotation; }
	inline Vector3& GetScale() { return Scale; }

	inline Matrix4 Get() const
	{
		Matrix4 posMat = translate(Position);
		Matrix4 rotXMat = rotateAroundXAxis(Rotation.GetX());
		Matrix4 rotYMat = rotateAroundYAxis(Rotation.GetY());
		Matrix4 rotZMat = rotateAroundZAxis(Rotation.GetZ());
		Matrix4 scaleMat = scale(Scale);

		Matrix4 rotMat = rotZMat * rotYMat * rotXMat;
		return posMat * rotMat * scaleMat;
	}
protected:
private:
	Vector3 Position;
	//Watch out for gimbal lock
	Vector3 Rotation;
	Vector3 Scale;
};
