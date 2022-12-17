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
			cout << "보스 출현!!!" << endl;
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
			cout << "전투 종료\n";
			if (isBoss) {
				cout << "축하합니다. 게임을 클리어하셨습니다.\n";
				cin.ignore();
				while (!_kbhit()) {}

				PlayerInstance::Get()->SavePlayerData();
			}
			Sleep(1000);
			dungeonState = DungeonState::EXIT;
			break;
		case DungeonState::GAME_OVER:
			cout << "플레이어 사망.... Game Over\n";
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
	cout << "메뉴 선택\n1. 일반전투\n2. 보스\n3. 돌아가기\n-> ";
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
		cout << "전투에 나올 몬스터의 수를 입력하시오(1~" << MAX_ENEMY << ", 0은 돌아가기)-> ";
		cin >> input;

		if (input > MAX_ENEMY)
			cout << "너무 많은 수를 부르셨어요. 다시\n";
		else if (input < 0)
			cout << "인간적으로 음수는 아니지. 다시\n";
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
	//플레이어 행동
	cout << "1. 공격\n2. 아이템\n3. 도망\n-> ";
	cin >> input;

	int curEnemy = 0;
	for (int i = 0; i < nEnemy; i++) {
		if (!monsters[i]->IsDead())
			curEnemy++;
	}

	switch (input) {
	case 1:
		int target;
		cout << "타겟 선택\n";
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
				cout << "잘못된 타겟입니다.\n";
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
		cout << "소지 아이템\n";
		auto playerBag = PlayerInstance::Get()->GetBag();

		if (PlayerInstance::Get()->GetBag()->empty()) {
			cout << "아이템 없음\n";
			Sleep(1000);
			return;
		}
		for (auto it = playerBag->begin(); it != playerBag->end(); it++) {
			cout << it->first << ". " << it->second->GetData().name << "(" << it->second->Count() << ")\n";
		}

		int itemNum;
		cout << "사용할 아이템 번호(취소:-1) -> ";
		cin >> itemNum;
		if (itemNum == -1) {
			return;
		}

		if (!PlayerInstance::Get()->HaveItem(itemNum)) {
			cout << "아이템이 없습니다." << endl;
		}
		switch (itemNum) {
		case 0: case 3:
			cout << PlayerInstance::Get()->GetStatus()->Heal(30) << "회복했다.\n";
			break;
		case 1:
		{
			for (int i = 0; i < 3; i++) {
				int r = rand() % nEnemy;
				if (monsters[r]->IsDead()) {
					cout << "이미 죽은 몬스터에게 맞았다...\n";
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
			cout << "완전히 회복했다.\n";
			break;
		default:
			break;
		}

		PlayerInstance::Get()->UseItem(itemNum);
	}
		break;
	default:
		cout << "도망쳤다...";
		Sleep(1000);
		break;
	}

	if (curEnemy == 0) {
		dungeonState = DungeonState::BATTLE_END;
		Sleep(1000);
		return;
	}

	//몬스터 행동
	for (int i = 0; i < nEnemy; i++) {
		if (monsters[i]->IsDead())
			continue;

		monsters[i]->Attack(PlayerInstance::Get()->GetStatus());
		if (PlayerInstance::Get()->GetStatus()->IsDead()) {
			cout << PlayerInstance::Get()->GetStatus()->GetName() << "는 쓰러지고 말았다.\n";
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
	cout << dead->GetName() << "가 쓰러졌다.\n";
	PlayerInstance::Get()->GetStatus()->GainExp(dead->GetDropExp());
	cout << "돈 " << dead->GetDropMoney() << "을 얻었다.\n";
	PlayerInstance::Get()->GainMoney(dead->GetDropMoney());
	Sleep(1000);
}

void DungeonRunner::Update(InputType input)
{
}

void DungeonRunner::Render()
{
}
