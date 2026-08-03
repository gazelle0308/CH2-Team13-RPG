
#pragma once

// Copyright 2026 CH2-Team13-RPG

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include "Monster/monster.h"
#include "Player/player.h"
#include "Boss/boss.h"
#include "Effect/effect.h"

enum class BattleResult { WIN, LOSE };

class Battle {
private:
    int damage;
    std::string choice;

public:
    bool playerlive;
    bool monsterlive;

    using MonsterFactory = std::function<std::unique_ptr<Monster>()>;
    using MonsterMap = std::map<std::string, std::vector <MonsterFactory>>;
    MonsterMap CreateMonsterMap();
    void Encounter(MonsterMap& regionMonsters,
        const std::string& choice, std::unique_ptr<Monster>& m_ptr);

    std::string SelectedRegion();
    bool PlayerHealthCheck();
    bool MonsterHealthCheck(Monster& monster);
    int DealDamage(Monster& monster);
    int MonsterDealDamage(Monster& monster);
    void Attack(Monster& monster);
    void MonsterAttack(Monster& monster);
    void BattleMenu(Monster& monster, Effect<Monster>& effect);

    void HuntRewardGold(int gold);

    bool AfterMenu();

    BattleResult RunBattle(Monster& monster, Effect<Monster>& effect);

    void BattleLoop();
};

inline Battle::MonsterFactory MakeFactory(MonsterType type) {
    return [type]() {return std::make_unique<Monster>(type); };
}
