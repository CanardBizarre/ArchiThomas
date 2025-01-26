#include "Plunger.h"
#include "TimerManager.h"
#include "InputManager.h"

Plunger::Plunger(const Vector2f& _size, const string& _path, const IntRect& _rect) : MeshActor(_size, _path, PNG, _rect, "Duck")
{
	animation = CreateComponent<AnimationComponent>();
}

Plunger::Plunger(const Plunger& _other) : MeshActor(_other)
{
	animation = CreateComponent<AnimationComponent>();
}


void Plunger::Construct()
{
	Super::Construct();

	const float _timeBetween = 0.05f;
	const Vector2i& _spriteSize = Vector2i(81, 400);
	const SpriteData& _spritesData = SpriteData(_timeBetween, Vector2i(81, 0), _spriteSize);

	AnimationData _animationData = AnimationData(7, 2.0f, _spritesData);

	animation->AddAnimation(new Animation("Default", GetMesh()->GetShape(), _animationData));
	animation->SetCurrentAnimation("Default");
	M_INPUT.BindAction(Code::Down, [&]() 
		{
			animation->StartAnimation();
			new Timer([&]() { animation->StopAnimation(); }, seconds(1), true, false);
		});
}

void Plunger::Deconstruct()
{
	Super::Deconstruct();
	animation->StopAnimation();
}

void Plunger::BeginPlay()
{

}