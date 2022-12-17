#include "Framework.h"
#include "Monster.h"

Monster::Monster(int key)
{
	SetData(key);
}

void Monster::SetData(int key)
{
	auto loadData = DataManager::Get()->GetMonsterData(key);

	this->key = key;
	characterData = loadData.first;
	info = loadData.second;
}
