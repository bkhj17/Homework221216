#pragma once
struct CharacterData {
    string name;
    int curHp = 1;
    int maxHp = 1;
    int attack = 0;
};

class CharacterStatus
{
public:
    CharacterStatus(CharacterData cData) : characterData(cData) {}
    CharacterStatus() {}

    void Attack(CharacterStatus* target);
    virtual int Attacked(int attack);
    int Damaged(int damage);

    int Heal(int point);

    virtual void ShowInfo();
    virtual void ShowShortInfo();

    const string& GetName() { return characterData.name; }

    bool IsDead() { return characterData.curHp <= 0; }
protected:
    CharacterData characterData;
};
