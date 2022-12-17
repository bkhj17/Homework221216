#include "Framework.h"
#include "PlayerInstance.h"

PlayerStatus::PlayerStatus(CharacterData& cData, PlayerExpData& eData, int money)
	: CharacterStatus(cData), playerLevel(eData), money(money)
{
}

PlayerStatus::PlayerStatus(string name, int level, int money)
	: money(money)
{
	auto data = DataManager::Get()->GetPlayerData(level);
	characterData = data.first;
	characterData.name = name;
	playerLevel = data.second;


	characterData.curHp = characterData.maxHp;
}
PlayerStatus::~PlayerStatus()
{
}

void PlayerStatus::GainExp(int expGain)
{
	playerLevel.curExp += expGain;
	cout << characterData.name << "��/�� " << expGain << "����ġ�� �����\n";
	Sleep(500);

	while (playerLevel.levelUpExp > 0 && playerLevel.curExp >= playerLevel.levelUpExp)
		LevelUp();
}

void PlayerStatus::SaveStatus(stringstream& ss)
{
	ss << characterData.name << "\n";
	ss << playerLevel.level << "\n";
	ss << characterData.curHp << "\t" << characterData.maxHp << "\n";
	ss << characterData.attack << "\n";
	ss << playerLevel.curExp << "\t" << playerLevel.levelUpExp << "\n";
	ss << money << "\n";
}

void PlayerStatus::LevelUp()
{
	auto data = DataManager::Get()->GetPlayerData(playerLevel.level+1);
	data.first.name = characterData.name;
	characterData = data.first;

	playerLevel = data.second;
	characterData.curHp = characterData.maxHp;

	cout << characterData.name << "�� ������ " << playerLevel.level << "�� �Ǿ���!\n";
	ShowInfo();
}

void PlayerStatus::ShowInfo()
{
	cout << characterData.name << "\t���� : " << playerLevel.level << endl
		<< "HP : " << characterData.curHp << " / " << characterData.maxHp << endl
		<< "ATK : " << characterData.attack << endl << endl;
	cout << "Exp : " << playerLevel.curExp << " / " << playerLevel.levelUpExp << endl;
}

/////////////////////////////////////////////////////////////////////

PlayerInstance* PlayerInstance::instance = nullptr;

PlayerInstance::PlayerInstance()
{
	GameStart();
}

PlayerInstance::~PlayerInstance()
{
	delete status;
	for (auto it = bag.begin(); it != bag.end(); ) {
		if(it->second != nullptr)
			delete it->second;
		it = bag.erase(it);
	}
}

void PlayerInstance::GameStart()
{
	int select = 0;
	while (1) {
		cout << "1. �ҷ����� 2. �� ���� -> ";
		cin >> select;
		cin.ignore();

		if (select == 1) {
			LoadSaveData();
			break;
		}
		else if (select == 2) {
			CreateNewPlayer();
			break;
		}
	}
}

void PlayerInstance::CreateNewPlayer()
{
	string inputName;
	cout << "�÷��̾��� �̸��� �Է��Ͻÿ� -> ";
	cin >> inputName;
	//�̸� �ޱ�
	status = new PlayerStatus(inputName, 1);

	SavePlayerData();
}

void PlayerInstance::LoadSaveData()
{
	ifstream ifs;
	ifs.open(FILE_PLAYER_SAVE, ios::in);
	if (ifs.fail()) {
		cout << "���̺� ������ �����ϴ�. ���ο� �����͸� ����ϴ�.\n";
		CreateNewPlayer();
		return;
	}

	if (status)
		delete status;

	CharacterData cData;
	PlayerExpData eData;
	int money = 0;

	ifs >> cData.name 
		>> eData.level
		>> cData.curHp
		>> cData.maxHp
		>> cData.attack
		>> eData.curExp
		>> eData.levelUpExp
		>> money;

	status = new PlayerStatus(cData, eData, money);

	int itemNum = 0;
	ifs >> itemNum;
	while (itemNum--) {
		Item item;
		ifs >> item.GetData().key >> item.GetData().name >> item.GetData().price;
		ifs >> item.Count();
		bag[item.GetData().key] = new Item(item);
	}

	ifs.close();
}

void PlayerInstance::SavePlayerData()
{
	stringstream ss;
	//PlayerStatus ���
	status->SaveStatus(ss);

	//bag ���
	ss << bag.size() << "\n";
	for (auto it = bag.begin(); it != bag.end(); it++) {
		if(it->second != nullptr)
			it->second->GetItemSaveData(ss);
	}

	FileSave::SaveFile(FILE_PLAYER_SAVE, ss);
}

void PlayerInstance::AddItem(int itemKey, int count)
{
	if (bag.find(itemKey) == bag.end())
		bag[itemKey] = new Item(itemKey, count);
	else
		bag[itemKey]->Count() += count;
}

void PlayerInstance::ShowPlayerInfo()
{
	status->ShowInfo();
}

bool PlayerInstance::HaveItem(int itemKey)
{
	return bag.find(itemKey) != bag.end();
}

bool PlayerInstance::UseMoney(int pay)
{
	if (status->money < pay)
		return false;

	status->money -= pay;
	return true;
}

void PlayerInstance::GainMoney(int gain)
{
	status->money += gain;
}

void PlayerInstance::UseItem(int itemKey) {
	if (bag.find(itemKey) == bag.end())
		return;
	
	if ((--bag[itemKey]->Count()) == 0) {
		for (auto it = bag.begin(); it != bag.end();) {
			if (it->first == itemKey) {
				delete it->second;
				it = bag.erase(it);
			}
			else
				it++;
		}
	}
}