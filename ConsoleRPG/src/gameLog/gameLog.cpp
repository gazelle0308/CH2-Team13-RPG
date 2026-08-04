#include <iostream>
#include <string>
#include <format>

#include "../include/GameLog/GameLog.h"


void GameLog::addLog(const std::string& logMessage) {
    if (logs.size() >= maxSize) {
        logs.erase(logs.begin());
    }
    logs.push_back(logMessage);
    std::cout << logMessage << std::endl;
}

void GameLog::print(const std::string& text) {
    std::cout << text << std::endl;
}

void GameLog::attackLog(
    const std::string& attacker,
    const std::string& target) {
    addLog(std::format(
        "[공격] {}이(가) {}을(를) 공격합니다.",
        attacker,
        target));
}

void GameLog::damageLog(
    const std::string& target,
    int damage) {
    addLog(std::format(
        "[피해] {}이(가) {} 데미지를 입었습니다.",
        target,
        damage));
}

void GameLog::itemLog(
    const std::string& itemName,
    const std::string& effect) {
    addLog(std::format(
        "[아이템] {} 사용! 효과: {}",
        itemName,
        effect));
}

void GameLog::goldLog(
    int gold, int currentGold) {
    addLog(std::format(
        "[골드] +{} 골드 획득 (보유 골드: {})",
        gold,
        currentGold));
}

void GameLog::addKillMonster(
    const std::string& monsterName) {
    killList[monsterName]++;
    addLog(std::format(
        "[처치] {}을(를) 처치했습니다!",
        monsterName));
}

void GameLog::showKillList() {
    print("=== 몬스터 처치 목록 ===");
    if (killList.empty()) {
        print("아직 처치한 몬스터가 없습니다.");
        return;
    }
    for (const auto& [name, count] : killList) {
        print(std::format("{} : {}마리", name, count));
    }
}

void GameLog::showLogs() {
    if (logs.empty()) {
        print("저장된 로그가 없습니다.");
        return;
    }
    print("===최근 로그(최대 30개)===");
    for (const auto& log : logs) {
        print(log);
    }
}