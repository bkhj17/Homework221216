#include "Framework.h"

void BaseRunner::Run()
{
    if (requestRender) {
        Render();
        requestRender = false;
    }
    if (requestInput) {
        input = Input();
        requestRender = true;
    }
    Update(input);
    input = InputType::NONE;
}

void BaseRunner::Init()
{
    isExit = false;
    requestRender = true;
    requestInput = true;
    cursor = 0;
}

InputType BaseRunner::Input()
{
    if (!requestInput)
        return InputType::NONE;
    requestInput = false;

    while (1) {
        if (_kbhit()) {
            requestRender = true;
            int c = _getch();
            switch (c)
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