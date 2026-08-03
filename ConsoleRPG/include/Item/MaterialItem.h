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

    virtual void Use() override;

private:
    virtual void PrintUseMessage() const override;
    void SetMaterialData(std::string id);

public:
    const FMaterialItemData& GetMaterialData() const;
    EMaterialType GetMaterialType() const;
};

