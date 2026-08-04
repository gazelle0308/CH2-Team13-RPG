// Copyright 2026/08/01 JinHo


#include "Essence/Essence.h"

#include <string>
#include <iostream>
#include <algorithm>

#include "Player/Player.h"
#include "Monster/Monster.h"
#include "Effect/Effect.h"
#include "Boss/Boss.h"
#include "Utility/Utility.h"


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

void Essence::Skill(Monster& monster, Effect<Monster>& effect) {
    Player& player = Player::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);

    StartLine();

    if (this->name == "슬라임") {
        std::cout << "슬라임의 정수를 사용했습니다.\n";
        std::cout << "방어구 손상(대상:monster): \n";
        std::cout << "5 Turn/8 DefenceDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 8, 5);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "좀비") {
        std::cout << "좀비의 정수를 사용했습니다.\n";
        std::cout << "재생(대상:player): \n";
        std::cout << "5 Turn/20 Regen\n";
        playerEffect.ReceiveEffect(EffectType::Regen, 4, 5);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "고블린") {
        std::cout << "고블린의 정수를 사용했습니다.\n";
        std::cout << "방망이 타격(대상:monster): \n";
        std::cout << "4 Turn/16 Damage\n";
        effect.ReceiveEffect(EffectType::Bleeding, 4, 4);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "야생 늑대") {
        std::cout << "야생 늑대의 정수를 사용했습니다.\n";
        std::cout << "투기 강화(대상:player): \n";
        std::cout << "4 Turn/10 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 10, 4);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "키메라") {
        std::cout << "키메라의 정수를 사용했습니다.\n";
        std::cout << "독(대상:monster): \n";
        std::cout << "5 Turn/30 Damage\n";
        effect.ReceiveEffect(EffectType::Poison, 6, 5);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "고스트") {
        std::cout << "고스트의 정수를 사용했습니다.\n";
        std::cout << "정신 침식(대상:monster): \n";
        std::cout << "4 Turn/8 ManaBurn\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 8, 4);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "서큐버스") {
        std::cout << "서큐버스의 정수를 사용했습니다.\n";
        std::cout << "매혹(대상:monster): \n";
        std::cout << "4 Turn/15 PowerDown\n";
        effect.ReceiveEffect(EffectType::PowerDown, 15, 4);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "인큐버스") {
        std::cout << "인큐버스의 정수를 사용했습니다.\n";
        std::cout << "매혹(대상:monster): \n";
        std::cout << "5 Turn/15 DefenceDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 15, 5);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "구울") {
        std::cout << "구울의 정수를 사용했습니다.\n";
        std::cout << "마나 침식(대상:monster): \n";
        std::cout << "5 Turn/15 ManaBurn\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 15, 5);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "웨어울프") {
        std::cout << "웨어울프의 정수를 사용했습니다.\n";
        std::cout << "고급 투기 강화(대상:player): \n";
        std::cout << "4 Turn/15 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 15, 4);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "가고일") {
        std::cout << "가고일의 정수를 사용했습니다.\n";
        std::cout << "경화(대상:player): \n";
        std::cout << "4 Turn/18 DefenceUp\n";
        playerEffect.ReceiveEffect(EffectType::DefenceUp, 18, 4);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "마고일") {
        std::cout << "마고일의 정수를 사용했습니다.\n";
        std::cout << "칼날 경화(대상:player): \n";
        std::cout << "3 Turn/25 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 25, 3);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "미라") {
        std::cout << "미라의 정수를 사용했습니다.\n";
        std::cout << "방어구 부식(대상:monster): \n";
        std::cout << "5 Turn/20 DefenceDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 20, 5);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "데몬") {
        std::cout << "데몬의 정수를 사용했습니다.\n";
        std::cout << "저주(대상:monster): ";
        std::cout << "4 Turn/20 ManaBurn\n";
        std::cout << "4 Turn/25 PowerDown\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 20, 4);
        effect.ReceiveEffect(EffectType::PowerDown, 25, 4);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "골렘") {
        std::cout << "골렘의 정수를 사용했습니다.\n";
        std::cout << "고급 경화(대상:player): \n";
        std::cout << "4 Turn/25 DefenceUp\n";
        playerEffect.ReceiveEffect(EffectType::DefenceUp, 25, 4);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "그리폰") {
        std::cout << "그리폰의 정수를 사용했습니다.\n";
        std::cout << "순풍(대상:player): \n";
        std::cout << "4 Turn/40 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 40, 4);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "뱀파이어") {
        std::cout << "뱀파이어의 정수를 사용했습니다.\n";
        std::cout << "출혈(대상:monster): \n";
        std::cout << "4 Turn/120 Bleed Damage\n";
        effect.ReceiveEffect(EffectType::Bleeding, 30, 4);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "세이렌") {
        std::cout << "세이렌의 정수를 사용했습니다.\n";
        std::cout << "고급 매혹(대상:monster): \n";
        std::cout << "5 Turn/30 PowerDown\n";
        effect.ReceiveEffect(EffectType::PowerDown, 30, 5);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "미노타우르스") {
        std::cout << "미노타우르스의 정수를 사용했습니다.\n";
        std::cout << "방어구 경파(대상:monster): \n";
        std::cout << "7 Turn/20 PowerDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 20, 7);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "얼음 정령") {
        std::cout << "얼음 정령의 정수를 사용했습니다.\n";
        std::cout << "서리 강화(대상:player): \n";
        std::cout << "2 Turn/60 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 60, 2);
        player[Pstat::Mp] -= 50;
    } else if (this->name == "헬 하운드") {
        std::cout << "헬 하운드의 정수를 사용했습니다.\n";
        std::cout << "6 Turn/25 ManaBurn\n";
        std::cout << "70 Turn/25 PowerDown\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 25, 6);
        effect.ReceiveEffect(EffectType::PowerDown, 25, 7);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "살라맨더") {
        std::cout << "살라맨더의 정수를 사용했습니다.\n";
        std::cout << "방어구 완파(대상:monster):\n";
        std::cout << "8 Turn/25 PowerDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 25, 8);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "와이번") {
        std::cout << "와이번의 정수를 사용했습니다.\n";
        std::cout << "심각한 출혈(대상:monster): \n";
        std::cout << "5 Turn/200 Bleed Damage\n";
        effect.ReceiveEffect(EffectType::Bleeding, 40, 5);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "맨티코어") {
        std::cout << "맨티코어의 정수를 사용했습니다.\n";
        std::cout << "맹독(대상:monster): \n";
        std::cout << "6 Turn/72 Damage\n";
        effect.ReceiveEffect(EffectType::Poison, 12, 6);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "피닉스") {
        std::cout << "피닉스의 정수를 사용했습니다.\n";
        std::cout << "극재생(대상:player): \n";
        std::cout << "5 Turn/100 Regen\n";
        playerEffect.ReceiveEffect(EffectType::Regen, 20, 5);
        player[Pstat::Mp] -= 60;
    } else {
        throw std::out_of_range("Unknown Essence");
    }
    StartLine();
}

