#include "Framework.h"

DungeonRunner::DungeonRunner()
{
	nEnemy = 0;
	monsters.resize(10);
	for (int i = 0; i < MAX_ENEMY; i++)
		monsters[i] = new Monster;
	Init();
}

DungeonRunner::~DungeonRunner()
{
	for (int i = 0; i < monsters.size(); i++) {
		if (monsters[i] != nullptr)
			delete monsters[i];
	}
}

void DungeonRunner::Init()
{
	__super::Init();
	dungeonState = DungeonState::SELECT_MENU;
	nEnemy = 0;
	isBoss = false;
}

void DungeonRunner::Run()
{

	while (1) {
		switch (dungeonState)
		{
		case DungeonState::SELECT_MENU:
			dungeonState = SelectMenu();
			break;
		case DungeonState::INPUT_ENEMY_NUM:
		{
			int numEnemy = InputEnemyNum();
			if (numEnemy == 0)
				dungeonState = DungeonState::SELECT_MENU;
			else {
				SetMonsters(numEnemy);
				dungeonState = DungeonState::TURN_START;
			}
		}
		break;
		case  DungeonState::BOSS_BATTLE:
			SetMonsters(1, true);
			cout << "���� ����!!!" << endl;
			isBoss = true;
			Sleep(500);
			dungeonState = DungeonState::TURN_START;
			break;
		case DungeonState::TURN_START:
			TurnStart();
			dungeonState = DungeonState::FIGHT;
			break;
		case DungeonState::FIGHT:
			Fight();
			break;
		case DungeonState::BATTLE_END:
			cout << "���� ����\n";
			if (isBoss) {
				cout << "�����մϴ�. ������ Ŭ�����ϼ̽��ϴ�.\n";
				cin.ignore();
				while (!_kbhit()) {}

				PlayerInstance::Get()->SavePlayerData();
			}
			Sleep(1000);
			dungeonState = DungeonState::EXIT;
			break;
		case DungeonState::GAME_OVER:
			cout << "�÷��̾� ���.... Game Over\n";
			Exit();
			break;
		case DungeonState::EXIT:
			Exit();
			break;
		default:
			break;
		}

		if (IsExit())
			break;
	}
}

DungeonRunner::DungeonState DungeonRunner::SelectMenu()
{
	system("cls");
	cout << "�޴� ����\n1. �Ϲ�����\n2. ����\n3. ���ư���\n-> ";
	int input = 0;
	cin.clear();
	cin.ignore(256, '\n');
	cin >> input;

	switch (input) {
	case 1:
		return DungeonState::INPUT_ENEMY_NUM;
	case 2:
		return DungeonState::BOSS_BATTLE;
	default:
		return DungeonState::EXIT;
	}
}

void DungeonRunner::SetMonsters(int numEnemy, bool isBoss)
{
	nEnemy = 0;
	if (isBoss) {
		monsters[0]->SetData(2);
		nEnemy++;
	}
	else {
		for (int i = 0; i < min(monsters.size(), numEnemy); i++) {
			monsters[i]->SetData(rand() % 2);
			nEnemy++;
		}

		while (nEnemy < numEnemy) {
			monsters.push_back(new Monster);
			monsters.back()->SetData();
			nEnemy++;
		}
	}
}
int DungeonRunner::InputEnemyNum()
{
	int input = 0;
	while (1) {
		cout << "������ ���� ������ ���� �Է��Ͻÿ�(1~" << MAX_ENEMY << ", 0�� ���ư���)-> ";
		cin >> input;

		if (input > MAX_ENEMY)
			cout << "�ʹ� ���� ���� �θ��̾��. �ٽ�\n";
		else if (input < 0)
			cout << "�ΰ������� ������ �ƴ���. �ٽ�\n";
		else
			break;
	}
	return input;
}

void DungeonRunner::TurnStart()
{
	system("cls");
	cout << "====================================\n";
	for (int i = 0; i < nEnemy; i++)
		if (!monsters[i]->IsDead())
			monsters[i]->ShowShortInfo();
	cout << "====================================\n";
	PlayerInstance::Get()->GetStatus()->ShowShortInfo();
	cout << "====================================\n";
}

