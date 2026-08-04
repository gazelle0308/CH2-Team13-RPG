// Copyright 2026/08/01 JinHo


#pragma once

#include <string>

#include "Effect/Effect.h"
#include "Boss/Boss.h"

class Monster;

class Essence {
 public:
    // Constructor

    explicit Essence() = default;
    explicit Essence(std::string name,
                      int hp,
                      int mp,
                      int power,
                      int defence);

    // Destructor

    ~Essence() = default;

    // Function

    void Skill(Monster& monster, Effect<Monster>& effect);
    void Skill(Alatreon& monster, Effect<Alatreon>& effect);

    void OpenEssence();
    void LockEssence();

    void EnableEssence();
    void DisableEssence();

    // Setter

    void SetLock(bool lock);
    void SetEnable(bool enable);

    void SetHp(int hp);
    void SetMp(int mp);
    void SetPower(int power);
    void SetDefence(int defence);

    void SetName(std::string name);

    void SetupSkill();

    // Getter

    bool GetLock() const;
    bool GetEnable() const;

    int GetHp() const;
    int GetMp() const;
    int GetPower() const;
    int GetDefence() const;

    std::string GetName() const;

    std::string GetSkill() const;

 private:
    bool lock = true;
    bool enable = false;

    int hp = 0;
    int mp = 0;
    int power = 0;
    int defence = 0;

    std::string name = "Empty";
    std::string skill = "Empty";
};
