// Copyright 2026/07/30 JinHo

#pragma once

#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

enum class Pstat
{
    Hp,
    Mp,
    MaxHp,
    MaxMp,
    BaseHp,
    BaseMp,
    Power,
    Defence,
    BasePower,
    BaseDefence,
    BuffPower,
    BuffDefence,
    Attack,
    Guard,
    Gold,
    Exp,
    Level,
    MaxExp
};



class Player {
 public:
     // operator
     int& operator[](const Pstat target);
     const int& operator[](const Pstat target) const;

    // virtual
    virtual ~Player() = default;

    // Getter
    int GetGold() const;

    int GetLevel() const;
    int GetExp() const;
    int GetMaxExp() const;

    int GetCurrentHp() const;
    int GetCurrentMp() const;

    int GetBaseMaxHp() const;
    int GetBaseMaxMp() const;
    int GetBasePower() const;
    int GetBaseDefence() const;

    int GetCurrentMaxHp() const;
    int GetCurrentMaxMp() const;
    int GetCurrentPower() const;
    int GetCurrentDefence() const;

    std::string GetName() const;
    std::string GetJob() const;

    std::string GetSkill() const;

    // Setter
    void SetGold(int gold);

    void SetLevel(int level);
    void SetExp(int exp);
    void SetMaxExp(int maxExp);


    void SetCurrentHp(int currentHp);
    void SetCurrentMp(int currentMp);

    void SetBaseMaxHp(int baseMaxHp);
    void SetBaseMaxMp(int baseMaxMp);
    void SetBasePower(int basePower);
    void SetBaseDefence(int baseDefence);

    void SetCurrentMaxHp(int currentMaxHp);
    void SetCurrentMaxMp(int currentMaxMp);
    void SetCurrentPower(int currentPower);
    void SetCurrentDefence(int currentDefence);

    void SetName(std::string name);
    void SetJob(std::string job);

    void SetSkill(std::string job);

    // Function
    void SyncToBase(Pstat target);

    void SyncToMax(Pstat target);

    void GetEffect(Pstat target, int num);

 protected:
    explicit Player(std::string name,
                    int level = 1,
                    int baseMaxHp = 200,
                    int baseMaxMp = 100,
                    int basePower = 30,
                    int baseDefence = 5,
                    std::string skill = "Punch!");

    int gold;

    int level;
    int exp;
    int maxExp;

    int currentHp;
    int currentMp;

    int baseMaxHp;
    int baseMaxMp;
    int basePower;
    int baseDefence;

    int currentMaxHp;
    int currentMaxMp;
    int currentPower;
    int currentDefence;

    int buffPower = 0;
    int buffDefence = 0;

    std::string name;
    std::string job;

    std::string skill;
};
