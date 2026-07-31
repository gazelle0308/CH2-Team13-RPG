#pragma once
#include "Item/Item.h"

class MaterialItem :
    public Item
{
private:
    FMaterialItemData materialItemData;

public:
    MaterialItem(std::string id)
        : Item(id) {
        SetMaterialData(id);
    }

    virtual void Use() override; // Player 인자 넣기
    virtual void PrintUseMessage() const override;
    
    void SetMaterialData(std::string id);

    const FMaterialItemData& GetMaterialData() const;
    const EMaterialType GetMaterialType() const;
};

