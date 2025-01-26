#include "Flipper.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "AudioManager.h"

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
    SetRotation(degrees(_rotation));
   
    const u_int& _result = GetRandomNumberInRange(0, 2);
    switch (_result)
    {
    case 0:
        M_AUDIO.PlaySample<SoundSample>("FlipperHit_1");
        break; 
    case 1:
        M_AUDIO.PlaySample<SoundSample>("FlipperHit_2");
        break;
    case 2:
        M_AUDIO.PlaySample<SoundSample>("FlipperHit_3");
        break;
    default:
        break;
    }
      
    

    new Timer([&]() { SetRotation(degrees(0.0f)); }, seconds(0.1f), true, false);
}