#pragma once
#include <string>
#include <map>
#include <vector>

class GameLog {
 private:
    int maxSize = 30;
    std::vector<std::string> logs;
    std::map<std::string, int> killList;

    void addLog(const std::string& logMessage);

 public:
    void print(const std::string& text);
    void attackLog(const std::string& attacker, const std::string& target);
    void damageLog(const std::string& target, int damage);
    void itemLog(const std::string& itemName, const std::string& effect);
    void goldLog(int gold, int currentGold);
    void addKillMonster(const std::string& monsterName);
    void showKillList();
	void showLogs();
};
