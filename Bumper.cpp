#include "Bumper.h"

Bumper::Bumper(const Vector2f& _size, const string& _path) : MeshActor(_size,_path)
{
	scorePoint = 0;
}

Bumper::Bumper(const Bumper& _other) : MeshActor(_other)
{
	scorePoint = _other.scorePoint;
}