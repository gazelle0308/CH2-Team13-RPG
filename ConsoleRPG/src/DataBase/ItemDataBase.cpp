#include "DataBase/ItemDataBase.h"

void ItemDataBase::LoadItemData()
{
	FEnumDisplay enumDisplay;

	std::ifstream file("data/items.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패" << std::endl;
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
		std::cout << "파일 열기 실패" << std::endl;
		return;
	}

	nlohmann::json data;
	file >> data;

	for (const auto& item : data)
	{
		FConsumableItemData consumableData;

		consumableData.id = item["id"];

		for (const auto& effect : item["effects"])
		{
			FConsumableEffect consumableEffect;

			consumableEffect.consumableType = enumDisplay.GetConsumableTypeToEnum(effect["consumableType"]);
			consumableEffect.value = effect["value"];

			consumableData.effects.push_back(consumableEffect);
		}

		consumableDataMap.emplace(consumableData.id, consumableData);
	}
}

void ItemDataBase::LoadUpgradeData()
{
	FEnumDisplay enumDisplay;

	std::ifstream file("data/upgrades.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패" << std::endl;
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
		std::cout << "파일 열기 실패" << std::endl;
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

void ItemDataBase::PrintAllItemData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FItemData>::const_iterator iter = itemDataMap.begin(); iter != itemDataMap.end(); iter++)
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

void ItemDataBase::PrintAllConsumableData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FConsumableItemData>::const_iterator iter = consumableDataMap.begin(); iter != consumableDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.id) << std::endl;

		for (const FConsumableEffect& effect : iter->second.effects)
		{
			std::cout << std::format("consumableType: {}, value: {}", enumDisplay.GetConsumableTypeToString(effect.consumableType), effect.value) << std::endl;
		}
	}
}

void ItemDataBase::PrintAllUpgradeData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FUpgradeItemData>::const_iterator iter = upgradeDataMap.begin(); iter != upgradeDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.id) << std::endl;
		std::cout << std::format("upgradeType: {}", enumDisplay.GetUpgradeTypeToString(iter->second.upgradeType)) << std::endl;
		std::cout << std::format("value: {}", iter->second.value) << std::endl;
	}
}

void ItemDataBase::PrintAllMaterialData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FMaterialItemData>::const_iterator iter = materialDataMap.begin(); iter != materialDataMap.end(); iter++)
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
	if (!itemDataMap.contains(id))
	{
		return FItemData();
	}

	return itemDataMap.at(id);
}

const EItemCategory ItemDataBase::GetCategory(std::string id) const
{
	if (!itemDataMap.contains(id))
	{
		return EItemCategory::None;
	}

	return itemDataMap.at(id).category;
}

const std::string ItemDataBase::GetName(std::string id) const
{
	if (!itemDataMap.contains(id))
	{
		return std::string();
	}

	return itemDataMap.at(id).name;
}

const std::string ItemDataBase::GetDescription(std::string id) const
{
	if (!itemDataMap.contains(id))
	{
		return std::string();
	}

	return itemDataMap.at(id).description;
}

const int ItemDataBase::GetPrice(std::string id) const
{
	if (!itemDataMap.contains(id))
	{
		return int();
	}

	return itemDataMap.at(id).price;
}

const int ItemDataBase::GetMaxStackCount(std::string id) const
{
	if (!itemDataMap.contains(id))
	{
		return int();
	}

	return itemDataMap.at(id).maxStackCount;
}

const FConsumableItemData& ItemDataBase::GetConsumableData(std::string id) const
{
	if (!consumableDataMap.contains(id))
	{
		return FConsumableItemData();
	}

	return consumableDataMap.at(id);
}

const std::vector<FConsumableEffect>& ItemDataBase::GetConsumableEffects(std::string id) const
{
	if (!consumableDataMap.contains(id))
	{
		return std::vector<FConsumableEffect>();
	}

	return consumableDataMap.at(id).effects;
}

const std::vector<EConsumableType>& ItemDataBase::GetConsumableTypes(std::string id) const
{
	if (!consumableDataMap.contains(id))
	{
		return std::vector<EConsumableType>();
	}

	std::vector<EConsumableType> consumableTypes{};
	FConsumableItemData consumableItemData = consumableDataMap.at(id);

	for (const FConsumableEffect& effect : consumableItemData.effects)
	{
		consumableTypes.push_back(effect.consumableType);
	}

	return consumableTypes;
}

const FUpgradeItemData& ItemDataBase::GetUpgradeData(std::string id) const
{
	if (!upgradeDataMap.contains(id))
	{
		return FUpgradeItemData();
	}

	return upgradeDataMap.at(id);
}

const EUpgradeType ItemDataBase::GetUpgradeType(std::string id) const
{
	if (!upgradeDataMap.contains(id))
	{
		return EUpgradeType::None;
	}

	return upgradeDataMap.at(id).upgradeType;
}

const int ItemDataBase::GetUpgradeValue(std::string id) const
{
	if (!upgradeDataMap.contains(id))
	{
		return int();
	}

	return upgradeDataMap.at(id).value;
}

const FMaterialItemData& ItemDataBase::GetMaterialData(std::string id) const
{
	if (!materialDataMap.contains(id))
	{
		return FMaterialItemData();
	}

	return materialDataMap.at(id);
}

const EMaterialType ItemDataBase::GetMaterialType(std::string id) const
{
	if (!materialDataMap.contains(id))
	{
		return EMaterialType::None;
	}

	return materialDataMap.at(id).materialType;
}