void DungeonRunner::Fight()
{
	int input = 0;
	//�÷��̾� �ൿ
	cout << "1. ����\n2. ������\n3. ����\n-> ";
	cin >> input;

	int curEnemy = 0;
	for (int i = 0; i < nEnemy; i++) {
		if (!monsters[i]->IsDead())
			curEnemy++;
	}

	switch (input) {
	case 1:
		int target;
		cout << "Ÿ�� ����\n";
		for (int i = 0; i < nEnemy; i++) {
			if (monsters[i]->IsDead())
				cout << "X. ";
			else
				cout << i + 1 << ".";
			monsters[i]->ShowShortInfo();
		}

		while (1) {
			cin >> target;
			target--;
			if (target < 0 || target >= nEnemy || monsters[target]->IsDead()) {
				cout << "�߸��� Ÿ���Դϴ�.\n";
				continue;
			}
			break;
		}

		PlayerInstance::Get()->GetStatus()->Attack(monsters[target]);
		if (monsters[target]->IsDead()) {
			MonsterDead(monsters[target]);
			curEnemy--;
		}
		break;
	case 2:
	{
		cout << "���� ������\n";
		auto playerBag = PlayerInstance::Get()->GetBag();

		if (PlayerInstance::Get()->GetBag()->empty()) {
			cout << "������ ����\n";
			Sleep(1000);
			return;
		}
		for (auto it = playerBag->begin(); it != playerBag->end(); it++) {
			cout << it->first << ". " << it->second->GetData().name << "(" << it->second->Count() << ")\n";
		}

		int itemNum;
		cout << "����� ������ ��ȣ(���:-1) -> ";
		cin >> itemNum;
		if (itemNum == -1) {
			return;
		}

		if (!PlayerInstance::Get()->HaveItem(itemNum)) {
			cout << "�������� �����ϴ�." << endl;
		}
		switch (itemNum) {
		case 0: case 3:
			cout << PlayerInstance::Get()->GetStatus()->Heal(30) << "ȸ���ߴ�.\n";
			break;
		case 1:
		{
			for (int i = 0; i < 3; i++) {
				int r = rand() % nEnemy;
				if (monsters[r]->IsDead()) {
					cout << "�̹� ���� ���Ϳ��� �¾Ҵ�...\n";
					continue;
				}

				monsters[r]->Damaged(10);
				if (monsters[r]->IsDead()) {
					MonsterDead(monsters[i]);
					curEnemy--;
				}
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < nEnemy; i++) {
				if (monsters[i]->IsDead())
					continue;
				monsters[i]->Damaged(30);

				if (monsters[i]->IsDead()) {
					MonsterDead(monsters[i]);
					curEnemy--;
				}
			}
			break;
		}
		case 4:
			PlayerInstance::Get()->GetStatus()->Heal(9999);
			cout << "������ ȸ���ߴ�.\n";
			break;
		default:
			break;
		}

		PlayerInstance::Get()->UseItem(itemNum);
	}
		break;
	default:
		cout << "�����ƴ�...";
		Sleep(1000);
		break;
	}

	if (curEnemy == 0) {
		dungeonState = DungeonState::BATTLE_END;
		Sleep(1000);
		return;
	}

	//���� �ൿ
	for (int i = 0; i < nEnemy; i++) {
		if (monsters[i]->IsDead())
			continue;

		monsters[i]->Attack(PlayerInstance::Get()->GetStatus());
		if (PlayerInstance::Get()->GetStatus()->IsDead()) {
			cout << PlayerInstance::Get()->GetStatus()->GetName() << "�� �������� ���Ҵ�.\n";
			dungeonState = DungeonState::GAME_OVER;
			Sleep(1000);
			return;
		}

		if (monsters[i]->IsDead()) {
			MonsterDead(monsters[i]);
			curEnemy--;
		}
	}

	if (curEnemy == 0) {
		dungeonState = DungeonState::BATTLE_END;
		Sleep(1000);
		return;
	}

	dungeonState = DungeonState::TURN_START;
}

void DungeonRunner::MonsterDead(Monster* dead)
{
	cout << dead->GetName() << "�� ��������.\n";
	PlayerInstance::Get()->GetStatus()->GainExp(dead->GetDropExp());
	cout << "�� " << dead->GetDropMoney() << "�� �����.\n";
	PlayerInstance::Get()->GainMoney(dead->GetDropMoney());
	Sleep(1000);
}

void DungeonRunner::Update(InputType input)
{
}

void DungeonRunner::Render()
{
}
