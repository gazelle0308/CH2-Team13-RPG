#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <format>

#include "Types/InventoryTypes.h"
#include "DataBase/ItemDataBase.h"
#include "Factory/ItemFactory.h"

inline bool compareName(const FInventorySlot& a, const FInventorySlot& b)
{
	//std::string aName = a.item->GetName();
	//std::string bName = b.item->GetName();
	std::string aName = a.itemData.name;
	std::string bName = b.itemData.name;

	return aName < bName;
}

inline bool comparePrice(const FInventorySlot& a, const FInventorySlot& b)
{
	//int aPrice = a.item->GetPrice();
	//int bPrice = b.item->GetPrice();
	int aPrice = a.itemData.price;
	int bPrice = b.itemData.price;

	return aPrice < bPrice;
}

inline bool compareFunc(const FInventorySlot& a, const FInventorySlot& b)
{
	// id를 ITEM_CONSUMABLE_HP_01 과 같은 형식으로 설정했음을 전제

	//std::string aId = a.item->GetId();
	//std::string bId = b.item->GetId();
	std::string aId = a.itemData.id;
	std::string bId = b.itemData.id;

	return aId < bId;
}

class InventorySystem
{
private:
	std::vector<FInventorySlot> items;
	int inventorySize;
	int inventoryCount;

private:
	InventorySystem() : inventorySize(20), inventoryCount(0) {}

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

	void ShowInventoryInNormal(); // Player 인자 넣기
	void ShowInventoryInShop(float buybackRatem, int& totalBuyPrice);
	void ExpandInventory(int size);

public:
	void ClearScreen() const;
	void PrintInventoryItems(EInventoryViewMode mode, float buybackRate = 1) const;
	void HandleNormalInventoryOptions(bool& isEnd);
	void HandleShopInventoryOptions(float buybackRate, int& totalBuyPrice, bool& isEnd);
	void HandleNormalItemSelection();
	void PrintItemInfo(int index) const;
	void HandleNormalItemOptions(int index);
	void HandleNormalUsableItemOptions(int index);
	void HandleNormalNonUsableItemOptions(int index);
	void HandleShopItemOptions(int index, float buybackRate, int& totalBuyPrice);
	void HandleDiscardItem(int index);

	bool AddItem(std::string id, int itemCount = 1);
	bool RemoveItem(int index, int itemCount = 1);
	int FindItem(std::string id) const; // -1: fail, 0~: index(동일한 아이템 존재 시 아이템 가장 적게 들어있는 슬롯)
	int GetTotalItemCount(int index) const;
	bool UseItem(int index); // Player 인자 넣기

	void SortByName();
	void SortByPrice();
	void SortByFunc();
	void MergeSameItems();
};