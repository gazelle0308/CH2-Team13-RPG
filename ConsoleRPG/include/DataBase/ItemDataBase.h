#pragma once
#include <iostream>
#include <fstream>
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

public:
	void LoadItemData();
	void LoadConsumableData();
	void LoadUpgradeData();
	void LoadMaterialData();

	void PrintAllItemData();
	void PrintAllConsumableData();
	void PrintAllUpgradeData();
	void PrintAllMaterialData();

	const FItemData& GetItemData(std::string id) const;
	const EItemCategory GetCategory(std::string id) const;
	const std::string GetName(std::string id) const;
	const std::string GetDescription(std::string id) const;
	const int GetPrice(std::string id) const;
	const int GetMaxStackCount(std::string id) const;

	const FConsumableItemData& GetConsumableData(std::string id) const;
	const EConsumableType GetConsumableType(std::string id) const;
	const int GetConsumableValue(std::string id) const;

	const FUpgradeItemData& GetUpgradeData(std::string id) const;
	const EUpgradeType GetUpgradeType(std::string id) const;
	const int GetUpgradeValue(std::string id) const;

	const FMaterialItemData& GetMaterialData(std::string id) const;
	const EMaterialType GetMaterialType(std::string id) const;
};

