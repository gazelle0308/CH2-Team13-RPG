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

	bool GetItemData(std::string id, FItemData& itemData) const;
	bool GetCategory(std::string id, EItemCategory& category) const;
	bool GetName(std::string id, std::string& name) const;
	bool GetDescription(std::string id, std::string& description) const;
	bool GetPrice(std::string id, int& price) const;
	bool GetMaxStackCount(std::string id, int& maxStackCount) const;

	bool GetConsumableData(std::string id, FConsumableItemData& consumableItemData) const;
	bool GetConsumableEffects(std::string id, std::vector<FConsumableEffect>& consumbaleEffects) const;
	bool GetConsumableTypes(std::string id, std::vector<EConsumableType>& consumableTypes) const;

	bool GetUpgradeData(std::string id, FUpgradeItemData& upgradeItemData) const;
	bool GetUpgradeType(std::string id, EUpgradeType& upgradeType) const;
	bool GetUpgradeValue(std::string id, int& value) const;

	bool GetMaterialData(std::string id, FMaterialItemData& materialItemData) const;
	bool GetMaterialType(std::string id, EMaterialType& materialType) const;
};

