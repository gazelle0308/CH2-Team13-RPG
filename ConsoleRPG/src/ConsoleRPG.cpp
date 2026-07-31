// Copyright 2026/07/30 NBC-CH2-Team13

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "DataBase/ItemDataBase.h"
#include "InventorySystem/InventorySystem.h"
#include "ShopSystem/ShopSystem.h"
#include "Player/Player.h"

int main()
{
	// 한글 출력
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	const std::vector<std::string> itemIds = ItemDataBase::GetInstance().GetAllItemIds();

	InventorySystem::GetInstance().ExpandInventory(1000);

	for (const std::string id : itemIds)
	{
		InventorySystem::GetInstance().AddItem(id, 11);
	}
}
