#pragma once
#define FILE_PLAYER_SAVE "PlayerSaveFile.tsv"

struct PlayerExpData {
	int level = 1;
	int curExp = 0;
	int levelUpExp = 999;
};

class PlayerStatus : public CharacterStatus {
	friend class PlayerInstance;

	static const int START_MONEY = 2000;
public:
	PlayerStatus(CharacterData&, PlayerExpData&, int money);
	PlayerStatus(string name, int level = 1, int money = START_MONEY);
	~PlayerStatus();

	void GainExp(int expGain);
	void LevelUp();
	
	void SaveStatus(stringstream& ss);

	void ShowInfo();

	int GetLevel() { return playerLevel.level; }
private:
	int money = START_MONEY;
	PlayerExpData playerLevel;
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
	static void Delete() { if(instance != nullptr)	delete instance; }

	PlayerStatus* GetStatus() { return status; }

	void GameStart();

	void CreateNewPlayer();
	void LoadSaveData();
	void SavePlayerData();

	void ShowPlayerInfo();

	void AddItem(int itemKey, int count = 1);
	bool HaveItem(int itemKey);

	const int& GetMoney() { 
			
		return status->money; 
	}
	bool UseMoney(int pay);
	void GainMoney(int gain);

	map<int, Item*>* GetBag() { 
		return &bag; 
	}
	void UseItem(int itemKey);
private:
	static PlayerInstance* instance;

	PlayerStatus* status = nullptr;
	map<int, Item*> bag;
};
