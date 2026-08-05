
#pragma once

// Copyright 2026 CH2-Team13-RPG

#include "Battle/battle.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include <utility>
#include <random>
#include <algorithm>

#include "GameLog/GameLog.h"
#include "Player/player.h"
#include "Monster/monster.h"
#include "Boss/Boss.h"
#include "LevelUp/levelup.h"
#include "Effect/effect.h"
#include "Essence/EssenceOrb.h"
#include "InventorySystem/InventorySystem.h"
#include "Utility/Utility.h"

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

std::string Battle::SelectedRegion() {
    StartLine();
    std::cout << "   어느 지역을 탐색하시겠습니까?\n";
    StartLine();
    std::cout << "1. 라벤더 들판  2. 검은 숲  3. 스산한 협곡\n";
    std::cout << "4. 로야 빙원  5. 라플라 화산 지대 0. 다시 마을로 \n";
    StartLine();
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, monsters.size() - 1);
    size_t idx = dist(gen);

    auto encountered = monsters[idx]();

    Player& player = Player::GetInstance();
    encountered->generateStats(
        player.GetLevel(),
        player.GetCurrentMaxHp(),
        player.GetCurrentMaxMp(),
        player.GetCurrentPower(),
        player.GetCurrentDefence()
    );

    std::cout << "\n당신은 야생의 " << encountered->getName()
        << "와(과) 마주쳤다!\n";
    m_ptr = std::move(encountered);
}

bool Battle::PlayerHealthCheck() {
    Player& player = Player::GetInstance();
    if (player[Pstat::Hp] > 0) {
        playerlive = 1;
    } else if (player[Pstat::Hp] <= 0) {
        playerlive = 0;
    }
    return playerlive;
}

bool Battle::MonsterHealthCheck(Monster& monster) {
    if (monster.gethp() > 0) {
        monsterlive = 1;
    } else if (monster.gethp() <= 0) {
        monsterlive = 0;
    }
    return monsterlive;
}

int Battle::DealDamage(Monster& monster) {
    const Player& readPlayer = Player::GetReadInstance();
    Player& player = Player::GetInstance();
    if (readPlayer[Pstat::Attack] - monster.getdef() <= 0) {
        damage = 1;
    } else {
        damage = readPlayer[Pstat::Attack] - monster.getdef();
    }
    return damage;
}

int Battle::MonsterDealDamage(Monster& monster) {
    const Player& readPlayer = Player::GetReadInstance();
    Player& player = Player::GetInstance();
    if (monster.getatk() - readPlayer[Pstat::Guard] <= 0) {
        damage = 1;
    } else {
        damage = monster.getatk() - readPlayer[Pstat::Guard];
    }
    return damage;
}

void Battle::Attack(Monster& monster) {
    GameLog& log = GameLog::GetInstance();
    int hpBefore = monster.gethp();
    int dmg = DealDamage(monster);
    monster.sethp(hpBefore - dmg);

    log.attackLog("플레이어", monster.getName());
    log.damageLog(monster.getName(), dmg);

    std::cout << "(" << monster.getName() << " HP: "
        << hpBefore << " -> " << monster.gethp() << ")\n";
}

void Battle::Attack(Alatreon& boss) {
    GameLog& log = GameLog::GetInstance();

    const Player& readPlayer = Player::GetReadInstance();

    int hpBefore = boss.gethp();
    int dmg = std::max(readPlayer[Pstat::Attack] - boss.getdef(), 1);

    boss.sethp(hpBefore - dmg);

    log.attackLog("플레이어", boss.getName());
    log.damageLog(boss.getName(), dmg);

    std::cout << "(" << boss.getName() << " HP: "
        << hpBefore << " -> " << boss.gethp() << ")\n";
}

void Battle::MonsterAttack(Monster& monster) {
    GameLog& log = GameLog::GetInstance();
    Player& player = Player::GetInstance();
    int hpBefore = player[Pstat::Hp];
    int dmg = MonsterDealDamage(monster);
    player[Pstat::Hp] -= dmg;

    log.attackLog(monster.getName(), "플레이어");
    log.damageLog("플레이어", dmg);

    std::cout << "(내 HP: " << hpBefore << " -> " << player[Pstat::Hp] << ")\n";
}

void Battle::ViewMonsterStatus(Monster& monster) {
    StartLine();
    std::cout << "[" << monster.getName() << "]\n";
    std::cout << "HP: " << monster.gethp() << " "
        << "MP: " << monster.getmp() << "\n";
    std::cout << "공격력: " << monster.getatk()
        << "  방어력: " << monster.getdef() << "\n";
    StartLine();
}

