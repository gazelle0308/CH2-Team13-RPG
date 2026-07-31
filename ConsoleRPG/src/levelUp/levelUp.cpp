// Copyright 2026/07/30 JinHo

#include "levelUp/levelUp.h"

#include <string>

#include "player/player.h"

void LevelUpPlayer(Player& player) {
    int levelSetup = player[Pstat::Level] - 1;

    while (player[Pstat::Exp] >= player[Pstat::MaxExp]) {
        player.SetLevel(player[Pstat::Level] + 1);

        player.SetExp(player[Pstat::Exp] - player[Pstat::MaxExp]);
        player.SetMaxExp(100 + (player[Pstat::Exp] - 1) * 40);

        player.SetBaseMaxHp(player[Pstat::BaseHp] + 10 * levelSetup);
        player.SetBaseMaxMp(player[Pstat::BaseMp] + 5 * levelSetup);

        player.SetCurrentMaxHp(player[Pstat::MaxHp] + 10 * levelSetup);
        player.SetCurrentMaxMp(player[Pstat::MaxMp] + 5 * levelSetup);

        player.SyncToMax(Pstat::Hp);
        player.SyncToMax(Pstat::Mp);

        player.SetBasePower(player[Pstat::BasePower] + 10 * levelSetup);
        player.SetBaseDefence(player[Pstat::BaseDefence] + 1 * levelSetup);

        player.SetCurrentPower(player[Pstat::Power] + 10 * levelSetup);
        player.SetCurrentDefence(player[Pstat::Defence] + 1 * levelSetup);
    }
}

void HuntRewardExp(int exp, Player& player) {
    player.SetExp(player[Pstat::Exp] + exp);
    if (player[Pstat::Exp] >= player[Pstat::MaxExp]) {
        LevelUpPlayer(player);
    }
}
