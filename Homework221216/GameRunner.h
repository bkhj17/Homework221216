#pragma once
class GameRunner : public BaseRunner
{
	static const int MAX_MENU = 6;

	enum class GameState {
		LOBBY,
		SHOW_PLAYER,
		BAG,
		SHOP,
		DUNGEON,
		SAVE,
		EXIT
	};
	GameState gameState = GameState::LOBBY;
public:
	GameRunner();
	~GameRunner();

	// BaseRunner을(를) 통해 상속됨
	virtual void Run() override;

	void Init();
	// BaseRunner을(를) 통해 상속됨
	virtual void Update(InputType input) override;
	virtual void Render() override;

private:
	BaseRunner* curRunner = nullptr;

	ShowPlayer* showPlayer = nullptr;
	ShopRunner* shop = nullptr;
	InventoryRunner* inventory = nullptr;
	DungeonRunner* dungeon = nullptr;

	bool saved = false;
};