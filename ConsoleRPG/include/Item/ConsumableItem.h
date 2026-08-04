  // Copyright 2026 ShinStella

#pragma once

#include <string>
#include <vector>

#include "Item/Item.h"
#include "Player/player.h"
#include "Effect/Effect.h"

class ConsumableItem :
    public Item {
 private:
    FConsumableItemData consumableItemData;

 public:
    explicit ConsumableItem(std::string id)
        : Item(id) {
        SetConsumableData(id);
    }

    void Use() override;

 private:
    void PrintUseMessage() const override;
    void SetConsumableData(std::string id);

 public:
    const FConsumableItemData& GetConsumableData() const;
    const std::vector<FConsumableEffect>& GetConsumableEffects() const;
    const std::vector<EConsumableType>& GetConsumableTypes() const;
};

