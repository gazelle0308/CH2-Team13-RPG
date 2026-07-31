#include "Item/UpgradeItem.h"

void UpgradeItem::Use()
{
	PrintUseMessage();

	switch (upgradeItemData.upgradeType)
	{
	case EUpgradeType::Inventory:
		// 인벤토리 확장
		break;
	}
}

void UpgradeItem::PrintUseMessage() const
{
	Item::PrintUseMessage();

	FEnumDisplay enumDisplay;
	std::string displayName = enumDisplay.GetUpgradeTypeDisplayName(upgradeItemData.upgradeType);
	std::string message = std::format("{}이(가) {} 증가했습니다.", displayName, upgradeItemData.value);

	// AddLog(message);
}

void UpgradeItem::SetUpgradeData(std::string id)
{
	ItemDataBase itemDataBase;
	upgradeItemData = itemDataBase.GetUpgradeData(id);
}

const FUpgradeItemData& UpgradeItem::GetUpgradeData() const
{
	return upgradeItemData;
}

const EUpgradeType UpgradeItem::GetUpgradeType() const
{
	return upgradeItemData.upgradeType;
}

const int UpgradeItem::GetValue() const
{
	return upgradeItemData.value;
}