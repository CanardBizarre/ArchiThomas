#include "MeshActor.h"
#include "CameraManager.h"

MeshActor::MeshActor(const float _radius, const size_t& _pointCount, const string& _path,
					 const IntRect& _rect, const string& _name, const u_int& _lifeSpand) : Actor(_name, _lifeSpand)
{
	mesh = CreateComponent<MeshComponent>(_radius, _pointCount, _path, _rect);
	renderMeshToken = -1;
	size = Vector2f(_radius * 2.0f, _radius * 2.0f);
}

MeshActor::MeshActor(const Vector2f& _size, const string& _path, const TextureExtensionType& _textureType,
					 const IntRect& _rect, const string& _name, const u_int& _lifeSpand) : Actor(_name, _lifeSpand)
{
	mesh = CreateComponent<MeshComponent>(_size, _path, _textureType, _rect);
	renderMeshToken = -1;
	size = _size;
}

MeshActor::MeshActor(const MeshActor& _other) : Actor(_other)
{
	mesh = CreateComponent<MeshComponent>(_other.mesh);
	renderMeshToken = _other.renderMeshToken;
	size = _other.size;
}

void MeshActor::Construct()
{
	Super::Construct();
	renderMeshToken = M_CAMERA.BindOnRenderWindow(bind(&MeshActor::RenderMesh, this, placeholders::_1));
}

void MeshActor::Deconstruct()
{
	Super::Deconstruct();
	M_CAMERA.UnbindOnRenderWindow(renderMeshToken);
}

void MeshActor::RenderMesh(RenderWindow& _window)
{
	_window.draw(*mesh->GetShape()->GetDrawable());
}