void Essence::Skill(Alatreon& monster, Effect<Alatreon>& effect) {
    Player& player = Player::GetInstance();
    Effect<Player>& playerEffect = Effect<Player>::GetPlayerInstance(player);


    StartLine();

    if (this->name == "슬라임") {
        std::cout << "슬라임의 정수를 사용했습니다.\n";
        std::cout << "방어구 손상(대상:monster): \n";
        std::cout << "5 Turn/8 DefenceDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 8, 5);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "좀비") {
        std::cout << "좀비의 정수를 사용했습니다.\n";
        std::cout << "재생(대상:player): \n";
        std::cout << "5 Turn/20 Regen\n";
        playerEffect.ReceiveEffect(EffectType::Regen, 4, 5);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "고블린") {
        std::cout << "고블린의 정수를 사용했습니다.\n";
        std::cout << "방망이 타격(대상:monster): \n";
        std::cout << "4 Turn/16 Damage\n";
        effect.ReceiveEffect(EffectType::Bleeding, 4, 4);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "야생 늑대") {
        std::cout << "야생 늑대의 정수를 사용했습니다.\n";
        std::cout << "투기 강화(대상:player): \n";
        std::cout << "4 Turn/10 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 10, 4);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "키메라") {
        std::cout << "키메라의 정수를 사용했습니다.\n";
        std::cout << "독(대상:monster): \n";
        std::cout << "5 Turn/30 Damage\n";
        effect.ReceiveEffect(EffectType::Poison, 6, 5);
        player[Pstat::Mp] -= 10;
    } else if (this->name == "고스트") {
        std::cout << "고스트의 정수를 사용했습니다.\n";
        std::cout << "정신 침식(대상:monster): \n";
        std::cout << "4 Turn/8 ManaBurn\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 8, 4);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "서큐버스") {
        std::cout << "서큐버스의 정수를 사용했습니다.\n";
        std::cout << "매혹(대상:monster): \n";
        std::cout << "4 Turn/15 PowerDown\n";
        effect.ReceiveEffect(EffectType::PowerDown, 15, 4);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "인큐버스") {
        std::cout << "인큐버스의 정수를 사용했습니다.\n";
        std::cout << "매혹(대상:monster): \n";
        std::cout << "5 Turn/15 DefenceDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 15, 5);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "구울") {
        std::cout << "구울의 정수를 사용했습니다.\n";
        std::cout << "마나 침식(대상:monster): \n";
        std::cout << "5 Turn/15 ManaBurn\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 15, 5);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "웨어울프") {
        std::cout << "웨어울프의 정수를 사용했습니다.\n";
        std::cout << "고급 투기 강화(대상:player): \n";
        std::cout << "4 Turn/15 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 15, 4);
        player[Pstat::Mp] -= 15;
    } else if (this->name == "가고일") {
        std::cout << "가고일의 정수를 사용했습니다.\n";
        std::cout << "경화(대상:player): \n";
        std::cout << "4 Turn/18 DefenceUp\n";
        playerEffect.ReceiveEffect(EffectType::DefenceUp, 18, 4);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "마고일") {
        std::cout << "마고일의 정수를 사용했습니다.\n";
        std::cout << "칼날 경화(대상:player): \n";
        std::cout << "3 Turn/25 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 25, 3);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "미라") {
        std::cout << "미라의 정수를 사용했습니다.\n";
        std::cout << "방어구 부식(대상:monster): \n";
        std::cout << "5 Turn/20 DefenceDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 20, 5);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "데몬") {
        std::cout << "데몬의 정수를 사용했습니다.\n";
        std::cout << "저주(대상:monster): ";
        std::cout << "4 Turn/20 ManaBurn\n";
        std::cout << "4 Turn/25 PowerDown\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 20, 4);
        effect.ReceiveEffect(EffectType::PowerDown, 25, 4);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "골렘") {
        std::cout << "골렘의 정수를 사용했습니다.\n";
        std::cout << "고급 경화(대상:player): \n";
        std::cout << "4 Turn/25 DefenceUp\n";
        playerEffect.ReceiveEffect(EffectType::DefenceUp, 25, 4);
        player[Pstat::Mp] -= 25;
    } else if (this->name == "그리폰") {
        std::cout << "그리폰의 정수를 사용했습니다.\n";
        std::cout << "순풍(대상:player): \n";
        std::cout << "4 Turn/40 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 40, 4);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "뱀파이어") {
        std::cout << "뱀파이어의 정수를 사용했습니다.\n";
        std::cout << "출혈(대상:monster): \n";
        std::cout << "4 Turn/120 Bleed Damage\n";
        effect.ReceiveEffect(EffectType::Bleeding, 30, 4);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "세이렌") {
        std::cout << "세이렌의 정수를 사용했습니다.\n";
        std::cout << "고급 매혹(대상:monster): \n";
        std::cout << "5 Turn/30 PowerDown\n";
        effect.ReceiveEffect(EffectType::PowerDown, 30, 5);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "미노타우르스") {
        std::cout << "미노타우르스의 정수를 사용했습니다.\n";
        std::cout << "방어구 경파(대상:monster): \n";
        std::cout << "7 Turn/20 PowerDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 20, 7);
        player[Pstat::Mp] -= 30;
    } else if (this->name == "얼음 정령") {
        std::cout << "얼음 정령의 정수를 사용했습니다.\n";
        std::cout << "서리 강화(대상:player): \n";
        std::cout << "2 Turn/60 PowerUp\n";
        playerEffect.ReceiveEffect(EffectType::PowerUp, 60, 2);
        player[Pstat::Mp] -= 50;
    } else if (this->name == "헬 하운드") {
        std::cout << "헬 하운드의 정수를 사용했습니다.\n";
        std::cout << "6 Turn/25 ManaBurn\n";
        std::cout << "7 Turn/25 PowerDown\n";
        effect.ReceiveEffect(EffectType::ManaBurn, 25, 6);
        effect.ReceiveEffect(EffectType::PowerDown, 25, 7);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "살라맨더") {
        std::cout << "살라맨더의 정수를 사용했습니다.\n";
        std::cout << "방어구 완파(대상:monster):\n";
        std::cout << "8 Turn/25 PowerDown\n";
        effect.ReceiveEffect(EffectType::DefenceDown, 25, 8);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "와이번") {
        std::cout << "와이번의 정수를 사용했습니다.\n";
        std::cout << "심각한 출혈(대상:monster): \n";
        std::cout << "5 Turn/200 Bleed Damage\n";
        effect.ReceiveEffect(EffectType::Bleeding, 40, 5);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "맨티코어") {
        std::cout << "맨티코어의 정수를 사용했습니다.\n";
        std::cout << "맹독(대상:monster): \n";
        std::cout << "6 Turn/72 Damage\n";
        effect.ReceiveEffect(EffectType::Poison, 12, 6);
        player[Pstat::Mp] -= 40;
    } else if (this->name == "피닉스") {
        std::cout << "피닉스의 정수를 사용했습니다.\n";
        std::cout << "극재생(대상:player): \n";
        std::cout << "5 Turn/100 Regen\n";
        playerEffect.ReceiveEffect(EffectType::Regen, 20, 5);
        player[Pstat::Mp] -= 60;
    } else {
        throw std::out_of_range("Unknown Essence");
    }
    StartLine();
}


void Essence::OpenEssence() {
    this->lock = false;
}

void Essence::LockEssence() {
    this->lock = true;
}


void Essence::EnableEssence() {
    if (lock) {
    } else {
        this->enable = true;
    }
}

void Essence::DisableEssence() {
    if (lock) {
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
