#include "Framework.h"


void ShopRunner::Run()
{
}

void ShopRunner::Update(InputType input)
{
}

void ShopRunner::Render()
{
}


/*
#include "InventoryTest.h"
#include "Shop.h"
#include "ItemNode.h"
#include "DoublyNode.h"
#include "DoublyLinkedList.h"

Shop::Shop()
{
	sellList = new DoublyLinkedList<Item>();
	for (int i = 0; i < ITEM_NUM; i++) {
		sellList->PushBack(Item(i, 0));
	}
}

Shop::~Shop()
{
	playerMoney = nullptr;
	playerList = nullptr;
	sellList = nullptr;
}

void Shop::Init(int* money, DoublyLinkedList<Item>* list)
{
	shopState = ShopState::MENU_SELECT;
	cursor = 0;
	playerMoney = money;
	playerList = list;
	noMoney = false;
	for (auto* node = list->GetFront(); node != nullptr; node = node->next) {
		sellList->Find(node->data.itemKey)->data.count = node->data.count;
	}
}

bool Shop::MenuSelect(const InputType& input)
{
	switch (input)
	{
	case InputType::UP:
		if (--cursor < 0)
			cursor = 2;
		break;
	case InputType::DOWN:
		if (++cursor > 2)
			cursor = 0;
		break;
	case InputType::YES:
		switch (cursor)
		{
		case 0:
			shopState = ShopState::BUY;
			cursor = 0;
			break;
		case 1:
			shopState = ShopState::SELL;
			cursor = 0;
			break;
		case 2:
			shopState = ShopState::OUT;
			break;
		default:
			break;
		}
		cursor = 0;
		break;
	case InputType::CANCEL:
		shopState = ShopState::OUT;
		break;
	}
	return (shopState == ShopState::OUT);
}

void Shop::BuyRun(const InputType& input)
{
	switch (input)
	{
	case InputType::UP:
		if (--cursor < 0) {
			cursor = ITEM_NUM;
		}
		break;
	case InputType::DOWN:
		if (++cursor > ITEM_NUM + 1) {
			cursor = 0;
		}
		break;
	case InputType::YES:
		if (cursor == ITEM_NUM) {
			shopState = ShopState::MENU_SELECT;
			cursor = 0;
		}
		else {
			if (UseMoney(sellList->Find(cursor)->data.data.price)) {
				bool isIn = false;
				for (auto* node = playerList->GetFront(); node != nullptr; node = node->next) {
					if (node->data.itemKey == cursor) {
						node->data.count++;
						isIn = true;
						break;
					}
				}
				if (!isIn) {
					playerList->PushBack(Item(cursor));
				}
			}
		}
		break;
	case InputType::CANCEL:
		shopState = ShopState::MENU_SELECT;
		cursor = 0;
		break;
	default:
		break;
	}
}

void Shop::SellRun(const InputType& input)
{
	switch (input)
	{
	case InputType::UP:
		if (--cursor < 0) {
			cursor = playerList->GetSize();
		}
		break;
	case InputType::DOWN:
		if (++cursor > playerList->GetSize()) {
			cursor = 0;
		}
		break;
	case InputType::YES:
		if (cursor == playerList->GetSize()) {
			shopState = ShopState::MENU_SELECT;
			cursor = 0;
		}
		else {
			auto node = playerList->Find(cursor);
			*playerMoney += node->data.data.price / 2;

			if (--node->data.count == 0)
				playerList->Erase(cursor);

			if (cursor > playerList->GetSize())
				cursor = playerList->GetSize();
		}
		break;
	case InputType::CANCEL:
		shopState = ShopState::MENU_SELECT;
		cursor = 0;
		break;
	default:
		break;
	}
}

bool Shop::Run(const InputType& input)
{
	switch (shopState)
	{
	case Shop::ShopState::MENU_SELECT:
		if (MenuSelect(input))
			return true;
		break;
	case Shop::ShopState::BUY:
		BuyRun(input);
		break;
	case Shop::ShopState::SELL:
		SellRun(input);
		break;
	case Shop::ShopState::OUT:
		return true;
	}

	return false;
}

void Shop::Render()
{
	cout << "[상점]" << endl;
	switch (shopState)
	{
	case Shop::ShopState::MENU_SELECT:
		if(cursor == 0)
			cout << "->";
		cout << "\t산다\n";

		if (cursor == 1)
			cout << "->";
		cout << "\t판다\n";

		if (cursor == 2)
			cout << "->";
		cout << "\t나간다\n";
		break;
	case Shop::ShopState::BUY:
	{
		int key = 0;
		cout << "소지금 : " << *playerMoney << "\n";
		for (auto* node = sellList->GetFront(); node != nullptr; node = node->next) {
			if (cursor == key)
				cout << "->";
			cout << "\t" << ITEM_DATABASE[key].name << "\t " << ITEM_DATABASE[key].price << "\t";
			auto playerData = GetPlayerData(key);
			cout << (playerData != nullptr ? playerData->count : 0) << "개 소지\n";
			key++;
		}

		if (cursor == key)
			cout << "->";
		cout << "\t뒤로\n";
	}
		break;
	case Shop::ShopState::SELL:
	{
		int count = 0;
		cout << "소지금 :" << *playerMoney << "\n";
		if (playerList->Empty()) {
			cout << "소지품 없음\n";
		}
		else {
			for (auto* node = playerList->GetFront(); node != nullptr; node = node->next) {
				if (cursor == count)
					cout << "->";
				cout << "\t" << node->data.data.name << "\t" << node->data.count << "개\t판매가 : " << node->data.data.price / 2 << "\n";
				count++;
			}
		}
		if (cursor == count)
			cout << "->";
		cout << "\t뒤로";
	}
		break;
	}

	cout << "\n==================================\n"
		<< "위 : W, 아래 : S, Z: 확인 X: 뒤로\n";
}

Item* Shop::GetPlayerData(int key)
{
	for (auto* node = playerList->GetFront(); node != nullptr; node = node->next) {
		if (node->data.itemKey == key) {
			return &(node->data);
		}
	}
	return nullptr;
}


bool Shop::UseMoney(int pay)
{
	if (!AblePay(pay))
		return false;

	*playerMoney -= pay;
	return true;
}
*/
