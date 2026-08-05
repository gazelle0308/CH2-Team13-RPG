  // Copyright 2026 ShinStella

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "Types/InventoryTypes.h"
#include "DataBase/ItemDataBase.h"

class InventoryDataBase {
 private:
    std::vector<FInventoryItemData> inventoryItemDatas;

 private:
    InventoryDataBase() {
        LoadInventoryData();
    }

    // 복사 방지
    InventoryDataBase(const InventoryDataBase&) = delete;
    InventoryDataBase& operator=(const InventoryDataBase&) = delete;

    // 이동 방지
    InventoryDataBase(const InventoryDataBase&&) = delete;
    InventoryDataBase& operator=(InventoryDataBase&&) = delete;

    void LoadInventoryData();

 public:
    static InventoryDataBase& GetInstance() {
        static InventoryDataBase instance;
        return instance;
    }

    void PrintAllInventoryDatas() const;  // 테스트용

    const std::vector<FInventoryItemData>& GetInventoryItemDatas() const;
};

