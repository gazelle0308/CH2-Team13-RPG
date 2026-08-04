#include "Item/UpgradeItem.h"
#include "InventorySystem/InventorySystem.h"

void UpgradeItem::Use()
{
	PrintUseMessage();

	switch (upgradeItemData.GetUpgradeType())
	{
	case EUpgradeType::Inventory:
		InventorySystem::GetInstance().ExpandInventory(upgradeItemData.GetValue());
		break;
	}
}

void UpgradeItem::PrintUseMessage() const
{
	Item::PrintUseMessage();

	FEnumDisplay enumDisplay;
	std::string displayName = enumDisplay.GetUpgradeTypeDisplayName(upgradeItemData.GetUpgradeType());
	std::string message = std::format("{}이(가) {} 증가했습니다.", displayName, upgradeItemData.GetValue());

	// AddLog(message);
}

void UpgradeItem::SetUpgradeData(std::string id)
{
	ItemDataBase::GetInstance().GetUpgradeData(id, upgradeItemData);
}

const FUpgradeItemData& UpgradeItem::GetUpgradeData() const
{
	return upgradeItemData;
}

EUpgradeType UpgradeItem::GetUpgradeType() const
{
	return upgradeItemData.GetUpgradeType();
}

int UpgradeItem::GetValue() const
{
	return upgradeItemData.GetValue();
}