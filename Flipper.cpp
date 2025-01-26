#include "Flipper.h"
#include "InputManager.h"
#include "TimerManager.h"

Flipper::Flipper(const Vector2f& _size, const string& _path, const bool _isLeftFlipper, const IntRect& _rect) : MeshActor(_size, _path, PNG, _rect, "Flipper")
{
	isLeftFlipper = _isLeftFlipper;
}

Flipper::Flipper(const Flipper& _other) : MeshActor(_other)
{
	isLeftFlipper = _other.isLeftFlipper;
}

void Flipper::BeginPlay()
{

}

void Flipper::Construct()
{
    Super::Construct();

    if (isLeftFlipper) {
        M_INPUT.BindActionWithState(Code::Left, [this](bool _state)
            {
                if (_state) this->ActiveFlipper(); 
            }, true);
    }
    else {
        M_INPUT.BindActionWithState(Code::Right, [this](bool _state)
            {
                if (_state) this->ActiveFlipper();
            }, true);
    }
}

void Flipper::Deconstruct()
{
	Super::Deconstruct();
}

void Flipper::ActiveFlipper()
{
    const float _rotation = isLeftFlipper ? -30 : 30;
    Rotate(degrees(_rotation));

    new Timer([&]() { SetRotation(degrees(0.0f)); }, seconds(0.1f), true, false);
}