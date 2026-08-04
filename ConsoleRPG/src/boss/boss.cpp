// Copyright 2026/08/04 JinHo

#include "Boss/Boss.h"

#include <random>
#include <iostream>
#include <algorithm>

#include "Effect/Effect.h"
#include "Player/Player.h"


// Constructor
Alatreon::Alatreon() {
    this->hp = 900;
    this->mp = 700;
    this->power = 100;
    this->defence = 20;

    this->name = "황흑룡 알바트리온";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    int result = dist(gen);

    if (result == 0) {
        this->elementForm = ElementForm::Fire;
        this->beforeForm = ElementForm::Fire;
        this->anotherForm = ElementForm::Ice;
    }
    else {
        this->elementForm = ElementForm::Ice;
        this->beforeForm = ElementForm::Ice;
        this->anotherForm = ElementForm::Fire;
    }

    this->FormStatSetup();
}


// Universal Interface
std::string Alatreon::getName() const {
    return this->name;
}

int Alatreon::gethp() const {
    return this->hp;
}

int Alatreon::getmp() const {
    return this->mp;
}

int Alatreon::getatk() const {
    return this->power;
}

int Alatreon::getdef() const {
    return this->defence;
}

void Alatreon::sethp(int value) {
    this->hp = value;
}

void Alatreon::setmp(int value) {
    this->mp = value;
}

void Alatreon::setatk(int value) {
    this->power = value;
}

void Alatreon::setdef(int value) {
    this->defence = value;
}


// Tick Function
void Alatreon::EndTurn() {
    if (this->statBuf[static_cast<int>(Stat::HP)] > this->hp) {
        this->elementalSuppression +=
            this->statBuf[static_cast<int>(Stat::HP)] - this->hp;
    }

    if (this->statBuf[static_cast<int>(Stat::MP)] > this->mp) {
        this->elementalSuppression +=
            this->statBuf[static_cast<int>(Stat::MP)] - this->mp;
    }

    if (this->statBuf[static_cast<int>(Stat::POWER)] > this->power) {
        this->elementalSuppression +=
            this->statBuf[static_cast<int>(Stat::POWER)] - this->power;
    }

    if (this->statBuf[static_cast<int>(Stat::DEFENCE)] > this->defence) {
        this->elementalSuppression +=
            this->statBuf[static_cast<int>(Stat::DEFENCE)] - this->defence;
    }

    this->ElementFormChange();
    this->EschatonJudgment();
}


void Alatreon::StartTurn() {
    this->statBuf[static_cast<int>(Stat::HP)] = this->hp;
    this->statBuf[static_cast<int>(Stat::MP)] = this->mp;
    this->statBuf[static_cast<int>(Stat::POWER)] = this->power;
    this->statBuf[static_cast<int>(Stat::DEFENCE)] = this->defence;
}


void Alatreon::BeforeEffect() {
    if (this->statBuf[static_cast<int>(Stat::HP)] > this->hp) {
        this->elementalSuppression +=
            (this->statBuf[static_cast<int>(Stat::HP)] - this->hp) / 4;

        this->hornDamage +=
            (this->statBuf[static_cast<int>(Stat::HP)] - this->hp) / 4;
    }

    if (this->statBuf[static_cast<int>(Stat::MP)] > this->mp) {
        this->elementalSuppression +=
            (this->statBuf[static_cast<int>(Stat::MP)] - this->mp) / 4;
    }

    if (this->statBuf[static_cast<int>(Stat::POWER)] > this->power) {
        this->elementalSuppression +=
            (this->statBuf[static_cast<int>(Stat::POWER)] - this->power) / 2;
    }

    if (this->statBuf[static_cast<int>(Stat::DEFENCE)] > this->defence) {
        this->elementalSuppression +=
            (this->statBuf[static_cast<int>(Stat::DEFENCE)] -
                this->defence) / 2;
    }

    this->IsHornBreak();

    this->statBuf[static_cast<int>(Stat::HP)] = this->hp;
    this->statBuf[static_cast<int>(Stat::MP)] = this->mp;
    this->statBuf[static_cast<int>(Stat::POWER)] = this->power;
    this->statBuf[static_cast<int>(Stat::DEFENCE)] = this->defence;
}


// Logic Function
void Alatreon::IsHornBreak() {
    if (this->elementForm == ElementForm::Dragon &&
        this->hornDamage > 100) {
        this->hornBreak = true;
    }
}


void Alatreon::EschatonJudgment() {
    Player& player = Player::GetInstance();

    if (countEschaton != 3) {
        return;
    }

    countEschaton = 0;

    if (this->elementalSuppression < 300) {
        player[Pstat::Hp] = 0;
    } else if (this->elementalSuppression < 400) {
        player[Pstat::Hp] /= 2;
    } else {
        player[Pstat::Hp] -= 100;
    }

    this->elementalSuppression = 0;
}


