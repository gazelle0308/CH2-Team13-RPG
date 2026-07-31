#pragma once

#include <iostream>
#include "Item/Item.h"
#include "Types/ItemTypes.h"

enum class EInventoryViewMode
{
	Normal,
	Shop,
};

struct FInventorySlot
{
//public:
	//std::unique_ptr<Item> item;
	FItemData itemData;
	int count = 0;
	//int maxCount;

//public:
	//FInventorySlot() : item(nullptr), count(0), maxCount(0) {}
};