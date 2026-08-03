
#pragma once

// Copyright 2026 CH2-Team13-RPG

#include "Battle/battle.h"

#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include <utility>

#include "Player/player.h"
#include "Monster/monster.h"
#include "LevelUp/levelup.h"
#include "Effect/effect.h"
#include "Essence/EssenceOrb.h"
#include "InventorySystem/InventorySystem.h"

namespace {
    const char kField[] = "라벤더 들판";
    const char kForest[] = "검은 숲";
    const char kCanyon[] = "스산한 협곡";
    const char kIceField[] = "로야 빙원";
    const char kVolcano[] = "라플라 화산 지대";
}

Battle::MonsterMap Battle::CreateMonsterMap() {
    Battle::MonsterMap regionMonsters;

    regionMonsters[kField] = {
        MakeFactory(MonsterType::Slime),
        MakeFactory(MonsterType::Zombie),
        MakeFactory(MonsterType::Goblin),
        MakeFactory(MonsterType::WildWolf),
        MakeFactory(MonsterType::Chimera),
    };

    regionMonsters[kForest] = {
        MakeFactory(MonsterType::Ghost),
        MakeFactory(MonsterType::Succubus),
        MakeFactory(MonsterType::Incubus),
        MakeFactory(MonsterType::Ghoul),
        MakeFactory(MonsterType::Werewolf),
    };

    regionMonsters[kCanyon] = {
        MakeFactory(MonsterType::Gargoyle),
        MakeFactory(MonsterType::Margoyle),
        MakeFactory(MonsterType::Mummy),
        MakeFactory(MonsterType::Daemon),
        MakeFactory(MonsterType::Golem),
    };

    regionMonsters[kIceField] = {
        MakeFactory(MonsterType::Griffon),
        MakeFactory(MonsterType::Vampire),
        MakeFactory(MonsterType::Siren),
        MakeFactory(MonsterType::Minotaur),
        MakeFactory(MonsterType::IceElemental),
    };

    regionMonsters[kVolcano] = {
        MakeFactory(MonsterType::HellHound),
        MakeFactory(MonsterType::Wyvern),
        MakeFactory(MonsterType::Salamander),
        MakeFactory(MonsterType::Manticore),
        MakeFactory(MonsterType::Phoenix),
    };

    return regionMonsters;
}
// 지역 선택 함수
std::string Battle::SelectedRegion() {
    std::cout << "===============================\n";
    std::cout << "  어느 지역을 탐색하시겠습니까?\n";
    std::cout << "-------------------------------\n";
    std::cout << "1. 라벤더 들판  2. 검은 숲  3. 스산한 협곡\n";
    std::cout << "4. 로야 빙원  5. 라플라 화산 지대 0. 다시 마을로 \n";
    std::cout << "===============================\n";
    std::cout << "선택한 지역:";
    int region;
    std::cin >> region;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "숫자를 입력해주세요.\n";
        return Battle::SelectedRegion();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (region) {
    case 1:
    {
        choice = "라벤더 들판";
        break;
    }
    case 2:
    {
        choice = "검은 숲";
        break;
    }
    case 3:
    {
        choice = "스산한 협곡";
        break;
    }
    case 4:
    {
        choice = "로야 빙원";
        break;
    }
    case 5:
    {
        choice = "라플라 화산 지대";
        break;
    }
    case 0:
    {
        std::cout << "오늘은 여기까지..마을로 돌아가자.\n";
        choice.clear();
        // VillageMenu();
        break;
    }
    default:
    {
        std::cout << "존재하지 않는 지역입니다.\n";
        std::cout << "이동할 지역을 다시 선택해주세요.\n";
        return Battle::SelectedRegion();
    }
    }
    return choice;
}

void Battle::Encounter(MonsterMap& regionMonsters,
    const std::string& choice, std::unique_ptr<Monster>& m_ptr) {
    auto& monsters = regionMonsters[choice];

    if (monsters.empty()) {
        std::cout << "이 지역엔 몬스터가 없다..\n";
        m_ptr.reset();
        return;
    }

    int idx = rand() % monsters.size();
    auto encountered = monsters[idx]();

    std::cout << "\n당신은 야생의 " << encountered->getName()
        << "와(과) 마주쳤다!\n";
    m_ptr = std::move(encountered);
}
// Player HP 체크
bool Battle::PlayerHealthCheck() {
    Player& player = Player::GetInstance();
    if (player[Pstat::Hp] > 0) {
        playerlive = 1;
    }
    else if (player[Pstat::Hp] <= 0) {
        playerlive = 0;
    }
    return playerlive;
}
// Monster HP 체크
bool Battle::MonsterHealthCheck(Monster& monster) {
    if (monster.gethp() > 0) {
        monsterlive = 1;
    }
    else if (monster.gethp() <= 0) {
        monsterlive = 0;
    }
    return monsterlive;
}
// Player Damage 계산
int Battle::DealDamage(Monster& monster) {
    const Player& readPlayer = Player::GetReadInstance();
    Player& player = Player::GetInstance();
    if (readPlayer[Pstat::Attack] - monster.getdef() <= 0) {
        damage = 1;
    }
    else {
        damage = readPlayer[Pstat::Attack] - monster.getdef();
    }
    return damage;
}
// Monster Damage 계산
int Battle::MonsterDealDamage(Monster& monster) {
    const Player& readPlayer = Player::GetReadInstance();
    Player& player = Player::GetInstance();
    if (monster.getatk() - readPlayer[Pstat::Guard] <= 0) {
        damage = 1;
    }
    else {
        damage = monster.getatk() - readPlayer[Pstat::Guard];
    }
    return damage;
}
// Player 공격 함수
void Battle::Attack(Monster& monster) {
    Player& player = Player::GetInstance();
    monster.sethp(monster.gethp() - DealDamage(monster));
}
// Monster 공격 함수
void Battle::MonsterAttack(Monster& monster) {
    Player& player = Player::GetInstance();
    player[Pstat::Hp] -= MonsterDealDamage(monster);
}

