#pragma once

#define FILE_PLAYER_LEVEL_TABLE "PlayerLevelTable.tsv"
#define FILE_ITEM_TABLE "ItemTable.tsv"
#define FILE_MONSTER_TABLE "MonsterTable.tsv"

class FileLoader {
public:
	static stringstream LoadFile(string filename);
	static void SaveFile(string filename, stringstream& ss);
};

class DataManager
{
	DataManager();
	~DataManager();
public:
	static DataManager* Get() {
		if (instance == nullptr)
			instance = new DataManager();
		return instance;
	}

	PlayerData GetPlayerData(int level = 1);
	ItemData GetItemData(int itemKey = 0);
private:
	void LoadPlayerLevelTable();
	void LoadItemTable();
	void LoadMonsterTable();


private:
	static DataManager* instance;

	map<int, PlayerData> playerLevelTable;
	map<int, ItemData> itemTable;
	//MonsterTable
};

