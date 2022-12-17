#pragma once

#define FILE_PLAYER_LEVEL_TABLE "PlayerLevelTable.tsv"
#define FILE_ITEM_TABLE "ItemTable.tsv"
#define FILE_MONSTER_TABLE "MonsterTable.tsv"

class FileSave {
public:
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
	static void Delete() { if(instance != nullptr) delete instance; }

	pair<CharacterData, PlayerExpData> GetPlayerData(int level = 1);
	ItemData GetItemData(int itemKey = 0);
	pair<CharacterData, MonsterInfo> GetMonsterData(int monsterKey = 0);
	int ItemDataNum() { return (int)itemTable.size(); }
private:
	void LoadPlayerLevelTable();
	void LoadItemTable();
	void LoadMonsterTable();


private:
	static DataManager* instance;

	map<int, pair<CharacterData, PlayerExpData>> playerLevelTable;
	map<int, ItemData> itemTable;
	map<int, pair<CharacterData, MonsterInfo>> monsterTable;
	//MonsterTable
};