void Battle::HuntRewardGold(int gold) {
    Player& player = Player::GetInstance();
    player[Pstat::Gold] += gold;
    std::cout << gold << " 골드를 획득했습니다!\n";
}
// Battle Menu 선택
void Battle::BattleMenu(Monster& monster, Effect<Monster>& effect) {
    Player& player = Player::GetInstance();
    EssenceOrb& orb = EssenceOrb::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);
    std::cout << "===============================\n";
    std::cout << "      행동을 선택해주세요.\n";
    std::cout << "===============================\n";
    std::cout << "1. 공격  2. 스킬  3. 정수 가방 \n";
    std::cout << "4.아이템\n";
    std::cout << "===============================\n";
    std::cout << "번호를 선택해주요. : ";
    int actionMenu;
    std::cin >> actionMenu;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "숫자를 입력해주세요.\n";
        Battle::BattleMenu(monster, effect);
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (actionMenu) {
    case 1:
    {
        Battle::Attack(monster);
        playerEffect.Bleed();
        break;
    }
    case 2:
    {
        std::cout << "스킬 사용\n";
        orb.EssenceOrb::UseSkill(monster, effect);
        break;
    }
    case 3:
    {
        std::cout << "수집한 정수를 사용합니다.\n";
        player.SetEssence(orb.UseEssence(monster.getName()));
        std::cout << monster.getName()
            << "의 정수를 사용해 수치가 변경됩니다.\n";
        player.ViewStatus();
        break;
    }
    case 4:
    {
        std::cout << "아이템을 사용합니다.\n";
        InventorySystem::GetInstance().ShowInventoryInBattle();
        break;
    }
    default:
    {
        std::cout << "없는 선택지 입니다.\n";
        std::cout << "행동을 다시 선택해주세요.\n";
        Battle::BattleMenu(monster, effect);
        break;
    }
    }
}
// Battle 시스템 오케스트레이션
BattleResult Battle::RunBattle(Monster& monster, Effect<Monster>& effect) {
    Player& player = Player::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);
    while (PlayerHealthCheck() && MonsterHealthCheck(monster)) {
        player.ViewStatus();
        Battle::BattleMenu(monster, effect);
        playerEffect.Tick();
        if (!Battle::PlayerHealthCheck()) break;
        if (!Battle::MonsterHealthCheck(monster)) break;

        Battle::MonsterAttack(monster);
        effect.Bleed();
        effect.Tick();
        if (!Battle::PlayerHealthCheck()) break;
    }
    playerEffect.ClearEffect();
    effect.ClearEffect();
    return PlayerHealthCheck() ? BattleResult::WIN : BattleResult::LOSE;
}



// Battle 이후 선택지
bool Battle::AfterMenu() {
    EssenceOrb& orb = EssenceOrb::GetInstance();
    std::cout << "===============================\n";
    std::cout << "      행동을 선택해주세요.\n";
    std::cout << "===============================\n";
    std::cout << "1. 지역 재탐색  2. 마을로 이동  3. 정수 가방 확인\n";
    std::cout << "4. 아이템 사용\n";
    std::cout << "===============================\n";
    std::cout << "번호를 선택해주요. : ";
    int afterMenu;
    std::cin >> afterMenu;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "숫자를 입력해주세요.\n";
        return Battle::AfterMenu();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (afterMenu) {
    case 1:
    {
        std::cout << "지역을 재탐색합니다.\n";
        return true;
    }
    case 2:
    {
        return false;
    }
    case 3:
    {
        std::cout << "정수 가방을 확인합니다.\n";
        std::cout << orb.GetOrbInfo();
        return true;
    }
    case 4:
    {
        std::cout << "아이템을 사용합니다.\n";
        InventorySystem::GetInstance().ShowInventoryInNormal();
        return true;
    }
    default:
    {
        std::cout << "없는 선택지 입니다.\n";
        std::cout << "행동을 다시 선택해주세요.\n";
        return Battle::AfterMenu();
    }
    }
}

void Battle::BattleLoop() {
    Player& player = Player::GetInstance();
    EssenceOrb& orb = EssenceOrb::GetInstance();
    auto regionMonsters = CreateMonsterMap();
    bool keep = true;

    while (keep) {
        std::string choice = SelectedRegion();

        if (choice.empty()) {
            keep = AfterMenu();
            continue;
        }

        std::unique_ptr<Monster> monster = nullptr;
        Encounter(regionMonsters, choice, monster);

        if (monster == nullptr) {
            keep = AfterMenu();
            continue;
        }

        Effect<Monster> monsterEffect(*monster);
        BattleResult result = RunBattle(*monster, monsterEffect);

        if (result == BattleResult::LOSE) {
            std::cout << "패배하였습니다.\n";
            std::cout << "당신은 가까운 마을의 어딘가에서 다시금 "
                << "눈을 뜰 것 입니다..\n";
            std::cout << "(당신은 HP 50 / MP 20의 데친미역 상태로 "
                << "깨어납니다.)\n";
            player[Pstat::Hp] = 50;
            player[Pstat::Mp] = 20;
            keep = false;
            break;
        }

        if (result == BattleResult::WIN) {
            HuntRewardExp(monster->getExp());
            int rewardGold = 10 + rand() % 41;
            HuntRewardGold(rewardGold);
            // AddItem(monster->getItem());
            orb.AcquireEssence(monster->getName());
            keep = AfterMenu();
        }
    }
    std::cout << "마을로 돌아갑니다.\n";
    // VillageMenu();
}
