#include "InputManager.h"
#include "CameraManager.h"

void  MyInput::InputManager::ConsumeData(RenderWindow& _window)
{
    while (const optional _event = _window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            _window.close();
        }

        else if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
        {
            for (InputData& _inputData : inputData)
            {
                if (_inputData.TryToExcute(_key)) break;
            }
        }

        else if (const Event::MouseMoved* _mouse = _event->getIf<Event::MouseMoved>())
        {
            M_CAMERA.GetCurrent()->SetPosition(CAST(Vector2f, _mouse->position));
            LOG(Warning, "Mouse pos X:" + to_string(_mouse->position.x) + " Y:" + to_string(_mouse->position.y));
        }
    }
}

void MyInput::InputManager::BindAction(const vector<Code>& _codes, const function<void()>& _callback)
{
    inputData.push_back(InputData(_callback, _codes, _codes.empty()));
}

void MyInput::InputManager::BindAction(const Code& _codes, const function<void()>& _callback)
{
    inputData.push_back(InputData(_callback, { _codes }));
}

//void MyInput::InputManager::BindAction(const Code& _codes, const function<void(bool)>& _callback, bool flag)
void MyInput::InputManager::BindActionWithState(const Code& _codes, const function<void(bool)>& _callback, bool _state)
{
    inputData.push_back(InputData(
        [callback = _callback, _state]() { callback(_state); }, // Capture le callback et l'état par copie
        { _codes }
    ));
}
