#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Effect/effect.h"


enum class MonsterType
{
    Slime,
    Zombie,
    Goblin,
    WildWolf,
    Chimera,

    Ghost,
    Succubus,
    Incubus,
    Ghoul,
    Werewolf,

    Gargoyle,
    Margoyle,
    Mummy,
    Daemon,
    Golem,

    Griffon,
    Vampire,
    Siren,
    Minotaur,
    IceElemental,

    HellHound,
    Wyvern,
    Salamander,
    Manticore,
    Phoenix
};


class Monster
{
private:

    // 몬스터 기본 경험치 고정
    static constexpr int DEFAULT_EXP = 20;

    int hp;
    int mp;
    int atk;
    int def;

    // 경험치 추가
    int exp;

    // 강화몹 추가경험치
    int bonusExp;

    std::string name;

    // 드랍 아이템
    std::string dropItem;

    // 지역별 난이도, 경험치 조절
    float regionMultiplier;
    float expMultiplier;


    float hpMultiplier;
    float mpMultiplier;
    float atkMultiplier;
    float defMultiplier;


    MonsterType type;


public:

    Monster(MonsterType monsterType);

    void Skill(Effect<Monster>& effect);


    int gethp() const;
    int getmp() const;
    int getatk() const;
    int getdef() const;

    int getexp() const;
    int getbonusExp() const;


    void sethp(int value);
    void setmp(int value);
    void setatk(int value);
    void setdef(int value);

    void setexp(int value);
    void setbonusExp(int value);

    // 경험치 계산 함수 추가
    int calculateExp();


    std::string getName() const;
    std::string getDropItem() const;

    float getRegionMultiplier() const;
    float getExpMultiplier() const;


    void generateStats(
        int playerLevel,
        int playerMaxHp,
        int playerMaxMp,
        int playerPower,
        int playerDefence
    );


private:

    int randomRange(
        int minValue,
        int maxValue
    );


    void setMonsterData(
        MonsterType monsterType
    );

};


#endif