#include "Cloud.h"
#include "AudioManager.h"


Cloud::Cloud(const Vector2f& _size, const string& _path, const IntRect& _rect) : MeshActor(_size, _path, PNG, _rect, "Cloud", 2)
{
	movement = CreateComponent<MovementComponent>(vector<MovementType>({ MT_ROTATEAT}));
}

Cloud::Cloud(const Cloud& _other) : MeshActor(_other)
{
	movement = CreateComponent<MovementComponent>(_other.movement);

}

void Cloud::BeginPlay()
{
	M_AUDIO.PlaySample<SoundSample>("hugooo", MP3);
}

