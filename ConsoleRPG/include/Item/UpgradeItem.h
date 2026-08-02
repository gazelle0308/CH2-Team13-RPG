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

    virtual void Use() override; // Player 인자 넣기

private:
    virtual void PrintUseMessage() const override;
    void SetUpgradeData(std::string id);

public:
    const FUpgradeItemData& GetUpgradeData() const;
    const EUpgradeType GetUpgradeType() const;
    const int GetValue() const;
};

