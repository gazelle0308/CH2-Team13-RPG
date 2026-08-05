// Copyright 2026/07/30 JinHo


#include "levelUp/levelUp.h"

#include <string>
#include <iostream>

#include "Utility/Utility.h"
#include "Player/Player.h"

void LevelUpPlayer() {
    Player& player = Player::GetInstance();
    const Player& readPlayer = Player::GetReadInstance();

    if (player.GetLevel() >= 10) {
        player.SetExp(player.GetMaxExp());
        return;
    }

    while (player.GetExp() >= player.GetMaxExp()) {
        if (player.GetLevel() >= 10) {
            player.SetExp(player.GetMaxExp());
            return;
        }
        StartLine();
        std::cout << "레벨업!\n";
        StartLine();
        player.SetLevel(player.GetLevel() + 1);

        player.SetExp(player.GetExp() - player.GetMaxExp());
        player.SetMaxExp(100 + (player.GetLevel() - 1) * 40);

        player.SetBaseMaxHp(player.GetBaseMaxHp() + 20);
        player.SetBaseMaxMp(player.GetBaseMaxMp() + 5);

        player.SetCurrentMaxHp(player.GetCurrentMaxHp() + 20);
        player.SetCurrentMaxMp(player.GetCurrentMaxMp() + 5);

        player.SyncToMax(Pstat::Hp);
        player.SyncToMax(Pstat::Mp);

        player.SetBasePower(player.GetBasePower() + 5);
        player.SetBaseDefence(player.GetBaseDefence() + 1);

        player.SetCurrentPower(player.GetCurrentPower() + 5);
        player.SetCurrentDefence(player.GetCurrentDefence() + 1);
        player.ApplyEffect(Pstat::BuffPower, readPlayer[Pstat::BuffPower]);
        player.ApplyEffect(Pstat::BuffDefence, readPlayer[Pstat::BuffDefence]);
    }
}

void HuntRewardExp(int exp) {
    Player& player = Player::GetInstance();

    player.SetExp(player.GetExp() + exp);
    if (player.GetExp() >= player.GetMaxExp()) {
        LevelUpPlayer();
    }
}
