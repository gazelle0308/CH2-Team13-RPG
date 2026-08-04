  // Copyright 2026 ShinStella

#pragma once

#include <string>

#include "Item/Item.h"

class MaterialItem :
    public Item {
 private:
    FMaterialItemData materialItemData;

 public:
    explicit MaterialItem(std::string id)
        : Item(id) {
        SetMaterialData(id);
    }

    void Use() override;

 private:
    void PrintUseMessage() const override;
    void SetMaterialData(std::string id);

 public:
    const FMaterialItemData& GetMaterialData() const;
    EMaterialType GetMaterialType() const;
};

