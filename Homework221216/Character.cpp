#include "Framework.h"

void CharacterStatus::Attack(CharacterStatus* target)
{
	cout << characterData.name << "��/�� " << target->characterData.name << "�� �����ߴ�!\n";
	Sleep(500);

	int result = target->Attacked(characterData.attack);
	if (result < 0) //�ݻ�
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

	cout << characterData.name << "��/�� " << damage << "�� �������� �Ծ���.\n";
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
