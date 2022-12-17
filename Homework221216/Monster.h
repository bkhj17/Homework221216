#pragma once

struct MonsterInfo {
    int dropExp = 1;
    int dropMoney = 100;
};

class Monster : public CharacterStatus
{
public:
    Monster(int key = 0);

    int GetDropExp() { return info.dropExp; }
    int GetDropMoney() { return info.dropMoney; }

    void SetData(int key = 0);
private:

    int key = 0;
    MonsterInfo info;
};

