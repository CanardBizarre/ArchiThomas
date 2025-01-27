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

Vector2f MeshActor::ComputeOppositeCornerCoordinate(const Vector2f& _coordinate)
{
	const float _width = GetPosition().x;
	const float _length = GetPosition().y;
	const Vector2f& _coordsRoatated = _coordinate.rotatedBy(degrees(180.0f));
	return Vector2(_coordsRoatated.x + _width * 2.0f,
		_coordsRoatated.y + _length * 2.0f);
}

Vector2f  MeshActor::ComputeRotatedCoordinate(const Vector2f& _coordinate, float _degrees)
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
Vector2f MeshActor::ComputeOrigineToCoordE()
{
	const float _halfLength = size.x / 2.0f;
	const Vector2f& _origin = { GetPosition().x, GetPosition().y };
	return Vector2f(_origin.x + _halfLength, _origin.y);
}

void MeshActor::LogCoordinate()
{
	LOG(Warning, "A coords is x: " + to_string(coordinatesOfCorner[RIGHTDOWNCORNER].x) + "y: " + to_string(coordinatesOfCorner[RIGHTDOWNCORNER].y));
	LOG(Warning, "b coords is x: " + to_string(coordinatesOfCorner[LEFTDOWNCORNER].x) + "y: " + to_string(coordinatesOfCorner[LEFTDOWNCORNER].y));
	LOG(Warning, "c coords is x: " + to_string(coordinatesOfCorner[LEFTUPCORNER].x) + "y: " + to_string(coordinatesOfCorner[LEFTUPCORNER].y));
	LOG(Warning, "d coords is x: " + to_string(coordinatesOfCorner[RIGHTUPCORNER].x) + "y: " + to_string(coordinatesOfCorner[RIGHTUPCORNER].y));
}
void MeshActor::ComputeCoord(const Vector2f _oe)
{
	const float _width = size.y;
	Vector2f _rightDownCorner = Vector2f(_oe.x, _oe.y + _width / 2.0f);
	Vector2f _righUpCorner = Vector2f(_oe.x, _oe.y - _width / 2.0f);

	coordinatesOfCorner.insert(make_pair(RIGHTDOWNCORNER, _rightDownCorner));
	coordinatesOfCorner.insert(make_pair(RIGHTUPCORNER, _righUpCorner));
	coordinatesOfCorner.insert(make_pair(LEFTDOWNCORNER, ComputeOppositeCornerCoordinate(_righUpCorner)));
	coordinatesOfCorner.insert(make_pair(LEFTUPCORNER, ComputeOppositeCornerCoordinate(_rightDownCorner)));
}
map<Corner, Vector2f> MeshActor::InitCoords()
{
	const Vector2f& _oE = ComputeOrigineToCoordE();
	ComputeCoord(_oE);
	LogCoordinate();

	return coordinatesOfCorner;
}

map<Corner, Vector2f> MeshActor::RotateAllCoords(const Angle& _radian)
{
	const float _degrees = RadToDeg(_radian);
	LogCoordinate();

	return RotateAllCoords(_degrees);
}
map<Corner, Vector2f> MeshActor::RotateAllCoords(const float _angle)
{
	for (pair<Corner, Vector2f> _pair : coordinatesOfCorner)
	{
		const Vector2f& _newcoordinate = ComputeRotatedCoordinate(_pair.second, _angle);
		coordinatesOfCorner[_pair.first] = _newcoordinate;
	}
	return coordinatesOfCorner;
}