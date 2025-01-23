#include "MeshActor.h"
#include "Game.h"

MeshActor::MeshActor(const float _radius, const size_t& _pointCount, const string& _path,
					 const IntRect& _rect, const string& _name) : Actor(_name)
{
	mesh = CreateComponent<MeshComponent>(_radius, _pointCount, _path, _rect);
	renderMeshToken = -1;
}

MeshActor::MeshActor(const Vector2f& _size, const string& _path, const TextureExtensionType& _textureType,
					 const IntRect& _rect, const string& _name) : Actor(_name)
{
	mesh = CreateComponent<MeshComponent>(_size, _path, _textureType, _rect);
	renderMeshToken = -1;
}

MeshActor::MeshActor(const MeshActor& _other) : Actor(_other)
{
	mesh = CreateComponent<MeshComponent>(_other.mesh);
	renderMeshToken = _other.renderMeshToken;
}

void MeshActor::Construct()
{
	Super::Construct();
	renderMeshToken = M_GAME.BindOnRenderWindow(bind(&MeshActor::RenderMesh, this, placeholders::_1));
}

void MeshActor::Deconstruct()
{
	Super::Deconstruct();
	M_GAME.UnbindOnRenderWindow(renderMeshToken);
}

void MeshActor::RenderMesh(RenderWindow& _window)
{
	_window.draw(*mesh->GetShape()->GetDrawable());
}