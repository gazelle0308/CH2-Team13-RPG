  // Copyright 2026 ShinStella

#include <iostream>
#include <string>

#include "Item/Item.h"
#include "GameLog/GameLog.h"

void Item::PrintUseMessage() const {
    GameLog::GetInstance().itemLog(itemData.GetName(), "사용했습니다.");
}

void Item::SetItemData(std::string id) {
    ItemDataBase::GetInstance().GetItemData(id, itemData);
}

const FItemData& Item::GetItemData() const {
    return itemData;
}

std::string Item::GetId() const {
    return itemData.GetId();
}

EItemCategory Item::GetCategory() const {
    return itemData.GetCategory();
}

std::string Item::GetName() const {
    return itemData.GetName();
}

std::string Item::GetDescription() const {
    return itemData.GetDescription();
}

int Item::GetPrice() const {
    return itemData.GetPrice();
}

int Item::GetMaxStackCount() const {
    return itemData.GetMaxStackCount();
}
