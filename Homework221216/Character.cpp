#include "Framework.h"

void CharacterStatus::Attack(CharacterStatus* target)
{
	cout << characterData.name << "은/는 " << target->characterData.name << "을 공격했다!\n";
	Sleep(500);

	int result = target->Attacked(characterData.attack);
	if (result < 0) //반사
		Damaged(characterData.attack);
}

int CharacterStatus::Attacked(int attack)
{
	Damaged(attack);
	return 0;
}

int CharacterStatus::Damaged(int damage)
{
	characterData.curHp -= damage;

	cout << characterData.name << "은/는 " << damage << "의 데미지를 입었다.\n";
	Sleep(500);
	return damage;
}

int CharacterStatus::Heal(int point)
{
	int pre = characterData.curHp;
	characterData.curHp += point;
	if (characterData.curHp > characterData.maxHp)
		characterData.curHp = characterData.maxHp;

	return characterData.curHp - pre;
}

void CharacterStatus::ShowInfo()
{

	cout << characterData.name << endl
		<< "HP : " << characterData.curHp << " / " << characterData.maxHp << endl
		<< "ATK : " << characterData.attack << endl << endl;
}

void CharacterStatus::ShowShortInfo()
{
	cout << characterData.name << "HP(" << characterData.curHp << "/" << characterData.maxHp << ") ATK : " << characterData.attack << "\n";
}
