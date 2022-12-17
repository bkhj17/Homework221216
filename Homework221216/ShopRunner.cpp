#include "Framework.h"

ShopRunner::ShopRunner()
{
	for (int i = 0; i < DataManager::Get()->ItemDataNum(); i++) {
		sellList.push_back(DataManager::Get()->GetItemData(i));
	}
}

ShopRunner::~ShopRunner()
{
}

void ShopRunner::Init()
{
	__super::Init();
	shopState = ShopState::MENU_SELECT;
	cursor = 0;
	noMoney = false;
}

void ShopRunner::Update(InputType input)
{
	switch (shopState)
	{
	case ShopState::MENU_SELECT:
		if (MenuSelect(input))
			Exit();
		break;
	case ShopState::BUY:
		BuyRun(input);
		break;
	case ShopState::SELL:
		SellRun(input);
		break;
	case ShopState::EXIT:
		Exit();
	}
	requestInput = true;
}

void ShopRunner::Render()
{
	system("cls");
	cout << "[상점]" << endl;

	auto playerBag = PlayerInstance::Get()->GetBag();
	if (playerBag == nullptr) {
		cout << "가방 접근 실패\n";
		return;
	}

	switch (shopState)
	{
	case ShopState::MENU_SELECT:
		if (cursor == 0)
			cout << "->";
		cout << "\t산다\n";

		if (cursor == 1)
			cout << "->";
		cout << "\t판다\n";

		if (cursor == 2)
			cout << "->";
		cout << "\t나간다\n";
		break;
	case ShopState::BUY:
	{
		cout << "소지금 : " << PlayerInstance::Get()->GetMoney() << "\n";

		int key = 0;
		for (; key < sellList.size(); key++) {
			if (cursor == key)
				cout << "->";
			cout << "\t" << sellList[key].name << "\t " << sellList[key].price << "\t";
			cout << (PlayerInstance::Get()->HaveItem(key) ?
				(*playerBag)[key]->Count() : 0) << "개 소지\n";
		}
		
		if (cursor == key)
			cout << "->";
		cout << "\t뒤로\n";

	}
	break;
	case ShopState::SELL:
	{

		int count = 0;
		cout << "소지금 :" << PlayerInstance::Get()->GetMoney() << "\n";
		if (playerBag->empty()) {
			cout << "소지품 없음\n";
		}
		else {
			for (auto it = playerBag->begin(); it != playerBag->end(); it++) {
				if (cursor == count)
					cout << "->";
				cout << "\t" << it->second->GetData().name << "\t" << it->second->Count() << "개\t판매가 : " << it->second->GetData().price / 2 << "\n";
				count++;
			}
		}
		if (cursor == count)
			cout << "->";
		cout << "\t뒤로";
	}
	break;
	}

	playerBag = nullptr;
	cout << "\n==================================\n"
		<< "위 : W, 아래 : S, Z: 확인 X: 뒤로\n";
}

bool ShopRunner::MenuSelect(const InputType& input)
{
	switch (input)
	{
	case InputType::NONE:
		break;
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
			shopState = ShopState::EXIT;
			break;
		default:
			break;
		}
		cursor = 0;
		break;
	case InputType::CANCEL:
		shopState = ShopState::EXIT;
		break;
	}


	return (shopState == ShopState::EXIT);
}

void ShopRunner::BuyRun(const InputType& input)
{
	auto playerBag = PlayerInstance::Get()->GetBag();

	switch (input)
	{
	case InputType::UP:
		if (--cursor < 0) {
			cursor = (int)sellList.size();
		}
		break;
	case InputType::DOWN:
		if (++cursor > sellList.size()) {
			cursor = 0;
		}
		break;
	case InputType::YES:
		if (cursor == sellList.size()) {
			shopState = ShopState::MENU_SELECT;
			cursor = 0;
		}
		else {
			if (PlayerInstance::Get()->UseMoney(sellList[cursor].price)) {
				PlayerInstance::Get()->AddItem(cursor);
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

	playerBag = nullptr;
}

void ShopRunner::SellRun(const InputType& input)
{
	auto playerBag = PlayerInstance::Get()->GetBag();

	switch (input)
	{
	case InputType::UP:
		if (--cursor < 0) {
			cursor = (int)playerBag->size();
		}
		break;
	case InputType::DOWN:
		if (++cursor > playerBag->size()) {
			cursor = 0;
		}
		break;
	case InputType::YES:
		if (cursor == playerBag->size()) {
			shopState = ShopState::MENU_SELECT;
			cursor = 0;
		}
		else {
			auto it = playerBag->find(cursor);
			if (it == playerBag->end())
				break;

			PlayerInstance::Get()->GainMoney(it->second->GetData().price / 2);

			if (--(it->second->Count()) == 0)
				playerBag->erase(it);

			if (cursor > playerBag->size())
				cursor = (int)playerBag->size();
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


