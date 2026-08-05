  // Copyright 2026 ShinStella

#pragma once

#include <string>

#include "Types/ItemTypes.h"

// 상점 초기 데이터
struct FShopItemData {
 public:
    std::string id = "ID";
    bool defaultUnlocked = false;
    bool hasStockLimit = false;
    int initialCount = 0;

 public:
    void SetId(std::string id_) {
        id = id_;
    }
    void SetDefaultUnlocked(bool defaultUnlocked_) {
        defaultUnlocked = defaultUnlocked_;
    }
    void SetHasStockLimit(bool hasStockLimit_) {
        hasStockLimit = hasStockLimit_;
    }
    void SetInitialCount(int intitialCount_) {
        initialCount = intitialCount_;
    }

    std::string GetId() const {
        return id;
    }
    bool GetDefaultUnlocked() const {
        return defaultUnlocked;
    }
    bool GetHasStockLimit() const {
        return hasStockLimit;
    }
    int GetInitialCount() const {
        return initialCount;
    }
};

// 상점 런타임 데이터
struct FShopSlot {
 public:
    FItemData itemData;
    bool isUnlocked = false;
    bool hasStockLimit = false;
    int currentCount = 0;

 public:
    void SetItemData(const FItemData& itemData_) {
        itemData = itemData_;
    }
    void SetIsUnlocked(bool isUnlocked_) {
        isUnlocked = isUnlocked_;
    }
    void SetHasStockLimit(bool hasStockLimit_) {
        hasStockLimit = hasStockLimit_;
    }
    void SetCurrentCount(int currentCount_) {
        currentCount = currentCount_;
    }

    const FItemData& GetItemData() const {
        return itemData;
    }
    bool GetIsUnlocked() const {
        return isUnlocked;
    }
    bool GetHasStockLimit() const {
        return hasStockLimit;
    }
    int GetCurrentCount() const {
        return currentCount;
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
