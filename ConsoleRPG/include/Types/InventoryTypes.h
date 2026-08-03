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

struct FItemSlot
{
public:
	FItemData itemData;
	int count = 0;

public:
	void SetItemData(FItemData itemData_) {
		itemData = itemData_;
	}
	void SetCount(int count_) {
		count = count_;
	}

	const FItemData& GetItemData() const {
		return itemData;
	}
	int GetCount() const {
		return count;
	}
	std::string GetId() const {
		return itemData.GetId();
	}
	EItemCategory GetCategory() const {
		return itemData.GetCategory();
	}
	std::string GetName() const {
		return itemData.GetName();
	}
	std::string GetDescription() const {
		return itemData.GetDescription();
	}
	int GetPrice() const {
		return itemData.GetPrice();
	}
	int GetMaxStackCount() const {
		return itemData.GetMaxStackCount();
	}
};