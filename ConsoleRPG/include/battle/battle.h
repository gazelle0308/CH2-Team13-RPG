/*
#ifndef BATTLE_H
#define BATTLE_H
#include <iostream>
#include <string>
#include <vector>
#include "monster/monster.h"
#include "player/player.h"
#include "boss/boss.h"


bool playerlive = 1;
bool monsterlive = 1;
int actionmenu;
int aftermenu;
int region = 0;
int damage = 0;

std::string choice;

std::map<std::string, std::vector <monster*>> regionmonsters;

void selectedregion(int region);
monster* CreateMonster(std::string choice);
void Encounter(monster*monster, regionmonsters[choice]);
void PlayerHealthCheck(player*player);
void MonsterHealthCheck(monster*monster);
void dealDamage(player*player, monster*monster);
void monsterdealDamage(player*player, monster*monster);
void Attack(player*player, monster*monster);
void BattleMenu(actionmenu);
void AfterMenu(aftermenu);

#endif
*/