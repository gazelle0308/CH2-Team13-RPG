// Copyright 2026/07/30 JinHo
#pragma once

#include <iostream>

#include "Player/Player.h"
#include "Monster/Monster.h"

class Player;
class Monster;

enum class EffectType {
    Poison,
    Bleeding,
    ManaBurn,
    PowerDown,
    DefenceDown,
    Regen,
    PowerUp,
    DefenceUp,
    PotionPowerUp,
    PotionDefenceUp,
    PotionHeal,
    PotionMana,
    NoEffect
};

template<typename Entity>
class Effect {
 public:
     void Bleed() {
         if (this->onBuff[1]) {
             this->entity.sethp(this->entity.gethp() -
                                this->amount[1]);
             std::cout << "=====================================================\n";
             std::cout << "( " << this->entity.getName()
                               << "의 출혈 "
                               << this->amount[1]
                               << " 데미지!).\n";
             std::cout << "=====================================================\n";
         }
     }

     void ReceiveEffect(EffectType target, unsigned int amount, unsigned int turn = 3) {
         if (target == EffectType::Poison) {
             this->onBuff[0] = true;
             this->LeftTurn[0] = turn;
             this->amount[0] = amount;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName()
                       << "은 독에 걸렸습니다!\n";
             std::cout << "(매턴 Hp - "
                       << this->amount[0]
                       << "의 데미지를 받습니다.).\n";
             std::cout << "=====================================================\n";
         } else if (target == EffectType::Bleeding) {
             this->onBuff[1] = true;
             this->LeftTurn[1] = turn;
             this->amount[1] = amount;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName()
                       << "은 출혈에 걸렸습니다!\n";
             std::cout << "(매턴 공격시 Hp -"
                       << this->amount[1]
                       << "의 데미지를 받습니다.).\n";
             std::cout << "=====================================================\n";
         } else if (target == EffectType::ManaBurn) {
             this->onBuff[2] = true;
             this->LeftTurn[2] = turn;
             this->amount[2] = amount;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName()
                       << "은 마나 저주에 걸렸습니다!\n";
             std::cout << "(매턴 Mp -"
                       << this->amount[2]
                       << "의 데미지를 받습니다.).\n";
             std::cout << "=====================================================\n";
         } else if (target == EffectType::PowerDown) {
             this->LeftTurn[3] = turn;
             this->amount[3] = amount;

             if (!onBuff[3]) {
                 this->entity.setatk(this->entity.getatk() -
                                     this->amount[3]);
             }
             this->onBuff[3] = true;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName()
                       << "은 공격력 저하에 걸렸습니다!\n";
             std::cout << "(" << LeftTurn[3]
                       << "턴 간"
                       << this->amount[3]
                       << "의 공격력이 떨어집니다.).\n";
             std::cout << "=====================================================\n";
         } else if (target == EffectType::DefenceDown) {
             this->LeftTurn[4] = turn;
             this->amount[4] = amount;

             if (!onBuff[4]) {
                 this->entity.setdef(this->entity.getdef() -
                                     this->amount[4]);
             }
             this->onBuff[4] = true;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName() << "은 방어력 저하에 걸렸습니다!\n";
             std::cout << "(" << LeftTurn[4]
                              << "턴 간"
                              << this->amount[4]
                              << "의 방어력이 떨어집니다.).\n";
             std::cout << "=====================================================\n";
         } else if (target == EffectType::Regen) {
             this->onBuff[5] = true;
             this->LeftTurn[5] = turn;
             this->amount[5] = amount;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName()
                       << "은 재생을 받았습니다!\n";
             std::cout << "(매턴 "
                       << this->amount[5]
                       << "씩  회복합니다.).\n";
             std::cout << "=====================================================\n";
         } else if (target == EffectType::PowerUp) {
             this->LeftTurn[6] = turn;
             this->amount[6] = amount;
             if (!onBuff[6]) {
                 this->entity.setdef(this->entity.getatk() +
                                     this->amount[6]);
             }
             this->onBuff[6] = true;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName()
                       << "은 공격력 증가를 받았습니다!\n";
             std::cout << "(" << LeftTurn[6]
                       << "턴 간"
                       << this->amount[6]
                       << "의 공격력이 증가합니다.).\n";
             std::cout << "=====================================================\n";
         } else if (target == EffectType::DefenceUp) {
             this->LeftTurn[7] = turn;
             this->amount[7] = amount;
             if (!onBuff[7]) {
                 this->entity.setdef(this->entity.getdef() +
                                     this->amount[7]);
             }
             this->onBuff[7] = true;
             std::cout << "=====================================================\n";
             std::cout << this->entity.getName()
                       << "은 방어력 증가를 받았습니다!\n";
             std::cout << "(" << LeftTurn[7]
                       << "턴 간"
                       << this->amount[7]
                       << "의 방어력이 증가합니다.).\n";
             std::cout << "=====================================================\n";
         } else {
             throw std::logic_error("Unknown Effect!");
         }
     }

     void DotEffect(int effect);

     void ApplyPotion(EffectType target, unsigned int amount, unsigned int turn = 3);

     void EndPotion(unsigned int effect);

     void EndEffect(unsigned int effect);

     void Tick();

     void ClearEffect();

     static Effect& GetPlayerInstance(Entity& entity) {
         static Effect<Entity> PlayerInstance(entity);
         return PlayerInstance;
     }

     explicit Effect(Entity& entity) :
         entity(entity) {
         cMaxBuf = entity.gethp();
     }

 private:

     Effect(const Effect&) = delete;
     Effect& operator=(const Effect&) = delete;

     Entity& entity;

     int cMaxBuf = 0;

     int amount[8] = {};

     int LeftTurn[10] = {};

     bool onBuff[10] = {};

     // index에 따라 버프 결정
     // index list
     // 0 = 독
     // 1 = 출혈
     // 2 = 마나 감소
     // 3 = 공격력 저하
     // 4 = 방어력 저하
     // 5 = 재생
     // 6 = 공격력 증가
     // 7 = 방어력 증가
     // 8 = 포션 공격력 증가-Player만 가능
     // 9 = 포션 방어력 증가-Player만 가능

     // Function
     void UpdateEffect(int effect) {
         if (LeftTurn[effect] == 0) { return; }

         this->LeftTurn[effect] = this->LeftTurn[effect] - 1;
         this->DotEffect(effect);

         if (LeftTurn[effect] == 0) {
             this->onBuff[effect] = false;
             this->EndEffect(effect);
         }
     }
};
