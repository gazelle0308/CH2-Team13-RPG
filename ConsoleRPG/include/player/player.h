// Copyright 2026/07/30 JinHo


#pragma once

#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <string>


template<typename Entity>
class Effect;


enum class Pstat {
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

class Essence;

class Player {
 public:

    // operator

    int& operator[](const Pstat target);
    const int& operator[](const Pstat target) const;

    int& operator[](const std::string& target);
    const int& operator[](const std::string& target) const;

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

    int GetBuffPower() const;
    int GetBuffDefence() const;

    std::string GetName() const;
    std::string GetEssence() const;

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

    void SetBuffPower(int buffPower);
    void SetBuffDefence(int buffDefence);

    void SetName(std::string name);
    void SetEssence(std::string essence);

    void SetSkill(std::string skill);

    // Universal interface

    std::string getName() const;

    int gethp() const;
    int getmp() const;
    int getatk() const;
    int getdef() const;


    void sethp(int value);
    void setmp(int value);
    void setatk(int value);
    void setdef(int value);

    // Function
    void SyncToBase(Pstat target);

    void SyncToMax(Pstat target);

    void ApplyEffect(Pstat target, int power);

    bool SetEssence(const Essence& essence);

    void ViewStatus();

    // singleton
    static Player& GetInstance() {
        static Player instance = []() {
            std::string name;

            std::cout << "=====================================================\n";
            std::cout << "닉네임을 입력해 주세요.\n";
            std::cout << "닉네임: ";
            std::cin >> name;
            std::cout << "=====================================================\n";

            return Player(name);
            }();

        return instance;
    }

    static const Player& GetReadInstance() {
        return GetInstance();
    }

 protected:

    // Constructor

    explicit Player(std::string name,
                    int level = 1,
                    int baseMaxHp = 200,
                    int baseMaxMp = 100,
                    int basePower = 30,
                    int baseDefence = 5,
                    std::string skill = "몸통 박치기!");

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

    int attack = 0;
    int guard = 0;

    std::string name;
    std::string essence;

    std::string skill;
};
