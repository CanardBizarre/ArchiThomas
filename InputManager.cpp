#include "InputManager.h"



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


