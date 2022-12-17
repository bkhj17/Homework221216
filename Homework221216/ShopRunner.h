#pragma once
#include "BaseRunner.h"
class ShopRunner : public BaseRunner
{
	enum class ShopState {
		MENU_SELECT,
		BUY,
		SELL, 
		EXIT
	};
	ShopState shopState = ShopState::MENU_SELECT;
public:
	ShopRunner();
	~ShopRunner();
	// BaseRunner을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update(InputType input) override;
	virtual void Render() override;


	bool MenuSelect(const InputType& input);
	void BuyRun(const InputType& input);
	void SellRun(const InputType& input);

	void AddMoney(int gain) { *playerMoney += gain; }
	bool AblePay(int pay) { return *playerMoney >= pay; }

private:
	int cursor = 0;
	bool noMoney = false;;

	int* playerMoney = nullptr;
	vector<ItemData> sellList;	//정렬 불필요
	//DoublyLinkedList<Item>* sellList = nullptr;
};