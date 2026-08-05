  // Copyright 2026 ShinStella

#pragma once

#include <conio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <format>
#include <utility>

#include "Types/InventoryTypes.h"
#include "DataBase/ItemDataBase.h"
#include "DataBase/InventoryDataBase.h"
#include "Factory/ItemFactory.h"
#include "GameLog/gameLog.h"
#include "Utility/Utility.h"

inline bool compareName(const FInventorySlot& a, const FInventorySlot& b) {
    std::string aName = a.GetName();
    std::string bName = b.GetName();

    if (aName == bName) {
        return a.count > b.count;
    }

    return aName < bName;
}

inline bool compareFunc(const FInventorySlot& a, const FInventorySlot& b) {
    // 기능 별로 순서 정해서 오름차순 정렬

    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    FEnumDisplay enumDisplay;
    EItemCategory aCategory = a.GetCategory();
    EItemCategory bCategory = b.GetCategory();
    int aSequence = static_cast<int>(aCategory);
    int bSequence = static_cast<int>(bCategory);

    if (aCategory == bCategory) {
        std::string aId = a.GetId();
        std::string bId = b.GetId();

        switch (aCategory) {
        case EItemCategory::Consumable:
        {
            std::vector<EConsumableType> aTypes{};
            std::vector<EConsumableType> bTypes{};

            if (itemDataBase.GetConsumableTypes(aId, aTypes) &&
                itemDataBase.GetConsumableTypes(bId, bTypes)) {
                if (!aTypes.empty() && !bTypes.empty()) {
                    aSequence = static_cast<int>(aTypes[0]);
                    bSequence = static_cast<int>(bTypes[0]);
                }
            }

            break;
        }
        case EItemCategory::Upgrade:
        {
            EUpgradeType aUpgradeType{};
            EUpgradeType bUpgradeType{};

            if (itemDataBase.GetUpgradeType(aId, aUpgradeType) &&
                itemDataBase.GetUpgradeType(bId, bUpgradeType)) {
                aSequence = static_cast<int>(aUpgradeType);
                bSequence = static_cast<int>(bUpgradeType);
            }

            break;
        }
        case EItemCategory::Material:
        {
            EMaterialType aMaterialType{};
            EMaterialType bMaterialType{};

            if (itemDataBase.GetMaterialType(aId, aMaterialType) &&
                itemDataBase.GetMaterialType(bId, bMaterialType)) {
                aSequence = static_cast<int>(aMaterialType);
                bSequence = static_cast<int>(bMaterialType);
            }

            break;
        }
        }

        if (aSequence == bSequence) {
            return compareName(a, b);
        }
    }

    return aSequence < bSequence;
}

inline bool comparePrice(const FInventorySlot& a, const FInventorySlot& b) {
    int aPrice = a.GetPrice();
    int bPrice = b.GetPrice();

    if (aPrice == bPrice) {
        return compareFunc(a, b);
    }

    return aPrice < bPrice;
}

class InventorySystem {
 private:
    std::vector<FInventorySlot> items;
    int inventoryMaxSize;

 private:
    InventorySystem() : inventoryMaxSize(20) {
        items.clear();
        SetInventoryData();
    }

    // 복사 방지
    InventorySystem(const InventorySystem&) = delete;
    InventorySystem& operator=(const InventorySystem&) = delete;

    // 이동 방지
    InventorySystem(InventorySystem&&) = delete;
    InventorySystem& operator=(InventorySystem&&) = delete;

 public:
    // 싱글톤
    static InventorySystem& GetInstance() {
        static InventorySystem instance;
        return instance;
    }

    void ShowInventoryInNormal();
    void ShowInventoryInBattle();
    void ShowInventoryInShop(double buybackRate,
                             int& totalBuyPrice,
                             bool& isEnd);
    void ShowInventoryInPotionWorkshop();

    bool AddItem(std::string id, int itemCount = 1);
    void AcquireItem(std::string id, int count, bool showLog);

    // 0: 성공, 1: 공간 부족, 2: 재료 부족, 3: 잘못된 index
    int CanCraftPotion(
        std::vector<std::pair<int, int>>& materials,
        std::string potionId, int potionCount);

    // -1: fail, 0~: index(동일한 아이템 존재 시 아이템 가장 적게 들어있는 슬롯)
    int FindItem(std::string id) const;

    void ExpandInventory(int size);

    int GetTotalItemCount(int index) const;
    bool GetItemData(int index, FItemData& itemData) const;
    std::string GetId(int index) const;

 private:
    void SetInventoryData();

    void ClearScreen() const;

    void PrintInventoryItems(
        EInventoryViewMode mode,
        double buybackRate = 1) const;

    void HandleNormalInventoryOptions(bool& isEnd);
    void HandleBattleInventoryOptions(bool& isEnd);
    void PrintPlayerGold() const;

    void HandleShopInventoryOptions(
        double buybackRate,
        int& totalBuyPrice,
        bool& isEnd);

    void HandleNormalItemSelection();
    void PrintItemInfo(int index) const;
    void HandleNormalItemOptions(int index);
    void HandleNormalUsableItemOptions(int index);
    void HandleNormalNonUsableItemOptions(int index);

    void HandleShopItemOptions(
        int index,
        double buybackRate,
        int& totalBuyPrice);

    bool HandleDiscard();
    void HandleDiscardSelection();
    void HandleDiscardCount(int index);
    void HandleDiscardItem(int index);

    // 0: 성공, 1: 개수 초과, 2: 잘못된 inde
    int RemoveItem(int index, int itemCount = 1);
    bool UseItem(int index);

    void SortByName();
    void SortByFunc();
    void SortByPrice();
    void MergeSameItems();
};
