  // Copyright 2026 ShinStella

#include <string>

#include "Item/UpgradeItem.h"
#include "InventorySystem/InventorySystem.h"
#include "GameLog/GameLog.h"

void UpgradeItem::Use() {
    // PrintUseMessage();

    switch (upgradeItemData.GetUpgradeType()) {
    case EUpgradeType::Inventory:
    {
        InventorySystem::GetInstance().
            ExpandInventory(upgradeItemData.GetValue());
        break;
    }
    }
}

void UpgradeItem::PrintUseMessage() const {
    Item::PrintUseMessage();

    FEnumDisplay enumDisplay;
    std::string displayName =
        enumDisplay.GetUpgradeTypeDisplayName(upgradeItemData.GetUpgradeType());
    GameLog::GetInstance().itemLog(itemData.GetName(), "증가했습니다.");
}

void UpgradeItem::SetUpgradeData(std::string id) {
    ItemDataBase::GetInstance().GetUpgradeData(id, upgradeItemData);
}

const FUpgradeItemData& UpgradeItem::GetUpgradeData() const {
    return upgradeItemData;
}

EUpgradeType UpgradeItem::GetUpgradeType() const {
    return upgradeItemData.GetUpgradeType();
}

int UpgradeItem::GetValue() const {
    return upgradeItemData.GetValue();
}
