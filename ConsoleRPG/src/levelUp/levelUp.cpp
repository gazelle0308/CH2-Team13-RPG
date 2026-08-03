// Copyright 2026/07/30 JinHo


#include "levelUp/levelUp.h"

#include <string>

#include "Player/Player.h"

void LevelUpPlayer() {
    Player& player = Player::GetInstance();

    while (player.GetExp() >= player.GetMaxExp()) {
        player.SetLevel(player.GetLevel() + 1);

        player.SetExp(player.GetExp() - player.GetMaxExp());
        player.SetMaxExp(100 + (player.GetLevel() - 1) * 40);

        player.SetBaseMaxHp(player.GetBaseMaxHp() + 20 *
                           (player.GetLevel() - 1));
        player.SetBaseMaxMp(player.GetBaseMaxMp() + 5 *
                           (player.GetLevel() - 1));

        player.SetCurrentMaxHp(player.GetCurrentMaxHp() + 20 *
                              (player.GetLevel() - 1));
        player.SetCurrentMaxMp(player.GetCurrentMaxMp() + 5 *
                              (player.GetLevel() - 1));

        player.SyncToMax(Pstat::Hp);
        player.SyncToMax(Pstat::Mp);

        player.SetBasePower(player.GetBasePower() + 5 *
                           (player.GetLevel() - 1));
        player.SetBaseDefence(player.GetBaseDefence() + 1 *
                             (player.GetLevel() - 1));

        player.SetCurrentPower(player.GetCurrentPower() + 5 *
                              (player.GetLevel() - 1));
        player.SetCurrentDefence(player.GetCurrentDefence() + 1 *
                                (player.GetLevel() - 1));
    }
}

void HuntRewardExp(int exp) {
    Player& player = Player::GetInstance();

    player.SetExp(player.GetExp() + exp);
    if (player.GetExp() >= player.GetMaxExp()) {
        LevelUpPlayer();
    }
}
