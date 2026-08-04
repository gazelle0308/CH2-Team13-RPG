// Copyright 2026/07/30 JinHo


#include "Effect/Effect.h"

#include <iostream>

#include "Player/Player.h"
#include "Monster/Monster.h"
#include "Boss/Boss.h"

template<>
void Effect<Player>::ApplyPotion(EffectType target,
                                 unsigned int amount,
                                 unsigned int turn) {
    if (target == EffectType::PotionPowerUp) {
        this->entity.ApplyEffect(Pstat::BuffPower, amount);
        this->onBuff[8] = true;
        this->LeftTurn[8] = turn;
        std::cout << "당신은 공격력 증가 포션을 사용했습니다!\n";
        std::cout << "(" << LeftTurn[8] << "턴 간 "
                         << this->entity.GetBuffPower()
                         << "의 공격력이 증가합니다.).\n";
    } else if (target == EffectType::PotionDefenceUp) {
        this->entity.ApplyEffect(Pstat::BuffDefence, amount);
        this->onBuff[9] = true;
        this->LeftTurn[9] = turn;
        std::cout << "당신은 방어력 증가 포션을 사용했습니다!\n";
        std::cout << "(" << LeftTurn[9] << "턴 간 "
                         << this->entity.GetBuffDefence()
                         << "의 방어력이 증가합니다.).\n";
    } else if (target == EffectType::PotionHeal) {
        this->entity.ApplyEffect(Pstat::Hp, amount);
        std::cout << "당신은 Hp 회복 포션을 사용했습니다!\n";
        std::cout << "(" << amount << "만큼 회복 합니다.).\n";
    } else if (target == EffectType::PotionMana) {
        this->entity.ApplyEffect(Pstat::Mp, amount);
        std::cout << "당신은 Mp 회복 포션을 사용했습니다!\n";
        std::cout << "(" << amount << "만큼 회복 합니다.).\n";
    } else {
        throw std::logic_error("That is not potion effect");
    }
}

template<>
void Effect<Monster>::ApplyPotion(EffectType target,
                                  unsigned int amount,
                                  unsigned int turn) {
    throw std::logic_error("Monster is not have potion effect!");
}

template<>
void Effect<Alatreon>::ApplyPotion(EffectType target,
                                   unsigned int amount,
                                   unsigned int turn) {
    throw std::logic_error("Monster is not have potion effect!");
}

template<>
void Effect<Player>::EndPotion(unsigned int effect) {
    if (effect == 8) {
        this->entity.ApplyEffect(Pstat::BuffPower, 0);
        this->onBuff[effect] = false;
        std::cout << "공격력 증가 포션의 효과가 떨어졌습니다!\n";
    } else if (effect == 9) {
        this->entity.ApplyEffect(Pstat::BuffDefence, 0);
        this->onBuff[effect] = false;
        std::cout << "방어력 증가 포션의 효과가 떨어졌습니다!\n";
    } else {
        throw std::logic_error("That is not potion effect");
    }
}

template<>
void Effect<Monster>::EndPotion(unsigned int effect) {
    throw std::logic_error("Monster is not have potion effect!");
}

template<>
void Effect<Alatreon>::EndPotion(unsigned int effect) {
    throw std::logic_error("Alatreon is not have potion effect!");
}

