#pragma once

#include <iostream>
#include "Item/Item.h"
#include "Types/ItemTypes.h"

enum class EInventoryViewMode
{
	Normal,
	Battle,
	Shop,
	PotionWorkshop,
};

struct FInventorySlot
{
	FItemData itemData;
	int count = 0;
};