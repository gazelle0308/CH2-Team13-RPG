// Copyright 2026/07/30 JinHo


#include "Player/Player.h"

#include <string>
#include <iostream>
#include <algorithm>

#include "Effect/Effect.h"
#include "Utility/Utility.h"
#include "Essence/EssenceOrb.h"


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
    } else if (target == Pstat::BaseHp) {
        return this->baseMaxHp;
    } else if (target == Pstat::BaseMp) {
        return this->baseMaxMp;
    } else if (target == Pstat::Power) {
        return this->currentPower;
    } else if (target == Pstat::Defence) {
        return this->currentDefence;
    } else if (target == Pstat::BasePower) {
        return this->basePower;
    } else if (target == Pstat::BaseDefence) {
        return this->baseDefence;
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
        return this->attack;
    } else if (target == Pstat::Guard) {
        return this->guard;
    } else {
        throw std::out_of_range("Unknown Pstat");
    }
}

int& Player::operator[](const std::string& target) {
    if (ignoreCaseCompare(target, "hp")) {
        return this->currentHp;
    } else if (ignoreCaseCompare(target, "mp")) {
        return this->currentMp;
    } else if (ignoreCaseCompare(target, "maxHp")) {
        return this->currentMaxHp;
    } else if (ignoreCaseCompare(target, "maxMp")) {
        return this->currentMaxMp;
    } else if (ignoreCaseCompare(target, "power")) {
        return this->currentPower;
    } else if (ignoreCaseCompare(target, "attack")) {
        return this->currentPower;
    } else if (ignoreCaseCompare(target, "defence")) {
        return this->currentDefence;
    } else if (ignoreCaseCompare(target, "buffpower")) {
        return this->buffPower;
    } else if (ignoreCaseCompare(target, "buffdefence")) {
        return this->buffDefence;
    } else if (ignoreCaseCompare(target, "gold")) {
        return this->gold;
    } else if (ignoreCaseCompare(target, "exp")) {
        return this->exp;
    } else if (ignoreCaseCompare(target, "baseHp") ||
        ignoreCaseCompare(target, "baseMp") ||
        ignoreCaseCompare(target, "basePower") ||
        ignoreCaseCompare(target, "baseDefence") ||
        ignoreCaseCompare(target, "level") ||
        ignoreCaseCompare(target, "maxExp") ||
        ignoreCaseCompare(target, "attack") ||
        ignoreCaseCompare(target, "guard")) {
        throw std::logic_error(target + " is read-only.");
    } else {
        throw std::out_of_range("Unknown status key : " + target);
    }
}

