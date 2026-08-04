// Copyright 2026/07/30 NBC-CH2-Team13

#define NOMINMAX
#include <Windows.h>
#include <random>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
#include "DataBase/ItemDataBase.h"
#include "InventorySystem/InventorySystem.h"
#include "ShopSystem/ShopSystem.h"
#include "PotionWorkshop/PotionWorkshop.h"
#include "Player/Player.h"
#include "Monster/Monster.h"
#include "Essence/EssenceOrb.h"
#include "LevelUp/levelUp.h"
#include "Boss/Boss.h"

int main()
{
	// 한글 출력
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Player& player = Player::GetInstance();

	InventorySystem& inventorySystem = InventorySystem::GetInstance();

	const std::vector<std::string> itemIds = ItemDataBase::GetInstance().GetAllItemIds();

	inventorySystem.ExpandInventory(78);

	for (const std::string id : itemIds)
	{
		inventorySystem.AddItem(id, 11);
	}

	int number{};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 1);

	Effect<Player>& playerEffect =
		Effect<Player>::GetPlayerInstance(player);
	EssenceOrb& orb = EssenceOrb::GetInstance();

	Alatreon boss;
	Effect<Alatreon> bossEffect(boss);

	for (int loop = 0; loop < 25; loop = loop + 1) {
		orb[loop].OpenEssence();
	}

	bool endDebug = true;
	HuntRewardExp(3000);

	while (endDebug) {
		boss.StartTurn();
		int choice{};
		int use_choice{};

		player.ViewStatus();
		std::cout << "================ 메뉴 ================" << std::endl;
		std::cout << "1. 스킬 사용" << std::endl;
		std::cout << "2. 정수 교체" << std::endl;
		std::cout << "3. 멀뚱멀뚱" << std::endl;
		std::cout << "4. 디버그 완료" << std::endl;
		std::cout << "입력: ";
		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(
				std::numeric_limits<std::streamsize>::max(),
				'\n'
			);
		}
		std::cout << "=======================================\n";

		switch (choice)
		{
		case 1:
			orb.UseSkill(boss, bossEffect);
			boss.BeforeEffect();
			playerEffect.Bleed();
			boss.AfterEffect();
			break;
		case 2:
			std::cout << orb.GetOrbInfo();
			std::cout << "사용 정수 입력: ";
			if (!(std::cin >> use_choice)) {
				std::cin.clear();
				std::cin.ignore(
					std::numeric_limits<std::streamsize>::max(),
					'\n'
				);
			}
			player.SetEssence(orb.UseEssence(use_choice));
			break;
		case 3:
			break;
		case 4:
			endDebug = false;
			break;
		}

		if (boss.getmp() > 0) {
			if (dist(gen) == 0) {
				boss.AlatreonAttack();
				boss.BeforeEffect();
				bossEffect.Bleed();
				boss.AfterEffect();
			}
			else {
				boss.AlatreonSkill();
			}
		}
		else {
			boss.AlatreonAttack();
			bossEffect.Bleed();
		}

		boss.BeforeEffect();
		bossEffect.Tick();
		playerEffect.Tick();
		boss.EndTurn();
	}


	while (true)
	{
		std::cout << "================ 메뉴 ================" << std::endl;
		std::cout << "1. 인벤토리 조회" << std::endl;
		std::cout << "2. 상점" << std::endl;
		std::cout << "3. 포션 제작소" << std::endl;
		std::cout << "4. 전투 중 인벤토리 조회" << std::endl;

		std::cin >> number;

		switch (number)
		{
		case 1:
			inventorySystem.ShowInventoryInNormal();
			break;
		case 2:
			ShopSystem::GetInstance().ShowShop();
			break;
		case 3:
			PotionWorkshop::GetInstance().ShowPotionWorkshop();
			break;
		case 4:
			inventorySystem.ShowInventoryInBattle();
			break;
		}
	}
}
