#pragma once

#include "Component.h"

class PhysicComponent : public Component
{
	bool canMove;
	Vector2f velocity;
	float mass;
	float gravity;
	float restitution;
	float friction;
public:
	PhysicComponent(Actor* _owner, const float _mass, const float _restitution, const float _friction);
	PhysicComponent(Actor* _owner, const PhysicComponent* _other);
public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

	void ApplyBounce(const Vector2f& _normal);
	void AddForce(const Vector2f& _force);
};

