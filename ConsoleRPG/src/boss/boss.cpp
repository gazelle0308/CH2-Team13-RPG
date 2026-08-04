// Copyright 2026/08/04 JinHo

#include "Boss/Boss.h"

#include <random>
#include <iostream>
#include <algorithm>

#include "Effect/Effect.h"
#include "Player/Player.h"


// Constructor
Alatreon::Alatreon() {
    this->hp = 1000;
    this->mp = 700;
    this->power = 90;
    this->defence = 22;

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
    std::cout << "=====================================================\n";
    std::cout << "<" << this->name << ">\n";
    std::cout << "HP: " << this->hp
              << " MP: " << this->mp << "\n";
    std::cout << "공격력: " << this->power
              << " 방어력: " << this->defence << "\n";
    this->FormPrint();
    this->BeforeFormPrint();
    std::cout << "=====================================================\n";
    std::cout << "현재 까지의 속성 억제 누적 수치: " << this->elementalSuppression << "! \n";
    std::cout << "=====================================================\n";
    this->IsHornBreak();
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

    this->statBuf[static_cast<int>(Stat::HP)] = this->hp;
    this->statBuf[static_cast<int>(Stat::MP)] = this->mp;
    this->statBuf[static_cast<int>(Stat::POWER)] = this->power;
    this->statBuf[static_cast<int>(Stat::DEFENCE)] = this->defence;
}


void Alatreon::AfterEffect() {
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

    if (countEschaton != 2) {
        return;
    }

    countEschaton = 0;
    std::cout << "=====================================================\n";
    std::cout << "알바트리온의 에스카톤 저지먼트! \n";
    std::cout << "=====================================================\n";

    if (this->elementalSuppression < 300) {
        std::cout << "속성 억제에 실패했습니다! \n";
        std::cout << "즉사기! \n";
        std::cout << "=====================================================\n";
        player[Pstat::Hp] = 0;
    } else if (this->elementalSuppression < 400) {
        std::cout << "속성 억제에 부분 성공 했습니다! \n";
        std::cout << "체력의 절반 만큼 데미지 받습니다! \n";
        std::cout << "=====================================================\n";
        player[Pstat::Hp] /= 2;
    } else {
        std::cout << "속성 억제에 완전 성공 했습니다! \n";
        std::cout << "100 데미지 받습니다! \n";
        std::cout << "=====================================================\n";
        player[Pstat::Hp] -= 100;
    }

    this->elementalSuppression = 0;
}


void Alatreon::ElementFormChange() {
    this->turnAfterChange += 1;

    if (this->turnAfterChange % 5 != 0) {
        return;
    }

    std::cout << "=====================================================\n";
    std::cout << "황흑룡의 모습이 변화했습니다! \n";
    std::cout << "=====================================================\n";
    countEschaton += 1;

    if (this->elementForm != ElementForm::Dragon) {
        std::cout << "지금은 용속성 모습입니다! \n";
        std::cout << "기존 속성 변화를 막으려면 데미지를 누적해야 합니다! \n";
        std::cout << "=====================================================\n";
        this->elementForm = ElementForm::Dragon;
    } else if (this->hornBreak) {
        std::cout << "데미지를 누적 하는데 성공 했습니다! \n";
        std::cout << "기존 속성 변화를 막았습니다! \n";
        this->BeforeFormPrint();
        std::cout << "=====================================================\n";
        this->elementForm = this->beforeForm;
        this->hornBreak = false;
        this->hornDamage = 0;
        this->mp = 700;
    } else {
        std::cout << "데미지를 누적 하는데 실패 했습니다! \n";
        std::cout << "기존 속성이 변화합니다! \n";
        std::cout << "원래 ";
        this->BeforeFormPrint();
        this->elementForm = this->anotherForm;
        this->anotherForm = this->beforeForm;
        this->beforeForm = this->elementForm;
        this->hornDamage = 0;
        this->mp = 700;
        std::cout << "신규 ";
        this->BeforeFormPrint();
        std::cout << "=====================================================\n";
    }

    this->FormStatSetup();
}

int Alatreon::IsWin() {
    Player& player = Player::GetInstance();

    if (player[Pstat::Hp] <= 0) {
        return 0;
    } else if (player[Pstat::Hp] > 0 && this->hp <= 0) {
        return 1;
    } else {
        return 2;
    }
}

void Alatreon::FormPrint() {
    if (this->elementForm == ElementForm::Fire) {
        std::cout << "속성 형태: 불(공격 특화)\n";
    } else if (this->elementForm == ElementForm::Ice) {
        std::cout << "속성 형태: 얼음(MP 특화)\n";
    } else if (this->elementForm == ElementForm::Dragon) {
        std::cout << "속성 형태: 용(방어 특화) \n";
    }
}

void Alatreon::BeforeFormPrint() {
    if (this->beforeForm == ElementForm::Fire) {
        std::cout << "기존 속성 형태: 불(공격 특화)\n";
    } else if (this->beforeForm == ElementForm::Ice) {
        std::cout << "기존 속성 형태: 얼음(MP 특화)\n";
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

    std::cout << "=====================================================\n";
    if ((this->elementForm == ElementForm::Dragon && result < 50) ||
        (this->elementForm == ElementForm::Fire &&
         result >= 50 && result < 85) ||
        (this->elementForm == ElementForm::Ice &&
         result >= 50 && result < 85)) {
        std::cout << "[" << this->name << "] 스킬 사용!\n";
        std::cout << "용속성 방출(대상:player):\n";
        std::cout << "5 Turn/10 PowerDown\n";
        std::cout << "5 Turn/7 ManaBurn\n";

        playerEffect.ReceiveEffect(EffectType::PowerDown, 10, 5);
        playerEffect.ReceiveEffect(EffectType::ManaBurn, 7, 5);

        this->mp = std::max(this->mp - 70, 0);
        this->statBuf[static_cast<int>(Stat::MP)] -= 70;
        std::cout << "=====================================================\n";
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
        std::cout << "5 Turn/5 DefenceDown\n";
        std::cout << "2 Attack/" << damage << " Damage\n";

        playerEffect.ReceiveEffect(
            EffectType::DefenceDown, 5, 5);

        player[Pstat::Hp] -= damage;
        player[Pstat::Hp] -= damage;

        this->mp = std::max(this->mp - 50, 0);
        this->statBuf[static_cast<int>(Stat::MP)] -= 50;
        std::cout << "=====================================================\n";
        return;
    }

    int damage =
        std::max((this->power / 3) - player[Pstat::Defence], 1);

    std::cout << "[" << this->name << "] 스킬 사용!\n";
    std::cout << "고드름 낙하(대상:player):\n";
    std::cout << "5 Turn/30 Bleed Damage\n";
    std::cout << "3 Attack/" << damage << " Damage\n";

    playerEffect.ReceiveEffect(
        EffectType::Bleeding, 6, 5);

    player[Pstat::Hp] -= damage;
    player[Pstat::Hp] -= damage;
    player[Pstat::Hp] -= damage;

    this->mp = std::max(this->mp - 30, 0);
    this->statBuf[static_cast<int>(Stat::MP)] -= 30;
    std::cout << "=====================================================\n";
}


void Alatreon::AlatreonAttack() {
    Player& player = Player::GetInstance();

    int damage =
        std::max(this->power - player[Pstat::Defence], 1);

    std::cout << "=====================================================\n";
    std::cout << "[" << this->name << "]의 돌진!\n";
    std::cout << "1 Attack/" << damage << " Damage\n";
    std::cout << "=====================================================\n";

    player[Pstat::Hp] -= damage;
}