void Battle::HuntRewardGold(int gold) {
    GameLog& log = GameLog::GetInstance();
    Player& player = Player::GetInstance();

    player[Pstat::Gold] += gold;

    log.goldLog(gold, player[Pstat::Gold]);
}

void Battle::BattleMenu(Monster& monster, Effect<Monster>& effect) {
    Player& player = Player::GetInstance();
    EssenceOrb& orb = EssenceOrb::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);

    bool turnEnded = false;

    while (!turnEnded) {
        StartLine();
        std::cout << "      행동을 선택해주세요.\n";
        StartLine();
        std::cout << "1. 공격  2. 스킬  3. 정수 가방 \n";
        std::cout << "4.아이템\n";
        StartLine();
        std::cout << "번호를 선택해주요. : ";
        int actionMenu;
        std::cin >> actionMenu;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "숫자를 입력해주세요.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (actionMenu) {
        case 1:
        {
            Battle::Attack(monster);
            playerEffect.Bleed();
            turnEnded = true;
            break;
        }
        case 2:
        {
            std::cout << "스킬 사용\n";
            orb.EssenceOrb::UseSkill(monster, effect);
            turnEnded = true;
            break;
        }
        case 3:
        {
            std::cout << "수집한 정수를 사용합니다.\n";
            std::cout << orb.GetOrbInfo();
            int essenceNumber;
            std::cout << "번호를 선택해주요. : ";
            std::cin >> essenceNumber;
            player.SetEssence(orb.UseEssence(essenceNumber));
            std::cout << "정수를 사용해 수치가 변경됩니다.\n";
            player.ViewStatus();
            turnEnded = true;
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
            break;
        }
        }
    }
}

void Battle::BossBattleMenu(Alatreon& alatreon, Effect<Alatreon>& effect) {
    Player& player = Player::GetInstance();
    EssenceOrb& orb = EssenceOrb::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);

    bool turnEnded = false;

    while (!turnEnded) {
        StartLine();
        std::cout << "      행동을 선택해주세요.\n";
        StartLine();
        std::cout << "1. 공격  2. 스킬  3. 정수 가방 \n";
        std::cout << "4.아이템\n";
        StartLine();
        std::cout << "번호를 선택해주요. : ";
        int actionMenu;
        std::cin >> actionMenu;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "숫자를 입력해주세요.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (actionMenu) {
        case 1:
        {
            Battle::Attack(alatreon);
            playerEffect.Bleed();
            turnEnded = true;
            break;
        }
        case 2:
        {
            std::cout << "스킬 사용\n";
            orb.EssenceOrb::UseSkill(alatreon, effect);
            turnEnded = true;
            break;
        }
        case 3:
        {
            std::cout << "수집한 정수를 사용합니다.\n";
            std::cout << orb.GetOrbInfo();
            int essenceNumber;
            std::cin >> essenceNumber;
            player.SetEssence(orb.UseEssence(essenceNumber));
            std::cout << "정수를 사용해 수치가 변경됩니다.\n";
            player.ViewStatus();
            turnEnded = true;
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
            break;
        }
        }
    }
}


BattleResult Battle::RunBattle(Monster& monster, Effect<Monster>& effect) {
    Player& player = Player::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    while (PlayerHealthCheck() && MonsterHealthCheck(monster)) {
        player.ViewStatus();
        Battle::ViewMonsterStatus(monster);
        Battle::BattleMenu(monster, effect);
        playerEffect.Tick();
        if (!Battle::PlayerHealthCheck()) break;
        if (!Battle::MonsterHealthCheck(monster)) break;


        if (monster.getmp() > 0) {
            if (dist(gen) == 0) {
                Battle::MonsterAttack(monster);
                effect.Bleed();
            } else {
                monster.Skill(effect);
            }
        } else {
            Battle::MonsterAttack(monster);
        }
        effect.Tick();
        if (!Battle::PlayerHealthCheck()) break;
        Battle::ClearScreen();
    }
    playerEffect.ClearEffect();
    effect.ClearEffect();
    return PlayerHealthCheck() ? BattleResult::WIN : BattleResult::LOSE;
}

