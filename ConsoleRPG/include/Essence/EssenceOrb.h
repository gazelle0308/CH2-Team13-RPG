// Copyright 2026/08/01 JinHo


#pragma once

#include <string>

#include "Essence.h"

class EssenceOrb {
 public:
    // Constructor

    EssenceOrb();

    // Destructor

    ~EssenceOrb() = default;

    // operator

    Essence& operator[](int index);

    // Function

    Essence& UseEssence(int index);

    std::string GetOrbInfo();

    int NameToIndex(std::string name);

    void AcquireEssence(std::string name);

 private:

    Essence orb[26];
};

