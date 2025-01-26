#pragma once
#include "MeshActor.h"
#include "PhysicComponent.h"
class Ball : public MeshActor
{
	PhysicComponent* physic;
public:
	FORCEINLINE PhysicComponent* GetPhysic() const
	{
		if (!physic)
		{
			LOG(Warning, "PhysicComponent est nullptr");
			return nullptr;
		}
		return physic;
	}
public:
	Ball(const float _radius);
	Ball(const Ball& _other);
public:
	virtual void Construct() override;
};

