// Copyright 2026/07/30 NBC-CH2-Team13

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "DataBase/ItemDataBase.h"
#include "InventorySystem/InventorySystem.h"
#include "ShopSystem/ShopSystem.h"
#include "PotionWorkshop/PotionWorkshop.h"
#include "Player/Player.h"
#include "Monster/Monster.h"
#include "Essence/EssenceOrb.h"
#include "LevelUp/levelUp.h"

int main()
{
	// 한글 출력
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Player& player = Player::GetInstance();
	InventorySystem& inventorySystem = InventorySystem::GetInstance();

	const std::vector<std::string> itemIds = ItemDataBase::GetInstance().GetAllItemIds();

	InventorySystem::GetInstance().ExpandInventory(78);
	for (const std::string id : itemIds)
	{
		InventorySystem::GetInstance().AddItem(id, 11);
	}

	int number{};

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
