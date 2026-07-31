// Copyright 2026/07/30 JinHo

#include "player/player.h"

#include <string>
#include <algorithm>

#include "Utility/Utility.h"


// operator
int& Player::operator[](const Pstat target) {
    if (target == Pstat::Hp) {
        return this->currentHp;
    } else if (target == Pstat::Mp) {
        return this->currentMp;
    } else if (target == Pstat::MaxHp) {
        return this->currentMaxHp;
    } else if (target == Pstat::MaxMp) {
        return this->currentMaxMp;
    } else if (target == Pstat::Power) {
        return this->currentPower;
    } else if (target == Pstat::Defence) {
        return this->currentDefence;
    } else if (target == Pstat::BuffPower) {
        return this->buffPower;
    } else if (target == Pstat::BuffDefence) {
        return this->buffDefence;
    } else if (target == Pstat::Gold) {
        return this->gold;
    } else if (target == Pstat::Exp) {
        return this->exp;
    } else {
        throw std::logic_error("that taget is read-only.");
    }
}

const int& Player::operator[](const Pstat target) const {
    if (target == Pstat::Hp) {
        return this->currentHp;
    } else if (target == Pstat::Mp) {
        return this->currentMp;
    } else if (target == Pstat::MaxHp) {
        return this->currentMaxHp;
    } else if (target == Pstat::MaxMp) {
        return this->currentMaxMp;
    } else if (target == Pstat::Power) {
        return this->currentPower;
    } else if (target == Pstat::Defence) {
        return this->currentDefence;
    } else if (target == Pstat::BuffPower) {
        return this->buffPower;
    } else if (target == Pstat::BuffDefence) {
        return this->buffDefence;
    } else if (target == Pstat::Gold) {
        return this->gold;
    } else if (target == Pstat::Exp) {
        return this->exp;
    } else if (target == Pstat::Level) {
        return this->level;
    } else if (target == Pstat::MaxExp) {
        return this->maxExp;
    } else if (target == Pstat::Attack) {
        return this->currentPower + this->buffPower;
    } else if (target == Pstat::Guard) {
        return this->currentDefence + this->buffDefence;
    }
}

// Getter
int Player::GetGold() const { return this->gold; }

int Player::GetLevel() const { return this->level; }
int Player::GetExp() const { return this->exp; }
int Player::GetMaxExp() const { return this->maxExp; }


int Player::GetCurrentHp() const { return this->currentHp; }
int Player::GetCurrentMp() const { return this->currentMp; }


int Player::GetBaseMaxHp() const { return this->baseMaxHp; }
int Player::GetBaseMaxMp() const { return this->baseMaxMp; }
int Player::GetBasePower() const { return this->basePower; }
int Player::GetBaseDefence() const { return this->baseDefence; }

int Player::GetCurrentMaxHp() const { return this->currentMaxHp; }
int Player::GetCurrentMaxMp() const { return this->currentMaxMp; }
int Player::GetCurrentPower() const { return this->currentPower; }
int Player::GetCurrentDefence() const { return this->currentDefence; }

std::string Player::GetName() const { return this->name; }
std::string Player::GetJob() const { return this->job; }

std::string Player::GetSkill() const { return this->skill; }


// Setter
void Player::SetGold(int gold) { this->gold = gold; }

void Player::SetLevel(int level) { this->level = level; }
void Player::SetExp(int exp) { this->exp = exp; }
void Player::SetMaxExp(int maxExp) { this->maxExp = maxExp; }


void Player::SetCurrentHp(int currentHp) { this->currentHp = currentHp; }
void Player::SetCurrentMp(int currentMp) { this->currentMp = currentMp; }


void Player::SetBaseMaxHp(int baseMaxHp) {
    this->baseMaxHp = baseMaxHp;
}

void Player::SetBaseMaxMp(int baseMaxMp) {
    this->baseMaxMp = baseMaxMp;
}

void Player::SetBasePower(int basePower) {
    this->basePower = basePower;
}

void Player::SetBaseDefence(int baseDefence) {
    this->baseDefence = baseDefence;
}



void Player::SetCurrentMaxHp(int currentMaxHp) {
    this->currentMaxHp = currentMaxHp;
}

void Player::SetCurrentMaxMp(int currentMaxMp) {
    this->currentMaxMp = currentMaxMp;
}

void Player::SetCurrentPower(int currentPower) {
    this->currentPower = currentPower;
}

void Player::SetCurrentDefence(int currentDefence) {
    this->currentDefence = currentDefence;
}



void Player::SetName(std::string name) { this->name = name; }
void Player::SetJob(std::string job) { this->job = job; }

void Player::SetSkill(std::string skill) { this->skill = skill; }



// Function

void Player::SyncToBase(Pstat target) {
    if (target == Pstat::Hp) {
        this->currentHp = this->baseMaxHp;
    } else if (target == Pstat::Mp) {
        this->currentMp = this->baseMaxMp;
    } else if (target == Pstat::MaxHp) {
        this->currentMaxHp = this->baseMaxHp;
    } else if (target == Pstat::MaxMp) {
        this->currentMaxMp = this->baseMaxMp;
    } else if (target == Pstat::Power) {
        this->currentPower = this->basePower;
    } else if (target == Pstat::Defence) {
        this->currentDefence = this->baseDefence;
    } else {
        throw std::out_of_range("Can't another target");
    }
}

void Player::SyncToMax(Pstat target) {
    if (target == Pstat::Hp) {
        this->currentHp = this->currentMaxHp;
    } else if (target == Pstat::Mp) {
        this->currentMp = this->currentMaxMp;
    } else {
        throw std::out_of_range("Can't another target");
    }
}

void Player::GetEffect(Pstat target, int num) {
    if (target == Pstat::Hp) {
        this->currentHp = std::min(this->currentHp + num, this->currentMaxHp);
    } else if (target == Pstat::Mp) {
        this->currentMp = std::min(this->currentMp + num, this->currentMaxMp);
    } 
}

// Constructor
Player::Player(std::string name,
               int baseMaxHp,
               int baseMaxMp,
               int power,
               int defence,
               int level,
               std::string skill)
               :name(name),
                baseMaxHp(baseMaxHp),
                baseMaxMp(baseMaxMp),
                basePower(basePower),
                baseDefence(baseDefence),
                level(level),
                skill(skill) {
    if (this->job.empty()) {
        this->job = "Adventure";
    }

    this->maxExp = 100;
    this->exp = 0;
    this->gold = 0;

    SyncToBase(Pstat::Hp);
    SyncToBase(Pstat::Mp);
    SyncToBase(Pstat::MaxHp);
    SyncToBase(Pstat::MaxMp);
}
