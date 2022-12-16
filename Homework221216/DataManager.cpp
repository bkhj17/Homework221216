#include "Framework.h"

stringstream FileLoader::LoadFile(string filename)
{
	stringstream ss;
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (ifs.fail())
		return ss;

	string s;
	while (!ifs.eof()) {
		getline(ifs, s);

		ss << s << "\n";
	}
	ifs.close();
	return ss;
}

void FileLoader::SaveFile(string filename, stringstream& ss)
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
	delete instance;
}

PlayerData DataManager::GetPlayerData(int level)
{
	return playerLevelTable[level];
}

ItemData DataManager::GetItemData(int itemKey)
{
	return itemTable[itemKey];
}

void DataManager::LoadPlayerLevelTable()
{
	
}

void DataManager::LoadItemTable()
{
}

void DataManager::LoadMonsterTable()
{
}
