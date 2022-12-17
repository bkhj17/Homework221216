#include "Framework.h"

void FileSave::SaveFile(string filename, stringstream& ss)
{
	ofstream ofs;
	ofs.open(filename, ios::out);
	if (ofs.fail())
		return;

	string s;
	while (ss >> s) {
		ofs << s << "\n";
	}

	ofs.close();
}

DataManager* DataManager::instance = nullptr;

DataManager::DataManager()
{
	LoadPlayerLevelTable();
	LoadItemTable();
	LoadMonsterTable();
}

DataManager::~DataManager()
{
}

pair<CharacterData, PlayerExpData> DataManager::GetPlayerData(int level)
{
	return playerLevelTable[level];
}

ItemData DataManager::GetItemData(int itemKey)
{
	return itemTable[itemKey];
}

pair<CharacterData, MonsterInfo> DataManager::GetMonsterData(int monsterKey)
{
	return monsterTable[monsterKey];
}

void DataManager::LoadPlayerLevelTable()
{
	ifstream ifs;
	ifs.open(FILE_PLAYER_LEVEL_TABLE);
	if(ifs.fail()) {
		cout << "캐릭터 레벨 테이블 로드 실패.\n";
		return;
	}

	while (!ifs.eof()) {
		CharacterData cData;
		PlayerExpData eData;
		ifs >> eData.level;
		ifs >> cData.maxHp;
		ifs >> cData.attack;
		ifs >> eData.levelUpExp;
		playerLevelTable[eData.level] = make_pair(cData, eData);
	}
	ifs.close();
}

void DataManager::LoadItemTable()
{
	ifstream ifs;
	ifs.open(FILE_ITEM_TABLE);
	if (ifs.fail()) {
		cout << "아이템 테이블 로드 실패.\n";
		return;
	}

	while (!ifs.eof()) {
		ItemData data;
		ifs >> data.key;
		ifs >> data.name;
		ifs >> data.price;
		itemTable[data.key] = data;
	}
	ifs.close();
}

void DataManager::LoadMonsterTable()
{
	ifstream ifs;
	ifs.open(FILE_MONSTER_TABLE);
	if (ifs.fail()) {
		cout << "몬스터 테이블 로드 실패.\n";
		return;
	}

	while (!ifs.eof()) {
		int monsterKey = 0;
		CharacterData data;
		MonsterInfo mInfo;
		int dropExp = 0;
		
		ifs >> monsterKey;
		ifs >> data.name;
		ifs >> data.maxHp;
		data.curHp = data.maxHp;
		ifs >> data.attack;
		ifs >> mInfo.dropExp;
		ifs >> mInfo.dropMoney;

		monsterTable[monsterKey] = make_pair(data, mInfo);
	}
	ifs.close();

}
