  // Copyright 2026 ShinStella

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <utility>

#include "InventorySystem/InventorySystem.h"

void InventorySystem::ShowInventoryInNormal() {
    bool isEnd{};

    while (!isEnd) {
        PrintInventoryItems(EInventoryViewMode::Normal);
        HandleNormalInventoryOptions(isEnd);
    }
}

void InventorySystem::ShowInventoryInBattle() {
    bool isEnd{};

    while (!isEnd) {
        PrintInventoryItems(EInventoryViewMode::Battle);
        HandleBattleInventoryOptions(isEnd);
    }
}

void InventorySystem::ShowInventoryInShop(double buybackRate,
                                          int& totalBuyPrice,
                                          bool& isEnd) {
    PrintInventoryItems(EInventoryViewMode::Shop, buybackRate);
    PrintPlayerGold();
    HandleShopInventoryOptions(buybackRate, totalBuyPrice, isEnd);
}

void InventorySystem::ShowInventoryInPotionWorkshop() {
    PrintInventoryItems(EInventoryViewMode::PotionWorkshop);
}

// 0: 성공, 1: 공간 부족, 2: 재료 부족, 3: 잘못된 index
int InventorySystem::CanCraftPotion(std::vector<std::pair<int, int>>& materials,
                                    std::string potionId,
                                    int potionCount) {
    std::vector<FInventorySlot> tmpItems(items);

    std::sort(materials.begin(),
              materials.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                    return a.first > b.first;
                });

    for (const std::pair<int, int> material : materials) {
        int result = RemoveItem(material.first, material.second);

        std::cout << items.size() << std::endl;

        if (result == 1) {
            items = tmpItems;

            return 2;
        } else if (result == 2) {
            items = tmpItems;

            return 3;
        }
    }

    if (AddItem(potionId, potionCount)) {
        return 0;
    }

    items = tmpItems;

    return 1;
}

bool InventorySystem::GetItemData(int index, FItemData& itemData) const {
    int inventoryCount = static_cast<int>(items.size());

    if (index < 0 || inventoryCount <= index) {
        return false;
    }

    itemData = items[index].GetItemData();

    return true;
}

std::string InventorySystem::GetId(int index) const {
    return items[index].GetItemData().GetId();
}

void InventorySystem::SetInventoryData() {
    InventoryDataBase& inventoryDataBase = InventoryDataBase::GetInstance();
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();

    const std::vector<FInventoryItemData> inventoryItemDatas =
        inventoryDataBase.GetInventoryItemDatas();

    for (const FInventoryItemData& data : inventoryItemDatas) {
        FItemData itemData;

        if (!itemDataBase.GetItemData(data.GetId(), itemData)) {
            continue;
        }

        FInventorySlot itemSlot;

        itemSlot.SetItemData(itemData);
        itemSlot.SetCount(data.GetCount());

        items.push_back(itemSlot);
    }
}

void InventorySystem::ClearScreen() const {
    std::cout << std::endl;
    std::cout << "...아무 키나 누르세요..." << std::endl;

    (void)_getch();

    system("cls");
}

void InventorySystem::PrintInventoryItems(EInventoryViewMode mode,
                                          double buybackRate) const {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    FEnumDisplay enumDisplay;

    int inventoryCount = static_cast<int>(items.size());

    std::cout << "====================================== = " << std::endl;
    std::string str
        = std::format("         인벤토리 ({}/{})",
                        inventoryCount,
                        inventoryMaxSize);
    std::cout << str << std::endl;
    std::cout << "====================================== = " << std::endl;

    for (int index = 0; index < inventoryCount; index++) {
        std::string itemName = items[index].GetName();
        int itemCount = items[index].GetCount();
        std::string itemInfo = std::format("{} x{}", itemName, itemCount);
        std::string info{};

        if (mode == EInventoryViewMode::Battle) {
            if (items[index].GetCategory() != EItemCategory::Consumable) {
                continue;
            }

            std::vector<FConsumableEffect> effects{};

            if (!itemDataBase.GetConsumableEffects(items[index].GetId(),
                                                   effects)) {
                continue;
            }

            std::string effect{};

            effect =
                std::accumulate(
                        effects.begin(),
                        effects.end(),
                        effect,
                        [&enumDisplay](std::string result,
                                       const FConsumableEffect& e) {
                            std::string s =
                            std::format("{} +{}",
                                         enumDisplay.
                                         GetConsumableTypeDisplayName(
                                            e.consumableType),
                                            e.value);
                            return result + s + ", ";
                        });

            effect.erase(effect.end() - 2, effect.end());

            itemInfo = std::format("{} ({}) x{}", itemName, effect, itemCount);
        } else if (mode == EInventoryViewMode::PotionWorkshop) {
            if (items[index].GetCategory() != EItemCategory::Material) {
                continue;
            }

            EMaterialType materialType{};

            if (!itemDataBase.GetMaterialType(items[index].GetId(),
                                              materialType) ||
                materialType != EMaterialType::Primary &&
                materialType != EMaterialType::Secondary) {
                continue;
            }

            std::string mT =
                enumDisplay.GetMaterialTypeDisplayName(materialType);

            itemInfo = std::format("{} ({}) x{}", itemName, mT, itemCount);

        } else if (mode == EInventoryViewMode::Shop) {
            // 낮춘 가격으로 판매 가능
            int itemPrice =
                    static_cast<int>(items[index].GetPrice() * buybackRate);

            itemInfo = std::format("{} ({}G) x{}",
                                    itemName,
                                    itemPrice,
                                    itemCount);
        }

        info = std::format("{}. {}", index + 1, itemInfo);

        std::cout << info << std::endl;
    }
}

