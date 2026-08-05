// Copyright 2026/08/01 JinHo


#pragma once

#include <string>

#include "Essence.h"
#include "Boss/Boss.h"

class EssenceOrb {
 public:
    // Destructor

    ~EssenceOrb() = default;

    // operator

    Essence& operator[](int index);

    // Function

    Essence& UseEssence(int index);

    std::string GetOrbInfo();

    int NameToIndex(std::string name);

    void AcquireEssence(std::string name);

    void UseSkill(Monster& monster, Effect<Monster>& effect);

    void UseSkill(Alatreon& boss, Effect<Alatreon>& effect);

    bool AllCollection();

    // singleton

    static EssenceOrb& GetInstance() {
        static EssenceOrb instance;
        return instance;
    }

 private:
    // Constructor

    EssenceOrb();

    Essence orb[26];
};

