// Copyright 2026/08/01 JinHo


#include "Essence/Essence.h"

#include <string>
#include <iostream>
#include <algorithm>

#include "Player/Player.h"


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
void Essence::Skill(Player& player) {
    if (this->name == "Slime") {
    } else if (this->name == "Zombie") {
    } else if (this->name == "Goblin") {
    } else if (this->name == "Wild Wolf") {
    } else if (this->name == "Chimera") {
    } else if (this->name == "Ghost") {
    } else if (this->name == "Succubus") {
    } else if (this->name == "Incubus") {
    } else if (this->name == "Ghoul") {
    } else if (this->name == "Werewolf") {
    } else if (this->name == "Gargoyle") {
    } else if (this->name == "Margoyle") {
    } else if (this->name == "Mummy") {
    } else if (this->name == "Demon") {
    } else if (this->name == "Golem") {
    } else if (this->name == "Griffon") {
    } else if (this->name == "Vampire") {
    } else if (this->name == "Siren") {
    } else if (this->name == "Minotaur") {
    } else if (this->name == "Ice Elemental") {
    } else if (this->name == "High Demon") {
    } else if (this->name == "High Minotaur") {
    } else if (this->name == "High Vampire") {
    } else if (this->name == "Guardian Chimera") {
    } else if (this->name == "Phoenix") {
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
        std::cout << "Now " << this->name << " Essence is Locked \n";
    } else {
        this->enable = true;
    }
}

void Essence::DisableEssence() {
    if(lock) {
        std::cout << "Now " << this->name << " Essence is Locked \n";
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
