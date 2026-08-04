#pragma once

#include <iostream>
#include <string>
#include "item/item.h"
#include "Item/ConsumableItem.h"
#include "Item/UpgradeItem.h"
#include "Item/MaterialItem.h"

class ItemFactory
{
public:
	std::unique_ptr<ConsumableItem> CreateConsumableItem(std::string id) const;
	std::unique_ptr<UpgradeItem> CreateUpgradeItem(std::string id) const;
	std::unique_ptr<MaterialItem> CreateMaterialItem(std::string id) const;
};

