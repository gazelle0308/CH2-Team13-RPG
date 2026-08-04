
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
#include "Boss/Boss.h"
#include "Effect/effect.h"

enum class BattleResult { WIN, LOSE };

class Battle {
 private:
  int damage = 0;
  std::string choice;

 public:
  bool playerlive = true;
  bool monsterlive = true;

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
  void Attack(Alatreon& boss);
  void MonsterAttack(Monster& monster);
  void BattleMenu(Monster& monster, Effect<Monster>& effect);

  void HuntRewardGold(int gold);

  bool AfterMenu();

  BattleResult RunBattle(Monster& monster, Effect<Monster>& effect);
  bool BattleLoop();

  void BossBattleMenu(Alatreon& alatreon, Effect<Alatreon>& effect);
  BattleResult BossBattle();
  bool TotalBattleSystem();
};

inline Battle::MonsterFactory MakeFactory(MonsterType type) {
    return [type]() {return std::make_unique<Monster>(type); };
}
