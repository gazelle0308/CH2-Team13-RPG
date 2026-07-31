#include "DataBase/ItemDataBase.h"

void ItemDataBase::LoadItemData()
{
	FEnumDisplay enumDisplay;

	std::ifstream file("data/items.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패\n";
		return;
	}

	nlohmann::json data;
	file >> data;

	for (const auto& item : data)
	{
		FItemData itemData;

		itemData.id = item["id"];
		itemData.category = enumDisplay.GetItemCategoryToEnum(item["category"]);
		itemData.name = item["name"];
		itemData.description = item["description"];
		itemData.price = item["price"];
		itemData.maxStackCount = item["maxStackCount"];

		itemDataMap.emplace(itemData.id, itemData);
	}
}

void ItemDataBase::LoadConsumableData()
{
	FEnumDisplay enumDisplay;

	std::ifstream file("data/consumables.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패\n";
		return;
	}

	nlohmann::json data;
	file >> data;

	for (const auto& item : data)
	{
		FConsumableItemData consumableData;

		consumableData.id = item["id"];
		consumableData.consumableType = enumDisplay.GetConsumableTypeToEnum(item["consumableType"]);
		consumableData.value = item["value"];

		consumableDataMap.emplace(consumableData.id, consumableData);
	}
}

void ItemDataBase::LoadUpgradeData()
{
	FEnumDisplay enumDisplay;

	std::ifstream file("data/upgrades.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패\n";
		return;
	}

	nlohmann::json data;
	file >> data;

	for (const auto& item : data)
	{
		FUpgradeItemData upgradeItemData;

		upgradeItemData.id = item["id"];
		upgradeItemData.upgradeType = enumDisplay.GetUpgradeTypeToEnum(item["upgradeType"]);
		upgradeItemData.value = item["value"];

		upgradeDataMap.emplace(upgradeItemData.id, upgradeItemData);
	}
}

void ItemDataBase::LoadMaterialData()
{
	FEnumDisplay enumDisplay;

	std::ifstream file("data/materials.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패\n";
		return;
	}

	nlohmann::json data;
	file >> data;

	for (const auto& item : data)
	{
		FMaterialItemData materialItemData;

		materialItemData.id = item["id"];
		materialItemData.materialType = enumDisplay.GetMaterialTypeToEnum(item["materialType"]);

		materialDataMap.emplace(materialItemData.id, materialItemData);
	}
}

void ItemDataBase::PrintAllItemData()
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FItemData>::iterator iter = itemDataMap.begin(); iter != itemDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.id) << std::endl;
		std::cout << std::format("category: {}", enumDisplay.GetItemCategoryToString(iter->second.category)) << std::endl;
		std::cout << std::format("description: {}", iter->second.description) << std::endl;
		std::cout << std::format("name: {}", iter->second.name) << std::endl;
		std::cout << std::format("price: {}", iter->second.price) << std::endl;
		std::cout << std::format("maxStackCount: {}", iter->second.maxStackCount) << std::endl;
	}
}

void ItemDataBase::PrintAllConsumableData()
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FConsumableItemData>::iterator iter = consumableDataMap.begin(); iter != consumableDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.id) << std::endl;
		std::cout << std::format("consumableType: {}", enumDisplay.GetConsumableTypeToString(iter->second.consumableType)) << std::endl;
		std::cout << std::format("value: {}", iter->second.value) << std::endl;
	}
}

void ItemDataBase::PrintAllUpgradeData()
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FUpgradeItemData>::iterator iter = upgradeDataMap.begin(); iter != upgradeDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.id) << std::endl;
		std::cout << std::format("upgradeType: {}", enumDisplay.GetUpgradeTypeToString(iter->second.upgradeType)) << std::endl;
		std::cout << std::format("value: {}", iter->second.value) << std::endl;
	}
}

void ItemDataBase::PrintAllMaterialData()
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FMaterialItemData>::iterator iter = materialDataMap.begin(); iter != materialDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.id) << std::endl;
		std::cout << std::format("materialType: {}", enumDisplay.GetMaterialTypeToString(iter->second.materialType)) << std::endl;
	}
}

const std::vector<std::string> ItemDataBase::GetAllItemIds() const
{
	std::vector<std::string> ids{};

	for (std::unordered_map<std::string, FItemData>::const_iterator iter = itemDataMap.begin(); iter != itemDataMap.end(); iter++)
	{
		ids.push_back(iter->first);
	}

	return ids;
}

const FItemData& ItemDataBase::GetItemData(std::string id) const
{
	return itemDataMap.at(id);
}

const EItemCategory ItemDataBase::GetCategory(std::string id) const
{
	return itemDataMap.at(id).category;
}

const std::string ItemDataBase::GetName(std::string id) const
{
	return itemDataMap.at(id).name;
}

const std::string ItemDataBase::GetDescription(std::string id) const
{
	return itemDataMap.at(id).description;
}

const int ItemDataBase::GetPrice(std::string id) const
{
	return itemDataMap.at(id).price;
}

const int ItemDataBase::GetMaxStackCount(std::string id) const
{
	return itemDataMap.at(id).maxStackCount;
}

const FConsumableItemData& ItemDataBase::GetConsumableData(std::string id) const
{
	return consumableDataMap.at(id);
}

const EConsumableType ItemDataBase::GetConsumableType(std::string id) const
{
	return consumableDataMap.at(id).consumableType;
}

const int ItemDataBase::GetConsumableValue(std::string id) const
{
	return consumableDataMap.at(id).value;
}

const FUpgradeItemData& ItemDataBase::GetUpgradeData(std::string id) const
{
	return upgradeDataMap.at(id);
}

const EUpgradeType ItemDataBase::GetUpgradeType(std::string id) const
{
	return upgradeDataMap.at(id).upgradeType;
}

const int ItemDataBase::GetUpgradeValue(std::string id) const
{
	return upgradeDataMap.at(id).value;
}

const FMaterialItemData& ItemDataBase::GetMaterialData(std::string id) const
{
	return materialDataMap.at(id);
}

const EMaterialType ItemDataBase::GetMaterialType(std::string id) const
{
	return materialDataMap.at(id).materialType;
}