void Alatreon::ElementFormChange() {
    this->turnAfterChange += 1;

    if (this->turnAfterChange % 4 != 0) {
        return;
    }

    countEschaton += 1;

    if (this->elementForm != ElementForm::Dragon) {
        this->elementForm = ElementForm::Dragon;
    } else if (this->hornBreak) {
        this->elementForm = this->beforeForm;
        this->hornBreak = false;
        this->hornDamage = 0;
    } else {
        this->elementForm = this->anotherForm;
        this->anotherForm = this->beforeForm;
        this->beforeForm = this->elementForm;
        this->hornDamage = 0;
    }

    this->FormStatSetup();
}

int Alatreon::IsWin() {
    Player& player = Player::GetInstance();

    if(player[Pstat::Hp] > 0 && this->hp <= 0) {
        return 0;
    } else if (player[Pstat::Hp] <= 0 && this->hp > 0) {
        return 1;
    } else {
        return 2;
    }
}


void Alatreon::FormStatSetup() {
    this->mp -= this->formStatBuf[static_cast<int>(Stat::MP)];
    this->power -= this->formStatBuf[static_cast<int>(Stat::POWER)];
    this->defence -= this->formStatBuf[static_cast<int>(Stat::DEFENCE)];

    if (this->elementForm == ElementForm::Dragon) {
        this->formStatBuf[static_cast<int>(Stat::DEFENCE)] = 15;
        this->formStatBuf[static_cast<int>(Stat::MP)] = -30;
        this->formStatBuf[static_cast<int>(Stat::POWER)] = -20;
    } else if (this->elementForm == ElementForm::Fire) {
        this->formStatBuf[static_cast<int>(Stat::DEFENCE)] = -10;
        this->formStatBuf[static_cast<int>(Stat::MP)] = 50;
        this->formStatBuf[static_cast<int>(Stat::POWER)] = -20;
    } else {
        this->formStatBuf[static_cast<int>(Stat::DEFENCE)] = -10;
        this->formStatBuf[static_cast<int>(Stat::MP)] = -30;
        this->formStatBuf[static_cast<int>(Stat::POWER)] = 40;
    }

    this->mp += this->formStatBuf[static_cast<int>(Stat::MP)];
    this->power += this->formStatBuf[static_cast<int>(Stat::POWER)];
    this->defence += this->formStatBuf[static_cast<int>(Stat::DEFENCE)];
}


// Action Function
void Alatreon::AlatreonSkill() {
    Player& player = Player::GetInstance();
    Effect<Player>& playerEffect =
        Effect<Player>::GetPlayerInstance(player);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 99);

    int result = dist(gen);

    if ((this->elementForm == ElementForm::Dragon && result < 50) ||
        (this->elementForm == ElementForm::Fire &&
         result >= 50 && result < 85) ||
        (this->elementForm == ElementForm::Ice &&
         result >= 50 && result < 85)) {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "용속성 방출(대상:player):\n";
        std::cout << "5Turn/10 PowerDown\n";
        std::cout << "5Turn/7 ManaBurn\n";

        playerEffect.ReceiveEffect(EffectType::PowerDown, 10, 5);
        playerEffect.ReceiveEffect(EffectType::ManaBurn, 7, 5);

        this->mp = std::max(this->mp - 70, 0);
        return;
    }

    if ((this->elementForm == ElementForm::Dragon &&
         result >= 50 && result <= 75) ||
        (this->elementForm == ElementForm::Fire &&
         result < 50) ||
        (this->elementForm == ElementForm::Ice &&
         result >= 85)) {
        int damage =
            std::max((this->power / 2) - player[Pstat::Defence], 1);

        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "화염 브레스(대상:player):\n";
        std::cout << "5Turn/5 DefenceDown\n";
        std::cout << "2 Attack/" << damage << " Damage\n";

        playerEffect.ReceiveEffect(
            EffectType::DefenceDown, 5, 5);

        player[Pstat::Hp] -= damage;
        player[Pstat::Hp] -= damage;

        this->mp = std::max(this->mp - 50, 0);
        return;
    }

    int damage =
        std::max((this->power / 3) - player[Pstat::Defence], 1);

    std::cout << "[" << this->name << "] 스킬 사용!\n";
    std::cout << "고드름 낙하(대상:player):\n";
    std::cout << "5Turn/30 Damage\n";
    std::cout << "3 Attack/" << damage << " Damage\n";

    playerEffect.ReceiveEffect(
        EffectType::Bleeding, 6, 5);

    player[Pstat::Hp] -= damage;
    player[Pstat::Hp] -= damage;
    player[Pstat::Hp] -= damage;

    this->mp = std::max(this->mp - 30, 0);
}


void Alatreon::AlatreonAttack() {
    Player& player = Player::GetInstance();

    int damage =
        std::max(this->power - player[Pstat::Defence], 1);

    std::cout << "[" << this->name << "]의 돌진!\n";
    std::cout << "1 Attack/" << damage << " Damage\n";

    player[Pstat::Hp] -= damage;
}


void Alatreon::AlatreonAction() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    if (this->mp > 0) {
        if (dist(gen) == 0) {
            this->AlatreonAttack();
        } else {
            this->AlatreonSkill();
        }
        return;
    }
    this->AlatreonAttack();
}
