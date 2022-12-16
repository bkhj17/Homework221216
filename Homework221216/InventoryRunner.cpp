#include "Framework.h"

InventoryRunner::InventoryRunner()
{
}

InventoryRunner::~InventoryRunner()
{
}

void InventoryRunner::Run()
{
}

void InventoryRunner::Update(InputType input)
{
    map<int, Item*>* playerBag = &PlayerInstance::Get()->GetBag();

    switch (input)
    {
    case InputType::NONE:
        break;
    case InputType::UP:
        cursor--;
        if (cursor < 0)
            cursor = playerBag->size();

        requestInput = true;
        requestRender = true;
        break;
    case InputType::DOWN:
        cursor = (++cursor) % (playerBag->size() + 1);

        requestInput = true;
        requestRender = true;
        break;
    case InputType::YES:
        if (cursor == playerBag->size()) {
            Exit();
        }
        break;
    case InputType::CANCEL:
        Exit();
        break;
    default:
        break;
    }

    playerBag = nullptr;
}

void InventoryRunner::Render()
{
    map<int, Item*>* playerBag = &PlayerInstance::Get()->GetBag();
 
    cout << "[가방]\n";
    cout << "소지금 : " << /*PlayerInstance::Get()->money <<*/ "\n";
    int cnt = 0;
    for (auto it = playerBag->begin(); it != playerBag->end(); it++) {
        if (cursor == cnt++)
            cout << "->";
        cout << "\t" << it->second->GetData().name << "\t"
            << it->second->Count() << "개\n";
    }
    if (cursor == cnt) {
        cout << "->";
    }
    cout << "\t뒤로 가기";

    cout << "\n==================================\n"
        << "위 : W, 아래 : S, Z: 확인 X: 뒤로\n";

    playerBag = nullptr;
}