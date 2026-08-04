  // Copyright 2026 ShinStella

#pragma once

#include <string>

#include "Item/Item.h"

class InventorySystem;

class UpgradeItem :
    public Item {
 private:
    FUpgradeItemData upgradeItemData;

 public:
    explicit UpgradeItem(std::string id)
        : Item(id) {
        SetUpgradeData(id);
    }

    void Use() override;

 private:
    void PrintUseMessage() const override;
    void SetUpgradeData(std::string id);

 public:
    const FUpgradeItemData& GetUpgradeData() const;
    EUpgradeType GetUpgradeType() const;
    int GetValue() const;
};