bool Battle::AfterMenu() {
    EssenceOrb& orb = EssenceOrb::GetInstance();
    StartLine();
    std::cout << "      행동을 선택해주세요.\n";
    StartLine();
    std::cout << "1. 지역 재탐색  2. 마을로 이동  3. 정수 가방 확인\n";
    std::cout << "4. 아이템 사용  5. 아이템 조회\n";
    StartLine();
    std::cout << "번호를 선택해주요: ";
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
        InventorySystem::GetInstance().ShowInventoryInBattle();
        return true;
    }
    case 5:
    {
        std::cout << "아이템을 조회합니다.\n";
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

BattleResult Battle::BossBattle() {
    int isWin = 2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    Player& player = Player::GetInstance();
    Effect<Player>& playerEffect =
        Effect<Player>::GetPlayerInstance(player);

    Alatreon boss;
    Effect<Alatreon> bossEffect(boss);

    while (isWin != 0 && isWin != 1) {
        boss.StartTurn();

        Battle::BossBattleMenu(boss, bossEffect);

        if (boss.getmp() > 0) {
            if (dist(gen) == 0) {
                boss.AlatreonAttack();
                boss.BeforeEffect();
                bossEffect.Bleed();
                boss.AfterEffect();
            } else {
                boss.AlatreonSkill();
            }
        } else {
            boss.AlatreonAttack();
            boss.BeforeEffect();
            bossEffect.Bleed();
            boss.AfterEffect();
        }

        boss.BeforeEffect();
        bossEffect.Tick();
        playerEffect.Tick();
        boss.EndTurn();

        isWin = boss.IsWin();
    }
    if (isWin == 1) {
        std::cout << boss.getName() << " 을 쓰러뜨렸습니다!!\n";
        return BattleResult::WIN;
    } else if (isWin == 0) {
        return BattleResult::LOSE;
    }
}

bool Battle::BattleLoop() {
    Player& player = Player::GetInstance();
    EssenceOrb& orb = EssenceOrb::GetInstance();
    auto regionMonsters = CreateMonsterMap();
    bool keep = true;
    bool bossClear = false;

    std::cout << "================================\n";
    std::cout << "         모험을 시작합니다.\n";

    while (keep) {
        std::string choice = SelectedRegion();

        if (choice.empty()) {
            std::cout << "마을로 돌아갑니다.\n";
            keep = false;
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
            GameLog& log = GameLog::GetInstance();
            log.addKillMonster(monster->getName());

            HuntRewardExp(monster->getexp());

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> goldDist(10, 50);
            int rewardGold = goldDist(gen);
            HuntRewardGold(rewardGold);
            InventorySystem::GetInstance().AcquireItem(monster->getDropItem(), 1, true);
            GameLog::GetInstance().addKillMonster(monster->getName());  // 임의 추가
            orb.AcquireEssence(monster->getName());
            if (orb.AllCollection()) {
                StartLine();
                std::cout << "   모든 정수를 모은 당신의 앞에\n";
                std::cout << "             (보스)\n";
                std::cout << "        황흑룡 알바트리온\n";
                std::cout << "       이 모습을 드러냅니다..\n";
                StartLine();
                BattleResult bossResult = Battle::BossBattle();

                if (bossResult == BattleResult::LOSE) {
                    std::cout << "보스전에서 패배하였습니다.\n";
                    std::cout << "당신은 가까운 마을의 어딘가에서"
                              << "다시금 눈을 뜰 것 입니다..\n";
                    std::cout << "(당신은 HP 50 / MP 20의 데친미역 상태로 "
                              << "깨어납니다.)\n";
                    player[Pstat::Hp] = 50;
                    player[Pstat::Mp] = 20;
                    keep = false;
                    continue;
                }

                if (bossResult == BattleResult::WIN) {
                    std::cout << "알바트리온을 쓰러뜨린 당신은 마을의"
                              << "[수호자]로 기억되었습니다.\n";
                    std::cout << "\n";
                    keep = false;
                    bossClear = true;
                    continue;
                }
            }
            keep = AfterMenu();
        }
    }
    if (bossClear == true) {
        return true;
    } else {
        return false;
    }
}

bool Battle::TotalBattleSystem() {
    bool cleared = Battle::BattleLoop();
    if (cleared) {
        StartLine();
        std::cout << "           GAME CLEAR!!\n";
        StartLine();
    }
    if (!cleared) {
        std::cout << "마을로 돌아갑니다.\n";
    }
    return cleared;
}

void Battle::ClearScreen() const
{
    std::cout << std::endl;
    std::cout << "...아무 키나 누르세요..." << std::endl;

    (void)_getch();

    system("cls");
}
