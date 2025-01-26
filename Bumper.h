#pragma once
#include "MeshActor.h"
class Bumper : public MeshActor
{
	float scorePoint;
public:
	FORCEINLINE float GetScorePoint()
	{
		return scorePoint;
	}
	FORCEINLINE void SetScorePoint(const float _scorePoint)
	{
		scorePoint = _scorePoint;
	}
public:
	Bumper(const Vector2f& _size, const string& _path = "");
	Bumper(const Bumper& _other);
};