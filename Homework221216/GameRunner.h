#pragma once
class GameRunner : public BaseRunner
{
	static const int MAX_MENU = 3;

	enum class GameState {
		LOBBY,
		BAG,
		SHOP,
		EXIT,
	};
	GameState gameState = GameState::LOBBY;
public:
	// BaseRunner을(를) 통해 상속됨
	virtual void Run() override;

	void Init();
	// BaseRunner을(를) 통해 상속됨
	virtual void Update(InputType input) override;
	virtual void Render() override;

private:
	BaseRunner* curRunner = nullptr;

	ShopRunner* shop = nullptr;
	InventoryRunner* inventory = nullptr;
	DungeonRunner* dunfeon = nullptr;
};


/*
struct Item;

class InventoryTest
{
	InputType input = InputType::NONE;


public:
	InventoryTest();
	~InventoryTest();

	InputType GetInput();
	void RunLobby();
	void RunBag();
	void RunShop();
	void Run();
	void Render();

	void AddItem(int id, int cnt);

private:
	int money = 0;
	int cursor = 0;
	DoublyLinkedList<Item>* list;

	class Shop* shop = nullptr;
};

*/