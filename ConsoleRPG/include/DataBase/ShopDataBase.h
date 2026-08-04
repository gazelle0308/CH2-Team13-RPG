  // Copyright 2026 ShinStella

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include "Types/ItemTypes.h"
#include "Types/ShopTypes.h"
#include "DataBase/ItemDataBase.h"

class ShopDataBase {
 private:
     // 초기 데이터
    std::vector<FShopItemData> shopItemDatas;
    // 런타임 데이터. 전체 목록
    std::vector<FShopSlot> shopSlots;
    // 런타임 데이터. 판매 가능 목록
    std::vector<FShopSlot*> sellableShopSlots;
    // item id와 shop slot index 매칭
    std::unordered_map<std::string, int> shopSlotIndexMap;

 public:
    ShopDataBase() {
        LoadShopData();
    }

    // 복사 방지
    ShopDataBase(const ShopDataBase&) = delete;
    ShopDataBase& operator=(const ShopDataBase&) = delete;

    // 이동 방지
    ShopDataBase(ShopDataBase&&) = delete;
    ShopDataBase& operator=(ShopDataBase&&) = delete;

    void LoadShopData();

 public:
    // 싱글톤
    static ShopDataBase& GetInstance() {
        static ShopDataBase instance;
        return instance;
    }

    // 테스트용
    void PrintAllShopDatas() const;

 public:
    void SetShopItemUnlocked(std::string id, bool isUnlocked);

    const std::vector<FShopItemData>& GetShopItemDatas() const;
    std::vector<FShopSlot>* GetShopSlots();
    std::vector<FShopSlot*>* GetSellableShopSlots();
};

