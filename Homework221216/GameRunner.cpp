#include "Framework.h"

GameRunner::GameRunner()
{
    showPlayer = new ShowPlayer;
    shop = new ShopRunner;
    inventory = new InventoryRunner;
    dungeon = new DungeonRunner;
}

GameRunner::~GameRunner()
{
    delete showPlayer;
    delete shop;
    delete inventory;
    delete dungeon;
}

void GameRunner::Run()
{
    requestRender = true;
    requestInput = true;
    while (true) {
        if (curRunner == nullptr) {
            if (requestRender) {
                Render();
                requestRender = false;
            }
            if (requestInput)
                input = Input();
            Update(input);
        }
        else {
            curRunner->Run();
            if (curRunner->IsExit()) {
                Init();
                requestInput = true;
            }
        }
        if (PlayerInstance::Get()->GetStatus()->IsDead())
            Exit();
        if (IsExit())
            break;
    }

    //���� ����
}

void GameRunner::Init()
{
    __super::Init();
    curRunner = nullptr;
}

void GameRunner::Render()
{

    system("cls");
    cout << "[�κ�]" << endl;
    if (cursor == 0)
        cout << "->";
    cout << "\t�÷��̾� ����" << endl;
    if (cursor == 1)
        cout << "->";
    cout << "\t����" << endl;
    if (cursor == 2)
        cout << "->";
    cout << "\t����" << endl;
    if (cursor == 3)
        cout << "->";
    cout << "\t����" << endl;
    if (cursor == 4)
        cout << "->";
    cout << "\t����" << endl;
    if (cursor == 5)
        cout << "->";
    cout << "\t����" << endl;
    cout << "\n==================================\n"
        << "�� : W, �Ʒ� : S, Z: Ȯ�� X: ����\n";


    if (saved) {
        cout << "\n ���̺� \n";
        saved = false;
    }
}

void GameRunner::Update(InputType input)
{
    switch (input)
    {
    case InputType::NONE:
        break;
    case InputType::UP:
        cursor--;
        if (cursor < 0)
            cursor = MAX_MENU-1;

        requestInput = true;
        break;
    case InputType::DOWN:
        cursor = (++cursor) % MAX_MENU;

        requestInput = true;
        break;
    case InputType::YES:
        if (cursor == 0) {
            curRunner = showPlayer;
            curRunner->Init();
        }
        else if (cursor == 1) {
            if (shop != nullptr) {
                curRunner = shop;
                curRunner->Init();
            }
        }
        else if (cursor == 2) {
            if (inventory != nullptr) {
                curRunner = inventory;
                curRunner->Init();
            }
        }
        else if (cursor == 3) {
            if (dungeon != nullptr) {
                curRunner = dungeon;
                curRunner->Init();
            }
        }
        else if (cursor == 4) {
            PlayerInstance::Get()->SavePlayerData();

            saved = true;
        }
        else if (cursor == 5)
            Exit();
        requestInput = true;
        break;
    case InputType::CANCEL:
        Exit();
        requestRender = false;
        requestInput = false;
        break;
    default:
        break;
    }
}