// Copyright 2026/08/03 minjung

#include "GameManager/GameManager.h"

#include <iostream>

#include "DataBase/ItemDataBase.h"
#include "InventorySystem/InventorySystem.h"
#include "ShopSystem/ShopSystem.h"
#include "Player/Player.h"
#include "GameLog/GameLog.h"
#include "Battle/Battle.h"
#include "PotionWorkshop/PotionWorkshop.h"

void GameManager::Run() {
    Init();
    bool isRunning = true;
    while (isRunning) {
        VillageMenu();
        int choice = GetMenuChoice();
        HandleMenuChoice(choice, isRunning);
    }

    GameLog::GetInstance().print("게임을 종료합니다. 플레이해 주셔서 감사합니다!");
}

void GameManager::Init() {
    Player::GetInstance();

    GameLog::GetInstance().print("모험을 시작합니다!");
}

void GameManager::VillageMenu() const {
    GameLog& log = GameLog::GetInstance();
    log.print("\n===================================");
    log.print(" 1. 모험 2. 인벤토리 3. 플레이어 정보");
    log.print(" 4. 상점   5. 포션제작소  6.로그  0. 게임종료");
    log.print("선택: ");
}
int GameManager::GetMenuChoice() const {
    int choice = -1;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return -1;
    }
    return choice;
}

void GameManager::HandleMenuChoice(int choice, bool& isRunning) {
    GameLog& log = GameLog::GetInstance();

    switch (choice) {
    case 1:
        EnterBattle();
        break;
    case 2:
        InventorySystem::GetInstance().ShowInventoryInNormal();
        break;
    case 3:
        Player::GetInstance().ViewStatus();
        break;
    case 4:
        ShopSystem::GetInstance().ShowShop();
        break;
    case 5:
		PotionWorkshop::GetInstance().ShowPotionWorkshop();
        break;
    case 6:
        GameLog::GetInstance().showLogs();
        break;
    case 0:
        isRunning = false;
        break;
    default:
        log.print("잘못된 선택입니다. 다시 입력해 주세요.");
        break;
    }
}
void GameManager::EnterBattle() {
    Battle battle;
	battle.BattleLoop();
}
