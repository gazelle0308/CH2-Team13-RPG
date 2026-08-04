  // Copyright 2026 ShinStella

#pragma once

#include <iostream>
#include <string>

#include "Types/ItemTypes.h"

enum class EInventoryViewMode {
    Normal,
    Battle,
    Shop,
    PotionWorkshop,
};

struct FInventoryItemData {
 public:
    std::string id = "ID";
    int count = 0;

 public:
    void SetId(std::string id_) {
        id = id_;
    }
    void SetCount(int count_) {
        count = count_;
    }

    std::string GetId() const {
        return id;
    }
    int GetCount() const {
        return count;
    }
};

struct FInventorySlot {
 public:
    FItemData itemData;
    int count = 0;

 public:
    void SetItemData(FItemData itemData_) {
        itemData = itemData_;
    }
    void SetCount(int count_) {
        count = count_;
    }

    const FItemData& GetItemData() const {
        return itemData;
    }
    int GetCount() const {
        return count;
    }
    std::string GetId() const {
        return itemData.GetId();
    }
    EItemCategory GetCategory() const {
        return itemData.GetCategory();
    }
    std::string GetName() const {
        return itemData.GetName();
    }
    std::string GetDescription() const {
        return itemData.GetDescription();
    }
    int GetPrice() const {
        return itemData.GetPrice();
    }
    int GetMaxStackCount() const {
        return itemData.GetMaxStackCount();
    }
};