void InventorySystem::HandleNormalInventoryOptions(bool& isEnd) {
    int number{};
    bool isOk{};

    std::cout << std::endl;
    std::cout << "======= 선택 =======" << std::endl;
    std::cout << "1. 조회" << std::endl;
    std::cout << "2. 아이템 정리" << std::endl;
    std::cout << "3. 정렬 (이름순)" << std::endl;
    std::cout << "4. 정렬 (기능순)" << std::endl;
    std::cout << "5. 정렬 (가격순)" << std::endl;
    std::cout << "0. 돌아가기" << std::endl;

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "번호 입력: ";
        std::cin >> number;

        isOk = true;

        switch (number) {
        case 1:
        {
            HandleNormalItemSelection();
            break;
        }
        case 2:
        {
            MergeSameItems();
            ClearScreen();
            break;
        }
        case 3:
        {
            SortByName();
            ClearScreen();
            break;
        }
        case 4:
        {
            SortByFunc();
            ClearScreen();
            break;
        }
        case 5:
        {
            SortByPrice();
            ClearScreen();
            break;
        }
        case 0:
        {
            isEnd = true;
            std::cout << "메인 메뉴로 돌아갑니다." << std::endl;
            ClearScreen();
            break;
        }
        default:
        {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
            break;
        }
        }
    }
}

void InventorySystem::HandleBattleInventoryOptions(bool& isEnd) {
    int inventoryCount = static_cast<int>(items.size());
    int number{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "사용할 아이템 번호 입력(0: 돌아가기): ";
        std::cin >> number;

        isOk = true;

        if (number == 0) {
            isEnd = true;
            std::cout << "전투 메뉴로 돌아갑니다." << std::endl;
            ClearScreen();

        } else if (1 <= number && number <= inventoryCount) {
            if (items[number - 1].GetCategory() ==
                EItemCategory::Consumable) {
                UseItem(number - 1);
                ClearScreen();
            } else {
                isOk = false;
                std::cout << "잘못된 번호입니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            }
        } else {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
        }
    }
}

void InventorySystem::PrintPlayerGold() const {
    Player& player = Player::GetInstance();
    int playerGold = player[Pstat::Gold];

    std::cout << std::endl;
    std::cout << "소지 골드: " << playerGold << "G" << std::endl;
}

void InventorySystem::HandleShopInventoryOptions(double buybackRate,
                                                 int& totalBuyPrice,
                                                 bool& isEnd) {
    int inventoryCount = static_cast<int>(items.size());
    int number{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "판매할 아이템 번호 입력(0: 돌아가기): ";
        std::cin >> number;

        isOk = true;

        if (number == 0) {
            isEnd = true;
            std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
            ClearScreen();

        } else if (1 <= number && number <= inventoryCount) {
            HandleShopItemOptions(number - 1, buybackRate, totalBuyPrice);
        } else {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
        }
    }
}

void InventorySystem::HandleNormalItemSelection() {
    int inventoryCount = static_cast<int>(items.size());
    int number{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "아이템 번호 입력(0: 돌아가기): ";
        std::cin >> number;

        isOk = true;

        if (number == 0) {
            std::cout << "인벤토리 목록으로 돌아갑니다." << std::endl;
            ClearScreen();
        } else if (1 <= number && number <= inventoryCount) {
            PrintItemInfo(number - 1);
            HandleNormalItemOptions(number - 1);
        } else {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
        }
    }
}

void InventorySystem::PrintItemInfo(int index) const {
    std::string name = std::format("이름: {}", items[index].GetName());
    std::string description = std::format("{}", items[index].GetDescription());
    std::string price = std::format("가격: {}G", items[index].GetPrice());
    std::string count = std::format("보유: {}개", GetTotalItemCount(index));

    std::cout << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << name << std::endl;
    std::cout << std::endl;
    std::cout << description << std::endl;
    std::cout << std::endl;
    std::cout << price << std::endl;
    std::cout << count << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
}

void InventorySystem::HandleNormalItemOptions(int index) {
    if (items[index].GetCategory() == EItemCategory::Material) {
        HandleNormalNonUsableItemOptions(index);
    } else {
        HandleNormalUsableItemOptions(index);
    }
}

void InventorySystem::HandleNormalUsableItemOptions(int index) {
    int number{};
    bool isOk{};

    std::cout << std::endl;
    std::cout << "======= 선택 =======" << std::endl;
    std::cout << "1. 사용" << std::endl;
    std::cout << "2. 버리기" << std::endl;
    std::cout << "0. 돌아가기" << std::endl;

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "번호 입력: ";
        std::cin >> number;

        isOk = true;

        switch (number) {
        case 1:
        {
            UseItem(index);
            ClearScreen();
            break;
        }
        case 2:
        {
            HandleDiscardItem(index);
            break;
        }
        case 0:
        {
            std::cout << "인벤토리 목록으로 돌아갑니다." << std::endl;
            ClearScreen();
            break;
        }
        default:
        {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
            break;
        }
        }
    }
}

