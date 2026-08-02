// Copyright 2026/08/01 JinHo


#pragma once

#include <string>

#include "Essence.h"

class EssenceOrb {
public:

    // Destructor

    ~EssenceOrb() = default;

    // operator

    Essence& operator[](int index);

    // Function

    Essence& UseEssence(std::string name);

    std::string GetOrbInfo();

    int NameToIndex(std::string name);

    void AcquireEssence(std::string name);

    bool AllCollection();

    // singleton

    static EssenceOrb& GetInstance() {
        static EssenceOrb instance;
        return instance;
    };

private:
    // Constructor

    EssenceOrb();

    Essence orb[26];
};

