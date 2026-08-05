// Copyright 2026/08/03 minjung

#pragma once
#include <string>
#include <map>
#include <vector>

class GameLog {
private:
    GameLog() = default;
    GameLog(const GameLog&) = delete;
    GameLog& operator=(const GameLog&) = delete;

    int maxSize = 30;
    std::vector<std::string> logs;
    std::map<std::string, int> killList;

    void addLog(const std::string& logMessage);

public:
    static GameLog& GetInstance() {
        static GameLog instance;
        return instance;
    }

    void print(const std::string& text);
    void attackLog(const std::string& attacker, const std::string& target);
    void damageLog(const std::string& target, int damage);
    void itemLog(const std::string& itemName, const std::string& effect);
    void goldLog(int gold, int currentGold);
    void addKillMonster(const std::string& monsterName);
    void showKillList();
    void showLogs();
};
