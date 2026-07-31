#include "battle/battle.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include "monster/monster.h"
#include "player/player.h"
#include "boss/boss.h"
// 각 상속 받은 몬스터의 헤더 파일 임의 monster로 include.
//#include "monster/a.h"
//#include "monster/b.h"
//#include "monster/c.h"
//#include "monster/d.h"
//#include "monster/e.h"
//#include "monster/f.h"
//#include "monster/g.h"
//#include "monster/h.h"
//#include "monster/i.h"
//#include "monster/j.h"
//#include "monster/k.h"
//#include "monster/l.h"
//#include "monster/n.h"
//#include "monster/m.h"
//#include "monster/o.h"
//
//
//void selectedregion(int region) {
//    std::cout << "===============================\n";
//    std::cout << "  어느 지역을 탐색하시겠습니까?\n";
//    std::cout << "-------------------------------\n";
//    std::cout << "1. 라벤더 들판  2. 검은 숲  3. 스산한 협곡\n";
//    std::cout << "4. 로야 빙원  5. 라플라 화산 지대 0. 다시 마을로 \n";
//    std::cout << "===============================\n";
//    std::cout << "선택한 지역:";
//    std::cin >> region;
//    switch (region) {
//    case 1:
//    {
//        std::string choice = "라벤더 들판";
//        break;
//    }
//    case 2:
//    {
//        std::string choice = "검은 숲";
//        break;
//    }
//    case 3:
//    {
//        std::string choice = "스산한 협곡";
//        break;
//    }
//    case 4:
//    {
//        std::string choice = "로야 빙원";
//        break;
//    }
//    case 5:
//    {
//        std::string choice = "라플라 화산 지대";
//        break;
//    }
//    case 0:
//    {
//        std::cout << "오늘은 여기까지..마을로 돌아가자.\n";
//        VillageMenu();
//        break;
//    }
//    }
//}
//
//
//monster* CreateMonster(std::string choice) {
//    std::map<std::string, std::vector <monster*>> regionmonsters; 
//    regionmonsters["라벤더 들판"] = { new a(), new b(), new c() };
//    regionmonsters["검은 숲"] = { new d(), new e(), new f() };
//    regionmonsters["스산한 협곡"] = { new g(), new h(), new i() };
//    regionmonsters["로야 빙원"] = { new j(), new k(), new l() };
//    regionmonsters["라플라 화산 지대"] = { new n(), new m(), new o() };
//}
//
//void Encounter(monster*monster, regionmonsters[choice]) {
//    rand() % 3;
//    vector<monster*>& monsters = regionmonsters[choice];
//    std::cout << "\n당신은 야생의 " << monster->getname() << "와(과) 마주쳤다!\n";
//}
//
//bool PlayerHealthCheck(Player*player) {
//    if (player["hp"] > 0) {
//        playerlive = 1;
//    } else if (player["hp"] <= 0) {
//        playerlive = 0;
//    }
//}
//bool MonsterHealthCheck(Monster*monster) {
//    if (Monster->GetHp() > 0) {
//        monsterlive = 1;
//    } else if (player->GetHp() <= 0) {
//        monsterlive = 0;
//    }
//}
//
//void dealDamage(player*player, monster*monster) {
//    if (player["power"] - monster->getdefense() <= 0) {
//        damage = 1;
//    } else {
//        damage = player["power"] - monster->getdefense();
//    }
//}
//
//void monsterdealDamage(player*player, monster*monster) {
//    if (monster->getpower() - player["defence"] <= 0) {
//        damage = 1;
//    } else {
//        damage = monster->getpower() - player["defence"];
//    }
//}
//
//void Attack(player*player, monster*monster) {
//}
//
//void BattleMenu(actionmenu) {
//    std::cout << "===============================\n";
//    std::cout << "      행동을 선택해주세요.\n";
//    std::cout << "===============================\n";
//    std::cout << "1. 공격  2. 정수 가방  3. 아이템\n";
//    std::cout << "===============================\n";
//    std::cout << "번호를 선택해주요. : ";
//    std::cin >> actionmenu;
//    switch (actionmenu) {
//    case 1:
//    {
//        cout << "공격\n";
//    }
//    case 2:
//    {
//        cout << "정수 사용\n";
//    }
//    case 3;
//    {
//        cout << "Item 사용\n";
//    }
//    }
//}
//void AfterMenu(aftermenu) {
//    std::cout << "===============================\n";
//    std::cout << "      행동을 선택해주세요.\n";
//    std::cout << "===============================\n";
//    std::cout << "1. 지역 재탐색  2. 마을로 이동  3. 정수 가방 확인\n";
//    std::cout << "4. 아이템 사용  0. 게임 종료?\n";
//    std::cout << "===============================\n";
//    std::cout << "번호를 선택해주요. : ";
//    std::cin >> aftermenu;
//    switch (aftermenu) {
//    case 1:
//    {
//        cout << "지역을 재탐색합니다.\n";
//    }
//    case 2:
//    {
//        cout << "마을로 이동합니다.\n";
//    }
//    case 3:
//    {
//        cout << "정수 가방을 확인합니다.\n";
//    }
//    case 4:
//    {
//        cout << "아이템을 사용합니다.\n";
//    }
//    case 0:
//    {
//        IsGameEnd = 1;
//    }
//    }
//}