template<>
void Effect<Player>::EndEffect(unsigned int effect) {
    if (effect == 3) {
        entity.setatk(entity.getatk() + this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "공격력 저하의 효과가 떨어졌습니다!\n";
    } else if (effect == 4) {
        entity.setdef(entity.getdef() + this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "방어력 저하의 효과가 떨어졌습니다!\n";
    } else if (effect == 6) {
        entity.setatk(entity.getatk() - this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "공격력 증가의 효과가 떨어졌습니다!\n";
    } else if (effect == 7) {
        entity.setdef(entity.getdef() - this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "방어력 증가의 효과가 떨어졌습니다!\n";
    } else if (effect > 7 && effect < 10) {
        this->EndPotion(effect);
    } else if((effect < 3 && effect >= 0)|| effect == 5) {
        return;
    } else {
        throw std::out_of_range("No more effect");
    }
}

template<>
void Effect<Monster>::EndEffect(unsigned int effect) {
    if (effect == 3) {
        entity.setatk(entity.getatk() + this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 공격력 저하의 효과가 떨어졌습니다!\n";
    } else if (effect == 4) {
        entity.setdef(entity.getdef() + this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 방어력 저하의 효과가 떨어졌습니다!\n";
    } else if (effect == 6) {
        entity.setatk(entity.getatk() - this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 공격력 증가의 효과가 떨어졌습니다!\n";
    } else if (effect == 7) {
        entity.setdef(entity.getdef() - this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 방어력 증가의 효과가 떨어졌습니다!\n";
    } else if((effect < 3 && effect >= 0)|| effect == 5) {
        return;
    } else {
        throw std::out_of_range("No more effect");
    }
}

template<>
void Effect<Alatreon>::EndEffect(unsigned int effect) {
    if (effect == 3) {
        entity.setatk(entity.getatk() + this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 공격력 저하의 효과가 떨어졌습니다!\n";
    }
    else if (effect == 4) {
        entity.setdef(entity.getdef() + this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 방어력 저하의 효과가 떨어졌습니다!\n";
    }
    else if (effect == 6) {
        entity.setatk(entity.getatk() - this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 공격력 증가의 효과가 떨어졌습니다!\n";
    }
    else if (effect == 7) {
        entity.setdef(entity.getdef() - this->amount[effect]);
        this->amount[effect] = 0;
        this->onBuff[effect] = false;
        std::cout << "적의 방어력 증가의 효과가 떨어졌습니다!\n";
    }
    else if ((effect < 3 && effect >= 0) || effect == 5) {
        return;
    }
    else {
        throw std::out_of_range("No more effect");
    }
}

template<>
void Effect<Player>::Tick() {
    for (int i = 0; i < 10; i = i + 1) {
        UpdateEffect(i);
    }
}

template<>
void Effect<Monster>::Tick() {
    for (int i = 0; i < 8; i = i + 1) {
        UpdateEffect(i);
    }
}

template<>
void Effect<Alatreon>::Tick() {
    for (int i = 0; i < 8; i = i + 1) {
        UpdateEffect(i);
    }
}

template<>
void Effect<Player>::ClearEffect() {
    for (int i = 0; i < 10; i = i + 1) {
        if (i == 3) {
            entity.setatk(entity.getatk() +
                          this->amount[i]);
        } else if (i == 4) {
            entity.setdef(entity.getdef() +
                          this->amount[i]);
        } else if (i == 6) {
            entity.setatk(entity.getatk() +
                          this->amount[i]);
        } else if (i == 7) {
            entity.setdef(entity.getdef() +
                          this->amount[i]);
        } else if (i == 8) {
            this->entity.ApplyEffect(Pstat::BuffPower, 0);
        } else if (i == 9) {
            this->entity.ApplyEffect(Pstat::BuffDefence, 0);
        }

        if (i < 8) {
            this->amount[i] = 0;
        }

        this->LeftTurn[i] = 0;
        this->onBuff[i] = false;
    }
}

template<>
void Effect<Monster>::ClearEffect() {
    for (int i = 0; i < 8; i = i + 1) {
        if (i == 3) {
            entity.setatk(entity.getatk() +
                          this->amount[i]);
        } else if (i == 4) {
            entity.setdef(entity.getdef() +
                          this->amount[i]);
        } else if (i == 6) {
            entity.setatk(entity.getatk() +
                          this->amount[i]);
        } else if (i == 7) {
            entity.setdef(entity.getdef() +
                          this->amount[i]);
        }

        this->amount[i] = 0;
        this->LeftTurn[i] = 0;
        this->onBuff[i] = false;
    }
}

template<>
void Effect<Alatreon>::ClearEffect() {
    for (int i = 0; i < 8; i = i + 1) {
        if (i == 3) {
            entity.setatk(entity.getatk() +
                this->amount[i]);
        } else if (i == 4) {
            entity.setdef(entity.getdef() +
                this->amount[i]);
        } else if (i == 6) {
            entity.setatk(entity.getatk() +
                this->amount[i]);
        } else if (i == 7) {
            entity.setdef(entity.getdef() +
                this->amount[i]);
        }

        this->amount[i] = 0;
        this->LeftTurn[i] = 0;
        this->onBuff[i] = false;
    }
}
