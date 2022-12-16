#include "Framework.h"
#include "PlayerInstance.h"

PlayerStatus::PlayerStatus(string name, PlayerData* data)
	: name(name), data(data)
{
	curHp = data->maxHp;
}

PlayerStatus::PlayerStatus(string name, int level)
	: name(name)
{
	DataManager::Get()->GetPlayerData(level);
}

PlayerStatus::~PlayerStatus()
{
	delete data;

}

void PlayerStatus::SaveStatus(stringstream& ss)
{
	ss << name << "\n";
	ss << data->level << "\n";
	ss << curHp << "\t" << data->maxHp << "\n";
	ss << curExp << "\t" << data->levelUpExp << "\n";
	ss << money << "\n";
}

/////////////////////////////////////////////////////////////////////

PlayerInstance* instance = nullptr;

PlayerInstance::PlayerInstance()
{
}

PlayerInstance::~PlayerInstance()
{
	delete status;
	for (auto it = bag.begin(); it != bag.end(); ) {
		delete it->second;
		bag.erase(it);
	}
}

void PlayerInstance::CreateNewPlayer()
{
	string inputName;
	cout << "플레이어의 이름을 입력하시오 -> ";
	cin >> inputName;
	//이름 받기
	status = new PlayerStatus(inputName, 1);
}

void PlayerInstance::LoadSaveData()
{
	stringstream ss = FileLoader::LoadFile(FILE_PLAYER_SAVE);

	if (status)
		delete status;

	string name;
	PlayerData* data = new PlayerData;
	int curHp = 0, curExp = 0, money = 0;

	ss >> name;
	ss >> data->level;
	ss >> curHp; 
	ss >> data->maxHp;
	ss >> curExp;
	ss >> data->levelUpExp;
	ss >> money;

	status = new PlayerStatus(name, data, curHp, curExp, money);

}

void PlayerInstance::SavePlayerData()
{
	stringstream ss;
	//PlayerStatus 담기
	status->SaveStatus(ss);

	//bag 담기
	ss << bag.size();
	for (auto it = bag.begin(); it != bag.end(); it++) {
		it->second->GetItemSaveData(ss);
	}

	FileLoader::SaveFile(FILE_PLAYER_SAVE, ss);
}

void PlayerInstance::AddItem(int itemKey, int count)
{
	if (bag.find(itemKey) != bag.end())
		bag[itemKey] = new Item(itemKey, count);
	else
		bag[itemKey]->Count() += count;
}
