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

		if (!enumDisplay.GetItemCategoryToEnum(item["category"], itemData.category))
		{
			return;
		}

		itemData.SetId(item["id"]);
		itemData.SetName(item["name"]);
		itemData.SetDescription(item["description"]);
		itemData.SetPrice(item["price"]);
		itemData.SetMaxStackCount(item["maxStackCount"]);

		itemDataMap.emplace(itemData.GetId(), itemData);
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

			if (!enumDisplay.GetConsumableTypeToEnum(effect["consumableType"], consumableEffect.consumableType))
			{
				return;
			}

			consumableEffect.SetValue(effect["value"]);

			consumableData.effects.push_back(consumableEffect);
		}

		consumableDataMap.emplace(consumableData.GetId(), consumableData);
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

		if (!enumDisplay.GetUpgradeTypeToEnum(item["upgradeType"], upgradeItemData.upgradeType))
		{
			return;
		}

		upgradeItemData.SetId(item["id"]);
		upgradeItemData.SetValue(item["value"]);

		upgradeDataMap.emplace(upgradeItemData.GetId(), upgradeItemData);
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

		if (!enumDisplay.GetMaterialTypeToEnum(item["materialType"], materialItemData.materialType))
		{
			return;
		}

		materialItemData.SetId(item["id"]);

		materialDataMap.emplace(materialItemData.GetId(), materialItemData);
	}
}

void ItemDataBase::PrintAllItemData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FItemData>::const_iterator iter = itemDataMap.begin(); iter != itemDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.GetId()) << std::endl;
		std::cout << std::format("category: {}", enumDisplay.GetItemCategoryToString(iter->second.GetCategory())) << std::endl;
		std::cout << std::format("description: {}", iter->second.GetDescription()) << std::endl;
		std::cout << std::format("name: {}", iter->second.GetName()) << std::endl;
		std::cout << std::format("price: {}", iter->second.GetPrice()) << std::endl;
		std::cout << std::format("maxStackCount: {}", iter->second.GetMaxStackCount()) << std::endl;
	}
}

void ItemDataBase::PrintAllConsumableData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FConsumableItemData>::const_iterator iter = consumableDataMap.begin(); iter != consumableDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.GetId()) << std::endl;

		for (const FConsumableEffect& effect : iter->second.GetConsumableEffects())
		{
			std::cout << std::format("consumableType: {}, value: {}", enumDisplay.GetConsumableTypeToString(effect.GetConsumableType()), effect.GetValue()) << std::endl;
		}
	}
}

void ItemDataBase::PrintAllUpgradeData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FUpgradeItemData>::const_iterator iter = upgradeDataMap.begin(); iter != upgradeDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.GetId()) << std::endl;
		std::cout << std::format("upgradeType: {}", enumDisplay.GetUpgradeTypeToString(iter->second.GetUpgradeType())) << std::endl;
		std::cout << std::format("value: {}", iter->second.GetValue()) << std::endl;
	}
}

void ItemDataBase::PrintAllMaterialData() const
{
	FEnumDisplay enumDisplay;

	for (std::unordered_map<std::string, FMaterialItemData>::const_iterator iter = materialDataMap.begin(); iter != materialDataMap.end(); iter++)
	{
		std::cout << std::format("ID: {}", iter->first) << std::endl;
		std::cout << std::format("id: {}", iter->second.GetId()) << std::endl;
		std::cout << std::format("materialType: {}", enumDisplay.GetMaterialTypeToString(iter->second.GetMaterialType())) << std::endl;
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

bool ItemDataBase::GetItemData(std::string id, FItemData& itemData) const
{
	if (!itemDataMap.contains(id))
	{
		return false;
	}

	itemData = itemDataMap.at(id);

	return true;
}

bool ItemDataBase::GetCategory(std::string id, EItemCategory& category) const
{
	if (!itemDataMap.contains(id))
	{
		return false;
	}

	category = itemDataMap.at(id).GetCategory();

	return true;
}

bool ItemDataBase::GetName(std::string id, std::string& name) const
{
	if (!itemDataMap.contains(id))
	{
		return false;
	}

	name = itemDataMap.at(id).GetName();

	return true;
}

bool ItemDataBase::GetDescription(std::string id, std::string& description) const
{
	if (!itemDataMap.contains(id))
	{
		return false;
	}

	description = itemDataMap.at(id).GetDescription();
	
	return true;
}

bool ItemDataBase::GetPrice(std::string id, int& price) const
{
	if (!itemDataMap.contains(id))
	{
		return false;
	}

	price = itemDataMap.at(id).GetPrice();
	
	return true;
}

bool ItemDataBase::GetMaxStackCount(std::string id, int& maxStackCount) const
{
	if (!itemDataMap.contains(id))
	{
		return false;
	}

	maxStackCount = itemDataMap.at(id).GetMaxStackCount();
	
	return true;
}

bool ItemDataBase::GetConsumableData(std::string id, FConsumableItemData& consumableItemData) const
{
	if (!consumableDataMap.contains(id))
	{
		return false;
	}

	consumableItemData = consumableDataMap.at(id);
	
	return true;
}

bool ItemDataBase::GetConsumableEffects(std::string id, std::vector<FConsumableEffect>& consumbaleEffects) const
{
	if (!consumableDataMap.contains(id))
	{
		return false;
	}

	consumbaleEffects = consumableDataMap.at(id).GetConsumableEffects();
	
	return true;
}

bool ItemDataBase::GetConsumableTypes(std::string id, std::vector<EConsumableType>& consumableTypes) const
{
	if (!consumableDataMap.contains(id))
	{
		return false;
	}

	std::vector<EConsumableType> types{};
	FConsumableItemData consumableItemData = consumableDataMap.at(id);

	for (const FConsumableEffect& effect : consumableItemData.GetConsumableEffects())
	{
		types.push_back(effect.GetConsumableType());
	}

	consumableTypes = types;

	return true;
}

bool ItemDataBase::GetUpgradeData(std::string id, FUpgradeItemData& upgradeItemData) const
{
	if (!upgradeDataMap.contains(id))
	{
		return false;
	}

	upgradeItemData = upgradeDataMap.at(id);
	
	return true;
}

bool ItemDataBase::GetUpgradeType(std::string id, EUpgradeType& upgradeType) const
{
	if (!upgradeDataMap.contains(id))
	{
		return false;
	}

	upgradeType = upgradeDataMap.at(id).GetUpgradeType();
	
	return true;
}

bool ItemDataBase::GetUpgradeValue(std::string id, int& value) const
{
	if (!upgradeDataMap.contains(id))
	{
		return false;
	}

	value = upgradeDataMap.at(id).GetValue();

	return true;
}

bool ItemDataBase::GetMaterialData(std::string id, FMaterialItemData& materialItemData) const
{
	if (!materialDataMap.contains(id))
	{
		return false;
	}

	materialItemData = materialDataMap.at(id);
	
	return true;
}

bool ItemDataBase::GetMaterialType(std::string id, EMaterialType& materialType) const
{
	if (!materialDataMap.contains(id))
	{
		return false;
	}

	materialType = materialDataMap.at(id).GetMaterialType();
	
	return true;
}
