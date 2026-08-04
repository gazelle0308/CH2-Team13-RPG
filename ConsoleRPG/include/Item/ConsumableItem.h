#pragma once
#include <vector>
#include "Item/Item.h"
#include "Player/player.h"

class ConsumableItem :
    public Item
{
private:
    FConsumableItemData consumableItemData;

public:
    ConsumableItem(std::string id)
        : Item(id) {
        SetConsumableData(id);
    }

    virtual void Use() override;

private:
    virtual void PrintUseMessage() const override;
    void SetConsumableData(std::string id);

public:
    const FConsumableItemData& GetConsumableData() const;
    const std::vector<FConsumableEffect>& GetConsumableEffects() const;
    const std::vector<EConsumableType>& GetConsumableTypes() const;
};