void InventorySystem::HandleNormalNonUsableItemOptions(int index) {
    int number{};
    bool isOk{};

    std::cout << std::endl;
    std::cout << "======= 선택 =======" << std::endl;
    std::cout << "1. 버리기" << std::endl;
    std::cout << "0. 돌아가기" << std::endl;

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "번호 입력: ";
        std::cin >> number;

        isOk = true;

        switch (number) {
        case 1:
        {
            HandleDiscardItem(index);
            break;
        }
        case 0:
        {
            std::cout << "인벤토리 목록으로 돌아갑니다." << std::endl;
            ClearScreen();
            break;
        }
        default:
        {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
            break;
        }
        }
    }
}

void InventorySystem::HandleShopItemOptions(int index,
                                            double buybackRate,
                                            int& totalBuyPrice) {
    int number{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "판매할 아이템 개수 입력(0: 돌아가기): ";
        std::cin >> number;

        isOk = true;

        if (number == 0) {
            std::cout << "판매 목록을 조회합니다." << std::endl;
            ClearScreen();
        } else if (number < 0) {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
        } else {
            FInventorySlot itemSlot = items[index];
            int result = RemoveItem(index, number);

            if (result == 0) {
                std::string messages =
                        std::format("{}을(를) {}개 판매했습니다.",
                                       itemSlot.GetName(),
                                       number);
                std::cout << messages << std::endl;
                totalBuyPrice +=
                    static_cast<int>(itemSlot.GetPrice() *
                                        buybackRate) *
                                        number;
                ClearScreen();
            } else if (result == 1) {
                isOk = false;
                std::cout << "가지고 있는 개수보다 많습니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            } else if (result == 2) {
                isOk = false;
                std::cout << "유효하지 않은 아이템입니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            }
        }
    }
}

void InventorySystem::HandleDiscardItem(int index) {
    int number{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "버릴 아이템 개수 입력(0: 돌아가기): ";
        std::cin >> number;

        isOk = true;

        if (number == 0) {
            std::cout << "다시 선택합니다." << std::endl;
            HandleNormalItemOptions(index);
        } else if (number < 0) {
            isOk = false;
            std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
        } else {
            FInventorySlot itemSlot = items[index];
            int result = RemoveItem(index, number);

            if (result == 0) {
                std::string message =
                        std::format("{}을(를) {}개 버렸습니다.",
                                      itemSlot.GetName(),
                                      number);
                std::cout << message << std::endl;
                ClearScreen();
            } else if (result == 1) {
                isOk = false;
                std::cout << "가지고 있는 개수보다 많습니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            } else if (result == 2) {
                isOk = false;
                std::cout << "유효하지 않은 아이템입니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            }
        }
    }
}

bool InventorySystem::AddItem(std::string id, int itemCount) {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    FItemData itemData;

    if (!itemDataBase.GetItemData(id, itemData)) {
        return false;
    }

    int inventoryCount = static_cast<int>(items.size());
    int result = FindItem(id);
    int itemMaxStackCount = itemData.GetMaxStackCount();
    int fullSlotCount{};
    int partiallyFullSlotCount{};

    if (result != -1) {
        int count = items[result].GetCount();

        if (count + itemCount <= itemMaxStackCount) {
            items[result].SetCount(count + itemCount);

            return true;
        } else {
            itemCount -= itemMaxStackCount - count;
            fullSlotCount += 1;
        }
    }

    fullSlotCount = itemCount / itemMaxStackCount;
    partiallyFullSlotCount = itemCount % itemMaxStackCount == 0 ? 0 : 1;

    if (inventoryCount + fullSlotCount + partiallyFullSlotCount <=
            inventoryMaxSize) {
        if (result != -1) {
            items[result].SetCount(itemMaxStackCount);
        }

        FInventorySlot inventorySlot;
        inventorySlot.SetItemData(itemData);
        inventorySlot.SetCount(itemMaxStackCount);

        for (int i = 0; i < fullSlotCount; i++) {
            items.push_back(inventorySlot);
        }

        if (partiallyFullSlotCount == 1) {
            inventorySlot.SetCount(itemCount % itemMaxStackCount);
            items.push_back(inventorySlot);
        }

        return true;
    }

    return false;
}

// 0: 성공, 1: 개수 초과, 2: 잘못된 index
int InventorySystem::RemoveItem(int index, int count) {
    int inventoryCount = static_cast<int>(items.size());

    if (index < 0 || inventoryCount <= index) {
        return 2;
    }

    int result = GetTotalItemCount(index);

    if (count <= result) {
        std::string itemId = items[index].GetId();
        int left = count;
        int slotIndex = index;
        int number{};
        int itemCount{};

        while (left != 0) {
            itemCount = items[slotIndex].GetCount();
            number = std::min(left, itemCount);
            left -= number;
            items[slotIndex].SetCount(itemCount - number);

            if (items[slotIndex].GetCount() == 0) {
                items.erase(items.begin() + slotIndex);
            }

            slotIndex = FindItem(itemId);
        }

        return 0;
    }

    return 1;
}

// -1: fail, 0~: index(동일한 아이템 존재 시 아이템 가장 적게 들어있는 슬롯)
int InventorySystem::FindItem(std::string id) const {
    int inventoryCount = static_cast<int>(items.size());
    int index = -1;
    int minNum = -1;

    for (int i = 0; i < inventoryCount; i++) {
        if (items[i].GetId() == id) {
            if (minNum == -1 || items[i].GetCount() < minNum) {
                index = i;
                minNum = items[i].GetCount();
            }
        }
    }

    return index;
}

int InventorySystem::GetTotalItemCount(int index) const {
    int inventoryCount = static_cast<int>(items.size());
    std::string itemId = items[index].GetId();
    int total{};

    for (int i = 0; i < inventoryCount; i++) {
        if (items[i].GetId() == itemId) {
            total += items[i].GetCount();
        }
    }

    return total;
}

bool InventorySystem::UseItem(int index) {
    int inventoryCount = static_cast<int>(items.size());

    if (index < 0 || inventoryCount <= index) {
        return false;
    }

    ItemFactory itemFactory;
    std::string itemId = items[index].GetId();
    EItemCategory itemCategory = items[index].GetCategory();

    if (RemoveItem(index) != 0) {
        return false;
    }

    switch (itemCategory) {
    case EItemCategory::Consumable:
    {
        itemFactory.CreateConsumableItem(itemId)->Use();
        break;
    }
    case EItemCategory::Upgrade:
    {
        itemFactory.CreateUpgradeItem(itemId)->Use();
        break;
    }
    }

    return true;
}

void InventorySystem::SortByName() {
    std::sort(items.begin(), items.end(), compareName);
}

void InventorySystem::SortByFunc() {
    std::sort(items.begin(), items.end(), compareFunc);
}

void InventorySystem::SortByPrice() {
    std::sort(items.begin(), items.end(), comparePrice);
}

void InventorySystem::MergeSameItems() {
    int inventoryCount = static_cast<int>(items.size());

    std::vector<FInventorySlot> newItems{};
    std::unordered_set<std::string> visit{};

    int newInventoryCount{};
    int totalCount{};
    int fullSlot{};
    int remainder{};
    int itemMaxStackCount{};

    for (int i = 0; i < inventoryCount; i++) {
        if (!visit.contains(items[i].GetId())) {
            visit.emplace(items[i].GetId());

            totalCount = GetTotalItemCount(i);
            itemMaxStackCount = items[i].GetMaxStackCount();
            fullSlot = totalCount / itemMaxStackCount;
            remainder = totalCount % itemMaxStackCount;

            FInventorySlot inventorySlot;
            inventorySlot.SetItemData(items[i].GetItemData());
            inventorySlot.SetCount(itemMaxStackCount);

            for (int j = 0; j < fullSlot; j++) {
                newItems.push_back(inventorySlot);
            }

            if (remainder != 0) {
                inventorySlot.SetCount(remainder);
                newItems.push_back(inventorySlot);
            }
        }
    }

    items = newItems;
}

void InventorySystem::ExpandInventory(int size) {
    inventoryMaxSize += size;
}
