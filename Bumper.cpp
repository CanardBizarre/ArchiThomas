#include "Bumper.h"

Bumper::Bumper(const float _scorePoint, const Vector2f& _size, const string& _path) : MeshActor(_size, _path)
{
	scorePoint = _scorePoint;
}
