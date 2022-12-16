#pragma once
#define FILE_PLAYER_SAVE "PlayerSaveFile.tsv"

struct PlayerData {
	int level = 1;
	int maxHp = 0;
	int attack = 0;
	int levelUpExp = 999;
};

class PlayerStatus {
public:
	PlayerStatus(string name, PlayerData* data, int curHp, int curExp, int money);
	PlayerStatus(string name, PlayerData* data);
	PlayerStatus(string name, int level);
	~PlayerStatus();

	void SaveStatus(stringstream& ss);

	const string& GetName() { return name; }
private:
	int money = 0;
	int curHp = 0;
	int curExp = 0;
	PlayerData* data = nullptr;
	string name = "플레이어";
};

class PlayerInstance
{
	PlayerInstance();
	~PlayerInstance();
public:
	static PlayerInstance* Get() {
		if (instance == nullptr)
			instance = new PlayerInstance;
		return instance;
	}

	void CreateNewPlayer();
	void LoadSaveData();
	void SavePlayerData();

	void AddItem(int itemKey, int count);


	map<int, Item*>& GetBag() { return bag; }
private:
	static PlayerInstance* instance;

	PlayerStatus* status = nullptr;
	map<int, Item*> bag;
};

