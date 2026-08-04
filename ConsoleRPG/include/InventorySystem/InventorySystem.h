#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <format>

#include "Types/InventoryTypes.h"
#include "DataBase/ItemDataBase.h"
#include "DataBase/InventoryDataBase.h"
#include "Factory/ItemFactory.h"

inline bool compareName(const FItemSlot& a, const FItemSlot& b)
{
	std::string aName = a.GetName();
	std::string bName = b.GetName();

	if (aName == bName)
	{
		return a.count > b.count;
	}

	return aName < bName;
}

inline bool compareFunc(const FItemSlot& a, const FItemSlot& b)
{
	// 기능 별로 순서 정해서 오름차순 정렬

	ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
	FEnumDisplay enumDisplay;
	EItemCategory aCategory = a.GetCategory();
	EItemCategory bCategory = b.GetCategory();
	int aSequence = enumDisplay.GetItemCategorySequence(aCategory);
	int bSequence = enumDisplay.GetItemCategorySequence(bCategory);

	if (aCategory == bCategory)
	{
		std::string aId = a.GetId();
		std::string bId = b.GetId();
		
		switch (aCategory)
		{
		case EItemCategory::Consumable:
		{
			std::vector<EConsumableType> aTypes{};
			std::vector<EConsumableType> bTypes{};
			
			if (itemDataBase.GetConsumableTypes(aId, aTypes) && itemDataBase.GetConsumableTypes(bId, bTypes))
			{
				if (!aTypes.empty() && !bTypes.empty())
				{
					aSequence = enumDisplay.GetConsumableTypeSequence(aTypes[0]);
					bSequence = enumDisplay.GetConsumableTypeSequence(bTypes[0]);
				}
			}

			break;
		}
		case EItemCategory::Upgrade:
		{
			EUpgradeType aUpgradeType{};
			EUpgradeType bUpgradeType{};

			if (itemDataBase.GetUpgradeType(aId, aUpgradeType) && itemDataBase.GetUpgradeType(bId, bUpgradeType))
			{
				aSequence = enumDisplay.GetUpgradeTypeSequence(aUpgradeType);
				bSequence = enumDisplay.GetUpgradeTypeSequence(bUpgradeType);
			}

			break;
		}
		case EItemCategory::Material:
		{
			EMaterialType aMaterialType{};
			EMaterialType bMaterialType{};

			if (itemDataBase.GetMaterialType(aId, aMaterialType) && itemDataBase.GetMaterialType(bId, bMaterialType))
			{
				aSequence = enumDisplay.GetMaterialTypeSequence(aMaterialType);
				bSequence = enumDisplay.GetMaterialTypeSequence(bMaterialType);
			}

			break;
		}
		}

		if (aSequence == bSequence)
		{
			return compareName(a, b);
		}
	}

	return aSequence < bSequence;
}

inline bool comparePrice(const FItemSlot& a, const FItemSlot& b)
{
	int aPrice = a.GetPrice();
	int bPrice = b.GetPrice();

	if (aPrice == bPrice)
	{
		return compareFunc(a, b);
	}

	return aPrice < bPrice;
}

class InventorySystem
{
private:
	std::vector<FItemSlot> items;
	int inventorySize;
	int inventoryCount;

private:
	InventorySystem() : inventorySize(20), inventoryCount(0) {
		items.clear();
		SetInventoryData();
	}

	// 복사 방지
	InventorySystem(const InventorySystem&) = delete;
	InventorySystem& operator=(const InventorySystem&) = delete;

	// 이동 방지
	InventorySystem(InventorySystem&&) = delete;
	InventorySystem& operator=(InventorySystem&&) = delete;

public:
	// 싱글톤
	static InventorySystem& GetInstance() {
		static InventorySystem instance;
		return instance;
	}

	void ShowInventoryInNormal();
	void ShowInventoryInBattle();
	void ShowInventoryInShop(double buybackRate, int& totalBuyPrice, bool& isEnd);
	void ShowInventoryInPotionWorkshop();

	int CanCraftPotion(std::vector<std::pair<int, int>>& materials, std::string potionId, int potionCount); // 0: 성공, 1: 공간 부족, 2: 재료 부족, 3: 잘못된 index
	bool GetItemData(int index, FItemData& itemData) const;
	std::string GetId(int index) const;

//private:
public: // 테스트 위해 public 설정
	void SetInventoryData();

	void ClearScreen() const;
	void PrintInventoryItems(EInventoryViewMode mode, double buybackRate = 1) const;
	void HandleNormalInventoryOptions(bool& isEnd);
	void HandleBattleInventoryOptions(bool& isEnd);
	void PrintPlayerGold() const;
	void HandleShopInventoryOptions(double buybackRate, int& totalBuyPrice, bool& isEnd);
	void HandleNormalItemSelection();
	void PrintItemInfo(int index) const;
	void HandleNormalItemOptions(int index);
	void HandleNormalUsableItemOptions(int index);
	void HandleNormalNonUsableItemOptions(int index);
	void HandleShopItemOptions(int index, double buybackRate, int& totalBuyPrice);
	void HandleDiscardItem(int index);

	bool AddItem(std::string id, int itemCount = 1);
	int RemoveItem(int index, int itemCount = 1); // 0: 성공, 1: 개수 초과, 2: 잘못된 inde
	int FindItem(std::string id) const; // -1: fail, 0~: index(동일한 아이템 존재 시 아이템 가장 적게 들어있는 슬롯)
	int GetTotalItemCount(int index) const;
	bool UseItem(int index);

	void SortByName();
	void SortByFunc();
	void SortByPrice();
	void MergeSameItems();

	void ExpandInventory(int size);
};