#include "Framework.h"

void BaseRunner::Run()
{
    if (requestRender) {
        Render();
        requestRender = false;
    }
    if (requestInput)
        input = Input();
    Update(input);
}

void BaseRunner::Init()
{
    isExit = false;
    bool requestRender = true;
    bool requestInput = true;
}

InputType BaseRunner::Input()
{

    if (!requestInput)
        return InputType::NONE;
    requestInput = false;

    while (1) {
        if (_kbhit()) {
            requestRender = true;
            switch (_getch())
            {
            case 'w':
                return InputType::UP;
            case 's':
                return InputType::DOWN;
            case 'z':
                return InputType::YES;
            case 'x':
                return InputType::CANCEL;
            default:
                break;
            }
        }
    }
}

void BaseRunner::Update(InputType input)
{
}