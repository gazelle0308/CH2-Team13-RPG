#pragma once
#include "Item/Item.h"

class InventorySystem;

class UpgradeItem :
    public Item
{
private:
    FUpgradeItemData upgradeItemData;

public:
    UpgradeItem(std::string id)
        : Item(id) {
        SetUpgradeData(id);
    }

    virtual void Use() override;

private:
    virtual void PrintUseMessage() const override;
    void SetUpgradeData(std::string id);

public:
    const FUpgradeItemData& GetUpgradeData() const;
    EUpgradeType GetUpgradeType() const;
    int GetValue() const;
};

