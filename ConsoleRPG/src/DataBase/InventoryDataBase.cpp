  // Copyright 2026 ShinStella

#include <iostream>
#include <string>
#include <vector>

#include "DataBase/InventoryDataBase.h"

void InventoryDataBase::LoadInventoryData() {
    // std::ifstream file("data/testInventoryItems.json");  // 테스트 용
    std::ifstream file("data/inventoryItems.json");

    if (!file.is_open()) {
        std::cout << "파일 열기 실패" << std::endl;
        return;
    }

    nlohmann::json data;
    file >> data;

    for (const auto& item : data) {
        FInventoryItemData inventoryItemData;

        inventoryItemData.SetId(item["id"]);
        inventoryItemData.SetCount(item["count"]);

        inventoryItemDatas.push_back(inventoryItemData);
    }
}

void InventoryDataBase::PrintAllInventoryDatas() const {
    std::string id{};
    int count{};
    std::string info{};

    for (const FInventoryItemData& data : inventoryItemDatas) {
        id = data.GetId();
        count = data.GetCount();
        info = std::format("ID: {} x{}", id, count);

        std::cout << info << std::endl;
    }
}

const std::vector<FInventoryItemData>&
    InventoryDataBase::GetInventoryItemDatas() const {
    return inventoryItemDatas;
}