const int& Player::operator[](const std::string& target) const {
    if (ignoreCaseCompare(target, "hp")) {
        return this->currentHp;
    } else if (ignoreCaseCompare(target, "mp")) {
        return this->currentMp;
    } else if (ignoreCaseCompare(target, "maxHp")) {
        return this->currentMaxHp;
    } else if (ignoreCaseCompare(target, "maxMp")) {
        return this->currentMaxMp;
    } else if (ignoreCaseCompare(target, "baseHp")) {
        return this->baseMaxHp;
    } else if (ignoreCaseCompare(target, "baseMp")) {
        return this->baseMaxMp;
    } else if (ignoreCaseCompare(target, "power")) {
        return this->currentPower;
    } else if (ignoreCaseCompare(target, "defence")) {
        return this->currentDefence;
    } else if (ignoreCaseCompare(target, "basePower")) {
        return this->basePower;
    } else if (ignoreCaseCompare(target, "baseDefence")) {
        return this->baseDefence;
    } else if (ignoreCaseCompare(target, "gold")) {
        return this->gold;
    } else if (ignoreCaseCompare(target, "exp")) {
        return this->exp;
    } else if (ignoreCaseCompare(target, "level")) {
        return this->level;
    } else if (ignoreCaseCompare(target, "maxExp")) {
        return this->maxExp;
    } else if (ignoreCaseCompare(target, "attack")) {
        return this->attack;
    } else if (ignoreCaseCompare(target, "guard")) {
        return this->guard;
    } else if (ignoreCaseCompare(target, "buffpower")) {
        return this->buffPower;
    } else if (ignoreCaseCompare(target, "buffdefence")) {
        return this->buffDefence;
    } else {
        throw std::out_of_range("Unknown status key : " + target);
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

int Player::GetBuffPower() const { return this->buffPower; }
int Player::GetBuffDefence() const { return this->buffDefence; }

std::string Player::GetName() const { return this->name; }
std::string Player::GetEssence() const { return this->essence; }

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


void Player::SetBuffPower(int buffPower) {
    this->buffPower = buffPower;
}

void Player::SetBuffDefence(int buffDefence) {
    this->buffDefence = buffDefence;
}


void Player::SetName(std::string name) { this->name = name; }
void Player::SetEssence(std::string essence) { this->essence = essence; }

void Player::SetSkill(std::string skill) { this->skill = skill; }


// Universal interface

std::string Player::getName() const { return this->name; }

int Player::gethp() const { return this->currentHp; }
int Player::getmp() const { return this->currentMp; }
int Player::getatk() const { return this->currentPower; }
int Player::getdef() const { return this->currentDefence; }


void Player::sethp(int value) { this->currentHp = value; }
void Player::setmp(int value) { this->currentMp = value; }
void Player::setatk(int value) { this->currentPower = value; }
void Player::setdef(int value) { this->currentDefence = value; }


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

void Player::ApplyEffect(Pstat target, int power) {
    if (target == Pstat::Hp) {
        this->currentHp = std::min(this->currentHp + power, this->currentMaxHp);
    } else if (target == Pstat::Mp) {
        this->currentMp = std::min(this->currentMp + power, this->currentMaxMp);
    } else if (target == Pstat::BuffPower) {
        this->buffPower = power;
        this->attack = this->currentPower + this->buffPower;
    } else if (target == Pstat::BuffDefence) {
        this->buffDefence = power;
        this->guard = this->currentDefence + this->buffDefence;
    } else {
        throw std::out_of_range("Can't another target");
    }
}

void Player::SetEssence(const Essence& essence) {
    if (essence.GetName() == "잘못된 정보") {
        std::cout << "=====================================================\n";
        std::cout << "정수 사용에 실패 했습니다! \n";
        std::cout << "=====================================================\n";
        return;
    }
    if (essence.GetEnable()) {
        this->currentMaxHp = this->baseMaxHp + essence.GetHp();
        this->currentMaxMp = this->baseMaxMp + essence.GetMp();
        this->currentPower = this->basePower + essence.GetPower();
        this->currentDefence = this->baseDefence + essence.GetDefence();
        this->essence = essence.GetName();
    } else {
        this->SyncToBase(Pstat::MaxHp);
        this->SyncToBase(Pstat::MaxMp);
        this->SyncToBase(Pstat::Power);
        this->SyncToBase(Pstat::Defence);
        this->essence = "미장착";
    }
}

void Player::ViewStatus() {
    std::cout << "=====================================================\n";
    std::cout << "<플레이어>\n";
    std::cout << "이름: "  << this->name
              << " 정수: " << this->essence << "\n";
    std::cout << "레벨: "    << this->level
              << " 경험치: " << this->exp
              << "/" << this->maxExp
              <<" 골드: "    << this->gold << "\n";
    std::cout << "HP: "  << this->currentHp
              << "/" << this->currentMaxHp
              << " MP: " << this->currentMp
              << "/" << this->currentMaxMp << "\n";
    std::cout << "공격력: "  << this->attack
              << " 방어력: " << this->guard
              << " 스킬: "   << this->skill << "\n";
    std::cout << "=====================================================\n";
}

// Constructor

Player::Player(std::string name,
               int level,
               int baseMaxHp,
               int baseMaxMp,
               int basePower,
               int baseDefence,
               std::string skill)
               :name(name),
               level(level),
               baseMaxHp(baseMaxHp),
               baseMaxMp(baseMaxMp),
               basePower(basePower),
               baseDefence(baseDefence),
               skill(skill) {
               if (this->essence.empty()) {
                   this->essence = "미장착";
               }

    this->maxExp = 100;
    this->exp = 0;
    this->gold = 0;

    SyncToBase(Pstat::Hp);
    SyncToBase(Pstat::Mp);
    SyncToBase(Pstat::MaxHp);
    SyncToBase(Pstat::MaxMp);
    SyncToBase(Pstat::Power);
    SyncToBase(Pstat::Defence);

    this->attack = currentPower;
    this->guard = currentDefence;
}
