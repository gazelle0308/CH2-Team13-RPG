// Copyright 2026/08/01 JinHo


#include "Essence/Essence.h"

#include <string>
#include <iostream>
#include <algorithm>

#include "Player/Player.h"
#include "Monster/monster.h"
#include "Effect/Effect.h"


// Constructor

Essence::Essence(std::string name,
                 int hp,
                 int mp,
                 int power,
                 int defence):
                 name(name),
                 hp(hp),
                 mp(mp),
                 power(power),
                 defence(defence) {}



// Function

void Essence::Skill(Monster& monster) {
    if (this->name == "슬라임") {
    } else if (this->name == "좀비") {
    } else if (this->name == "고블린") {
    } else if (this->name == "야생 늑대") {
    } else if (this->name == "키메라") {
    } else if (this->name == "고스트") {
    } else if (this->name == "서큐버스") {
    } else if (this->name == "인큐버스") {
    } else if (this->name == "구울") {
    } else if (this->name == "웨어울프") {
    } else if (this->name == "가고일") {
    } else if (this->name == "마고일") {
    } else if (this->name == "미라") {
    } else if (this->name == "데몬") {
    } else if (this->name == "골렘") {
    } else if (this->name == "그리폰") {
    } else if (this->name == "뱀파이어") {
    } else if (this->name == "세이렌") {
    } else if (this->name == "미노타우르스") {
    } else if (this->name == "얼음 정령") {
    } else if (this->name == "상급 데몬") {
    } else if (this->name == "상급 미노타우르스") {
    } else if (this->name == "상급 뱀파이어") {
    } else if (this->name == "상급 키메라") {
    } else if (this->name == "피닉스") {
    } else {
        throw std::out_of_range("Unknown Essence");
    }
}


void Essence::OpenEssence() {
    this->lock = false;
}

void Essence::LockEssence() {
    this->lock = true;
}


void Essence::EnableEssence() {
    if (lock) {
        std::cout << "아직 얻지 못한 정수입니다.\n";
    } else {
        this->enable = true;
    }
}

void Essence::DisableEssence() {
    if(lock) {
        std::cout << "아직 얻지 못한 정수입니다.\n";
    } else {
        this->enable = false;
    }
}

// Setter

void Essence::SetLock(bool lock) { this->lock = lock; }
void Essence::SetEnable(bool enable) { this->enable = enable; }

void Essence::SetHp(int hp) { this->hp = hp; }
void Essence::SetMp(int mp) { this->mp = mp; }
void Essence::SetPower(int power) { this->power = power; }
void Essence::SetDefence(int defence) { this->defence = defence; }

void Essence::SetName(std::string name) { this->name = name; }

// Getter

bool Essence::GetLock() const { return this->lock; }
bool Essence::GetEnable() const { return this->enable; }

int Essence::GetHp() const { return this->hp; }
int Essence::GetMp() const { return this->mp; }
int Essence::GetPower() const { return this->power; }
int Essence::GetDefence() const { return this->defence; }

std::string Essence::GetName() const { return this->name; }
