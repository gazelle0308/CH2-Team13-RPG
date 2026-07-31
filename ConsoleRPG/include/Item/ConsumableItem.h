#pragma once
#include "Item/Item.h"

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

    virtual void Use() override; // Player 인자 넣기
    virtual void PrintUseMessage() const override;
        
    void SetConsumableData(std::string id);

    const FConsumableItemData& GetConsumableData() const;
    const EConsumableType GetConsumableType() const;
    const int GetValue() const;
};

