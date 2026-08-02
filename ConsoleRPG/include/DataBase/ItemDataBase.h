#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Types/ItemTypes.h"

class ItemDataBase
{
private:
	std::unordered_map<std::string, FItemData> itemDataMap;
	std::unordered_map<std::string, FConsumableItemData> consumableDataMap;
	std::unordered_map<std::string, FUpgradeItemData> upgradeDataMap;
	std::unordered_map<std::string, FMaterialItemData> materialDataMap;

private:
	ItemDataBase() {
		LoadItemData();
		LoadConsumableData();
		LoadUpgradeData();
		LoadMaterialData();
	}

	// 복사 방지
	ItemDataBase(const ItemDataBase&) = delete;
	ItemDataBase& operator=(const ItemDataBase&) = delete;

	// 이동 방지
	ItemDataBase(ItemDataBase&&) = delete;
	ItemDataBase& operator=(ItemDataBase&&) = delete;

	void LoadItemData();
	void LoadConsumableData();
	void LoadUpgradeData();
	void LoadMaterialData();

public:
	// 싱글톤
	static ItemDataBase& GetInstance() {
		static ItemDataBase instance;
		return instance;
	}

	// 테스트용
	void PrintAllItemData() const;
	void PrintAllConsumableData() const;
	void PrintAllUpgradeData() const;
	void PrintAllMaterialData() const;

public:
	const std::vector<std::string> GetAllItemIds() const;

	const FItemData& GetItemData(std::string id) const;
	const EItemCategory GetCategory(std::string id) const;
	const std::string GetName(std::string id) const;
	const std::string GetDescription(std::string id) const;
	const int GetPrice(std::string id) const;
	const int GetMaxStackCount(std::string id) const;

	const FConsumableItemData& GetConsumableData(std::string id) const;
	const std::vector<FConsumableEffect>& GetConsumableEffects(std::string id) const;
	const std::vector<EConsumableType>& GetConsumableTypes(std::string id) const;

	const FUpgradeItemData& GetUpgradeData(std::string id) const;
	const EUpgradeType GetUpgradeType(std::string id) const;
	const int GetUpgradeValue(std::string id) const;

	const FMaterialItemData& GetMaterialData(std::string id) const;
	const EMaterialType GetMaterialType(std::string id) const;
};

