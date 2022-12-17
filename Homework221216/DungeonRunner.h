#pragma once
class DungeonRunner : public BaseRunner
{
public:
	DungeonRunner();
	~DungeonRunner();

	// BaseRunner을(를) 통해 상속됨
    virtual void Init() override;

	virtual void Run() override;


private:
    static const int MAX_ENEMY = 10;

    enum class DungeonState {
        SELECT_MENU,
        INPUT_ENEMY_NUM,
        BOSS_BATTLE,
        TURN_START,
        SELECT_COMMAND,
        FIGHT,
        BATTLE_END,
        GAME_OVER,
        EXIT
    };
    DungeonState dungeonState = DungeonState::SELECT_MENU;

    DungeonState SelectMenu();
    void SetMonsters(int numEnemy = 1, bool isBoss = false);

    int InputEnemyNum();
    void TurnStart();

    void Fight();
    void MonsterDead(Monster* dead);

    bool isBoss = false;
    int nEnemy = 0;
    vector<Monster*> monsters;

    // BaseRunner을(를) 통해 상속됨
    virtual void Update(InputType input) override;
    virtual void Render() override;
};

