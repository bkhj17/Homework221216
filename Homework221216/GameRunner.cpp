#include "Framework.h"

void GameRunner::Run()
{
    while (true) {
        if (curRunner == nullptr) {
            __super::Run();
        }
        else {
            curRunner->Run();
            if (curRunner->IsExit()) {
                curRunner = nullptr;
            }
        }
        if (IsExit())
            break;
    }

    //���� ����
}

void GameRunner::Render()
{

    system("cls");
    cout << "[�κ�]" << endl;
    if (cursor == 0)
        cout << "->";
    cout << "\t����" << endl;
    if (cursor == 1)
        cout << "->";
    cout << "\t����" << endl;
    if (cursor == 2)
        cout << "->";
    cout << "\t����" << endl;
    cout << "\n==================================\n"
        << "�� : W, �Ʒ� : S, Z: Ȯ�� X: ����\n";
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
            cursor = 2;

        requestInput = true;
        break;
    case InputType::DOWN:
        cursor = (++cursor) % 3;

        requestInput = true;
        break;
    case InputType::YES:
        if (cursor == 0) {
            if (shop != nullptr) {
                curRunner = shop;
                shop->Init();
            }
        }
        else if (cursor == 1) {
            if (inventory != nullptr) {
                curRunner = inventory;
                shop->Init();
            }
        }
        else if (cursor == 2)
            gameState = GameState::EXIT;
        cursor = 0;
        requestInput = true;
        break;
    case InputType::CANCEL:
        gameState = GameState::EXIT;
        requestRender = false;
        requestInput = false;
        break;
    default:
        break;
    }
}

/*
#include "InventoryTest.h"
#include <iostream>
#include "ItemNode.h"
#include "Node.h"
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "Shop.h"
#include <conio.h>

InventoryTest::InventoryTest()
{
    list = new DoublyLinkedList<Item>();
    shop = new Shop();
}

InventoryTest::~InventoryTest()
{
    delete list;
    delete shop;
}

void InventoryTest::RunLobby()
{
}

void InventoryTest::RunBag()
{
}

void InventoryTest::RunShop()
{
    if (shop->Run(input))
        gameState = GameState::LOBBY;
    requestRender = true;
    requestInput = true;
}

void InventoryTest::Run()
{
    gameState = GameState::LOBBY;
    requestInput = true;
    requestRender = true;
    money += 3000;

    while (1) {
        Render();
        input = GetInput();
        switch (gameState)
        {
        case InventoryTest::GameState::LOBBY:
            RunLobby();
            break;
        case InventoryTest::GameState::BAG:
            RunBag();
            break;
        case InventoryTest::GameState::SHOP:
            RunShop();
            break;
        case InventoryTest::GameState::EXIT:
            break;
        }
        if (gameState == GameState::EXIT)
            break;
    }
}

void InventoryTest::Render()
{
    if (!requestRender)
        return;
    requestRender = false;


    //��Ȳ ǥ�� : ����, ����, �κ�
    //��Ȳ��
}

void InventoryTest::AddItem(int id, int cnt)
{
    for (auto* node = list->GetFront(); node != nullptr; node = node->next) {
        if (node->data.itemKey == id) {
            node->data.count += cnt;
            return;
        }
    }

    list->PushBack(Item(id, cnt));
}

*/