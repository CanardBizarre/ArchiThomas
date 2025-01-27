#pragma once
#include "Actor.h"
#include "MeshComponent.h"

enum Corner
{
	RIGHTDOWNCORNER,
	RIGHTUPCORNER,
	LEFTDOWNCORNER,
	LEFTUPCORNER,
};

class MeshActor : public Actor
{
	MeshComponent* mesh;
	u_int renderMeshToken;
	Vector2f size;
	map<Corner, Vector2f> coordinatesOfCorner;

public:
	FORCEINLINE MeshComponent* GetMesh() const
	{
		return mesh;
	}

	FORCEINLINE Vector2f GetSize() const
	{
		return size;
	}
	FORCEINLINE map<Corner, Vector2f> GetCoordinateOfCorner() const
	{
		return coordinatesOfCorner;
	}

	#pragma region Modifier

	FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
	{
		Super::SetPosition(_position);
		mesh->GetShape()->SetPosition(_position);
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
	{
		Super::SetRotation(_rotation);
		mesh->GetShape()->SetRotation(_rotation);
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
	{
		Super::SetScale(_scale);
		mesh->GetShape()->SetScale(_scale);
	}
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
	{
		Super::SetOrigin(_origin);
		mesh->GetShape()->SetOrigin(_origin);
	}
	FORCEINLINE void SetOriginAtMiddle()
	{
		SetOrigin(mesh->GetShape()->GetDrawable()->getGeometricCenter());
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) override
	{
		Super::Move(_offset);
		mesh->GetShape()->Move(_offset);
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle) override
	{
		Super::Rotate(_angle);
		mesh->GetShape()->Rotate(_angle);
		RotateAllCoords(_angle);
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor) override
	{
		Super::Scale(_factor);
		mesh->GetShape()->Scale(_factor);
	}

	#pragma endregion

public:
	MeshActor() = default;
	MeshActor(const float _radius, const size_t& _pointCount = 30, const string& _path = "",
			  const IntRect& _rect = {}, const string& _name = "MeshActor", const u_int& _lifeSpand = 0);
	MeshActor(const Vector2f& _size, const string& _path = "", const TextureExtensionType& _textureType = PNG,
			  const IntRect& _rect = {}, const string& _name = "MeshActor", const u_int& _lifeSpand = 0);
	MeshActor(const MeshActor& _other);

	virtual void Construct() override;
	virtual void Deconstruct() override;

private:
	void RenderMesh(RenderWindow& _window);

public:
#pragma region Code de vt
	Vector2f ComputeOppositeCornerCoordinate(const Vector2f& _coordinate);
	Vector2f ComputeRotatedCoordinate(const Vector2f& _coordinate, float _degrees);
	Vector2f ComputeOrigineToCoordE();
	void LogCoordinate();
	void ComputeCoord(const Vector2f _oe);
	map<Corner, Vector2f> InitCoords();
	map<Corner, Vector2f> RotateAllCoords(const Angle& _radian);
	map<Corner, Vector2f> RotateAllCoords(const float _angle);
#pragma endregion

};