// Copyright 2026/08/04 JinHo
#pragma once

#include <string>


enum class ElementForm {
    Fire,
    Dragon,
    Ice
};

enum class Stat {
    HP,
    MP,
    POWER,
    DEFENCE
};

class Alatreon {
 public:
    Alatreon();

    // Universal Interface
    std::string getName() const;

    int gethp() const;
    int getmp() const;
    int getatk() const;
    int getdef() const;

    void sethp(int value);
    void setmp(int value);
    void setatk(int value);
    void setdef(int value);

    // Tick
    void StartTurn();
    void BeforeEffect();
    void EndTurn();

    // Action
    void AlatreonSkill();
    void AlatreonAttack();

    // Logic
    int IsWin();

 private:
    // Logic
    void IsHornBreak();
    void EschatonJudgment();
    void ElementFormChange();
    void FormStatSetup();

    // Base Stat
    int hp = 0;
    int mp = 0;
    int power = 0;
    int defence = 0;

    std::string name;

    // Current Form
    ElementForm elementForm;
    ElementForm beforeForm;
    ElementForm anotherForm;

    // System
    int statBuf[4] = {};
    int formStatBuf[4] = { 0, 0, 0, 0};

    int elementalSuppression = 0;

    int hornDamage = 0;
    bool hornBreak = false;

    int turnAfterChange = 0;
    int countEschaton = 0;
};
