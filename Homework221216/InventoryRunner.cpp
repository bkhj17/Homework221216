#include "Framework.h"

InventoryRunner::InventoryRunner()
{
}

InventoryRunner::~InventoryRunner()
{
}

void InventoryRunner::Update(InputType input)
{
    auto playerBag = PlayerInstance::Get()->GetBag();

    switch (input)
    {
    case InputType::NONE:
        break;
    case InputType::UP:
        cursor--;
        if (cursor < 0)
            cursor = (int)playerBag->size();

        requestInput = true;
        break;
    case InputType::DOWN:
        cursor = (++cursor) % (playerBag->size() + 1);

        requestInput = true;
        break;
    case InputType::YES:
        if (cursor == playerBag->size()) {
            Exit();
        }
        requestInput = true;
        break;
    case InputType::CANCEL:
        Exit();
        requestInput = true;
        break;
    default:
        break;
    }
}

void InventoryRunner::Render()
{
    auto playerBag = PlayerInstance::Get()->GetBag();
 
    system("cls");
    cout << "[가방]\n";
    cout << "소지금 : " << PlayerInstance::Get()->GetMoney() << "\n";
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

}