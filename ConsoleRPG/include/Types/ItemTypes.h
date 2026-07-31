#pragma once

#include <string>
#include <unordered_map>

enum class EItemCategory
{
	None,
	Consumable, // 소비 아이템
	Upgrade, // 인벤토리 업그레이드
	Material, // 몬스터 드랍 아이템
};

enum class EConsumableType
{
	None,
	Hp,
	Mp,
	Power,
	Defence,
};

enum class EUpgradeType
{
	None,
	Inventory,
};

enum class EMaterialType
{
	None,
	Primary,
	Secondary,
};

// ==========================================================================================//

struct FItemData
{
	std::string id = "ITEM";
	EItemCategory category = EItemCategory::None;
	std::string name = "item";
	std::string description = "description";
	int price = 0;
	int maxStackCount = 0;
};

struct FConsumableItemData
{
	std::string id = "ITEM";
	EConsumableType consumableType = EConsumableType::None;
	int value = 0;
};

struct FUpgradeItemData
{
	std::string id = "ITEM";
	EUpgradeType upgradeType = EUpgradeType::None;
	int value = 0;
};

struct FMaterialItemData
{
	std::string id = "ITEM";
	EMaterialType materialType = EMaterialType::None;
};

// ==========================================================================================//

struct FEnumDisplay
{
private:
	std::unordered_map<EItemCategory, std::string> itemCategoryToStringMap =
	{
		{EItemCategory::None, "None"},
		{EItemCategory::Consumable, "Consumable"},
		{EItemCategory::Upgrade, "Upgrade"},
		{EItemCategory::Material, "Material"},
	};
	std::unordered_map<std::string, EItemCategory> itemCategoryToEnumMap =
	{
		{"None", EItemCategory::None},
		{"Consumable", EItemCategory::Consumable},
		{"Upgrade", EItemCategory::Upgrade},
		{"Material", EItemCategory::Material},
	};
	std::unordered_map<EItemCategory, std::string> itemCategoryDisplayNameMap =
	{
		{EItemCategory::None, "???"},
		{EItemCategory::Consumable, "소비"},
		{EItemCategory::Upgrade, "강화"},
		{EItemCategory::Material, "기타"},
	};
	std::unordered_map<EConsumableType, std::string> consumableToStringMap =
	{ 
		{EConsumableType::None, "None"},
		{EConsumableType::Hp, "Hp"},
		{EConsumableType::Mp, "Mp"},
		{EConsumableType::Power, "Power"},
		{EConsumableType::Defence, "Defence"}
	};
	std::unordered_map<std::string, EConsumableType> consumableToEnumMap =
	{ 
		{"None", EConsumableType::None},
		{"Hp", EConsumableType::Hp},
		{"Mp", EConsumableType::Mp},
		{"Power", EConsumableType::Power},
		{"Defence", EConsumableType::Defence}
	};
	std::unordered_map<EConsumableType, std::string> consumableDisplayNameMap =
	{
		{EConsumableType::None, "???"},
		{EConsumableType::Hp, "체력"},
		{EConsumableType::Mp, "마력"},
		{EConsumableType::Power, "공격력"},
		{EConsumableType::Defence, "방어력"}
	};
	std::unordered_map<EUpgradeType, std::string> upgradeToStringMap =
	{
		{EUpgradeType::None, "None"},
		{EUpgradeType::Inventory, "Inventory"}
	};
	std::unordered_map<std::string, EUpgradeType> upgradeToEnumMap =
	{
		{"None", EUpgradeType::None},
		{"Inventory", EUpgradeType::Inventory}
	};
	std::unordered_map<EUpgradeType, std::string> upgradeDisplayNameMap =
	{
		{EUpgradeType::None, "???"},
		{EUpgradeType::Inventory, "인벤토리"}
	};
	std::unordered_map<EMaterialType, std::string> materialToStringMap =
	{
		{EMaterialType::None, "None"},
		{EMaterialType::Primary, "Primary"},
		{EMaterialType::Secondary, "Secondary"}
	};
	std::unordered_map<std::string, EMaterialType> materialToEnumMap =
	{
		{"None", EMaterialType::None},
		{"Primary", EMaterialType::Primary},
		{"Secondary", EMaterialType::Secondary}
	};
	std::unordered_map<EMaterialType, std::string> materialDisplayNameMap =
	{
		{EMaterialType::None, "???"},
		{EMaterialType::Primary, "원재료"},
		{EMaterialType::Secondary, "부재료"}
	};

public:
	inline std::string GetItemCategoryToString(EItemCategory itemCategory)
	{
		return itemCategoryToStringMap[itemCategory];
	}
	inline EItemCategory GetItemCategoryToEnum(std::string str)
	{
		return itemCategoryToEnumMap[str];
	}
	inline std::string GetItemCategoryDisplayName(EItemCategory itemCategory)
	{
		return itemCategoryDisplayNameMap[itemCategory];
	}
	inline std::string GetConsumableTypeToString(EConsumableType consumableType)
	{
		return consumableToStringMap[consumableType];
	}
	inline EConsumableType GetConsumableTypeToEnum(std::string str)
	{
		return consumableToEnumMap[str];
	}
	inline std::string GetConsumableTypeDisplayName(EConsumableType ConsumableType)
	{
		return consumableDisplayNameMap[ConsumableType];
	}
	inline std::string GetUpgradeTypeToString(EUpgradeType upgradeType)
	{
		return upgradeToStringMap[upgradeType];
	}
	inline EUpgradeType GetUpgradeTypeToEnum(std::string str)
	{
		return upgradeToEnumMap[str];
	}
	inline std::string GetUpgradeTypeDisplayName(EUpgradeType upgradeType)
	{
		return upgradeDisplayNameMap[upgradeType];
	}
	inline std::string GetMaterialTypeToString(EMaterialType materialType)
	{
		return materialToStringMap[materialType];
	}
	inline EMaterialType GetMaterialTypeToEnum(std::string str)
	{
		return materialToEnumMap[str];
	}
	inline std::string GetMaterialTypeDisplayName(EMaterialType materialType)
	{
		return materialDisplayNameMap[materialType];
	}
};