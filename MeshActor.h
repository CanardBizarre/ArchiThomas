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
		LOG(Warning, to_string(_angle.asRadians()));
		mesh->GetShape()->Rotate(_angle);
		RotateAllCoords(_angle);
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor) override
	{
		Super::Scale(_factor);
		mesh->GetShape()->Scale(_factor);
	}

	FORCEINLINE Vector2f ComputeOppositeCornerCoordinate(const Vector2f& _coordinate)
	{
		const float _width = GetPosition().x;
		const float _length = GetPosition().y;
		const Vector2f& _coordsRoatated = _coordinate.rotatedBy(degrees(180.0f));

		return Vector2(_coordsRoatated.x + _width * 2.0f,
			_coordsRoatated.y + _length * 2.0f);
	}

	FORCEINLINE Vector2f ComputeRotatedCoordinate(const Vector2f& _coordinate, float _degrees)
	{
		const float _xOrigin = GetPosition().x;
		const float _yOrigin = GetPosition().y;
		const float _xCoordinate = _coordinate.x;
		const float _yCoordinate = _coordinate.y;

		// Convertir les degrés en radians
		const float _rad = DegToRad(_degrees);

		// Calculer le cos et sin de l'angle
		const float _cos = cos(_rad);
		const float _sin = sin(_rad);

		// Appliquer la rotation
		const float _newX = (_xCoordinate - _xOrigin) * _cos - (_yCoordinate - _yOrigin) * _sin + _xOrigin;
		const float _newY = (_xCoordinate - _xOrigin) * _sin + (_yCoordinate - _yOrigin) * _cos + _yOrigin;

		return { _newX, _newY };
	}


	FORCEINLINE Vector2f ComputeOrigineToCoordE()
	{
		const float _halfLength = size.x / 2.0f;
		const Vector2f& _origin = {GetPosition().x, GetPosition().y};
		return Vector2f(_origin.x + _halfLength, _origin.y);
	}

	FORCEINLINE void ComputeCoord(const Vector2f _oe)
	{
		const float _width = size.y;
		Vector2f _rightDownCorner = Vector2f(_oe.x, _oe.y + _width / 2.0f);
		Vector2f _righUpCorner = Vector2f(_oe.x, _oe.y - _width / 2.0f);
		
		coordinatesOfCorner.insert(make_pair(RIGHTDOWNCORNER, _rightDownCorner));
		coordinatesOfCorner.insert(make_pair(RIGHTUPCORNER, _righUpCorner));
		coordinatesOfCorner.insert(make_pair(LEFTDOWNCORNER, ComputeOppositeCornerCoordinate(_righUpCorner)));
		coordinatesOfCorner.insert(make_pair(LEFTUPCORNER, ComputeOppositeCornerCoordinate(_rightDownCorner)));
		LogCoordinate();
	}

	FORCEINLINE map<Corner, Vector2f>  InitCoords()
	{
		const Vector2f& _oE = ComputeOrigineToCoordE();
		ComputeCoord(_oE);
		return coordinatesOfCorner;
	}

	FORCEINLINE void LogCoordinate()
	{
		LOG(Warning, "A coords is x: " + to_string(coordinatesOfCorner[RIGHTDOWNCORNER].x) + "y: " + to_string(coordinatesOfCorner[RIGHTDOWNCORNER].y));
		LOG(Warning, "b coords is x: " + to_string(coordinatesOfCorner[LEFTDOWNCORNER].x) + "y: " + to_string(coordinatesOfCorner[LEFTDOWNCORNER].y));
		LOG(Warning, "c coords is x: " + to_string(coordinatesOfCorner[LEFTUPCORNER].x) + "y: " + to_string(coordinatesOfCorner[LEFTUPCORNER].y));
		LOG(Warning, "d coords is x: " + to_string(coordinatesOfCorner[RIGHTUPCORNER].x) + "y: " + to_string(coordinatesOfCorner[RIGHTUPCORNER].y));
	}

	FORCEINLINE map<Corner, Vector2f> RotateAllCoords(const Angle& _radian)
	{
		const float _degrees = RadToDeg(_radian);

		return RotateAllCoords(_degrees);
	}

	FORCEINLINE map<Corner, Vector2f> RotateAllCoords(const float _angle)
	{
		for (pair<Corner, Vector2f> _pair  : coordinatesOfCorner)
		{
			const Vector2f& _newcoordinate = ComputeRotatedCoordinate(_pair.second, _angle);
			coordinatesOfCorner[_pair.first] = _newcoordinate;
		}
		LogCoordinate();
		return coordinatesOfCorner;
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
};