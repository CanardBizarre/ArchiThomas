#pragma once
#include "MeshActor.h"

class RectangleActor : public MeshActor
{
public:
	RectangleActor(const Vector2f& _size, const string& _path = "", const TextureExtensionType& _textureType = PNG, const IntRect& _rect = {});
};