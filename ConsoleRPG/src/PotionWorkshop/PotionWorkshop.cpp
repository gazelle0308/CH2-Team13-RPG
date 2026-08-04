  // Copyright 2026 ShinStella

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

#include "PotionWorkshop/PotionWorkshop.h"

void PotionWorkshop::ShowPotionWorkshop() {
    bool isEnd{};

    while (!isEnd) {
        HandlePotionWorkshopOptions(isEnd);
    }
}

void PotionWorkshop::PrintAllPotionRecipes() {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    int size = static_cast<int>(potionRecipeStates.size());
    std::string recipeName{};
    std::string primaryName{};
    std::string secondaryName{};
    int primaryCount{};
    int secondaryCount{};
    std::string recipeInfo{};
    std::string info{};

    std::cout << "=========================================" << std::endl;
    std::cout << "              포션 레시피                " << std::endl;
    std::cout << "=========================================" << std::endl;


    for (int index = 0; index < size; index++) {
        FPotionRecipeState potionRecipeState = potionRecipeStates[index];

        if (!itemDataBase.
                    GetName(potionRecipeState.GetId(),
                            recipeName)
            || !itemDataBase.
                    GetName(potionRecipeState.GetPrimaryId(),
                            primaryName)
            || !itemDataBase.
                    GetName(potionRecipeState.GetSecondaryId(),
                            secondaryName)) {
            continue;
        }

        primaryCount = potionRecipeState.GetPrimaryCount();
        secondaryCount = potionRecipeState.GetSecondaryCount();

        recipeInfo = std::format("{} ({} x{}, {} x{})",
                                    recipeName,
                                    primaryName,
                                    primaryCount,
                                    secondaryName,
                                    secondaryCount);

        info = std::format("{}. {}", index + 1, recipeInfo);

        std::cout << info << std::endl;
    }
}

void PotionWorkshop::SetPotionWorkshopData() {
    PotionRecipeDataBase& potionRecipeDataBase =
        PotionRecipeDataBase::GetInstance();
    std::vector<FPotionRecipe> potionRecipes =
        potionRecipeDataBase.GetPotionRecipes();

    for (const FPotionRecipe& potionRecipe : potionRecipes) {
        FPotionRecipeState potionRecipeState;
        potionRecipeState.SetPotionRecipe(potionRecipe);
        potionRecipeState.SetIsUnlocked(potionRecipe.GetDefaultUnlocked());

        potionRecipeStates.push_back(potionRecipeState);
    }
}

void PotionWorkshop::ClearScreen() const {
    std::cout << std::endl;
    std::cout << "...아무 키나 누르세요..." << std::endl;

    (void)_getch();

    system("cls");
}

void PotionWorkshop::HandlePotionWorkshopOptions(bool& isEnd) {
    int number{};
    bool isOk{};

    std::cout << "=========================================" << std::endl;
    std::cout << "              포션 제작소                " << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "======== 선택 ========" << std::endl;
    std::cout << "1. 전체 레시피 검색" << std::endl;
    std::cout << "2. 레시피 검색(이름)" << std::endl;
    std::cout << "3. 레시피 검색(재료)" << std::endl;
    std::cout << "4. 포션 제작" << std::endl;
    std::cout << "0. 돌아가기" << std::endl;

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "번호 입력: ";
        std::cin >> number;

        isOk = true;

        switch (number) {
        case 1:
        {
            ClearScreen();
            HandleShowAllRecipes();
            break;
        }
        case 2:
        {
            ClearScreen();
            HandleSearchByName();
            break;
        }
        case 3:
        {
            ClearScreen();
            HandleSearchByIngredient();
            break;
        }
        case 4:
        {
            ClearScreen();
            HandleCraftPotion();
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

void PotionWorkshop::HandleShowAllRecipes() {
    bool isEnd{};

    selectedPrs.clear();

    for (FPotionRecipeState& prs : potionRecipeStates) {
        selectedPrs.push_back(&prs);
    }

    while (!isEnd) {
        PrintSelectedPotionRecipes();
        HandleRecipeOptions(isEnd);
        ClearScreen();
    }
}

void PotionWorkshop::HandleRecipeOptions(bool& isEnd) {
    if (selectedPrs.empty()) {
        isEnd = true;
        return;
    }

    int number{};
    bool isOk{};

    std::cout << std::endl;
    std::cout << "======== 선택 ========" << std::endl;
    std::cout << "1. 상세 정보" << std::endl;
    std::cout << "0. 돌아가기" << std::endl;

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "번호 입력: ";
        std::cin >> number;

        isOk = true;

        switch (number) {
        case 1:
        {
            HandleRecipeSelection();
            break;
        }
        case 0:
        {
            isEnd = true;
            std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
            break;
        }
        default:
        {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "다시 입력해주세요." << std::endl;
            break;
        }
        }
    }
}

void PotionWorkshop::PrintSelectedPotionRecipes() const {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    int size = static_cast<int>(selectedPrs.size());
    std::string recipeName{};
    std::string primaryName{};
    std::string secondaryName{};
    int primaryCount{};
    int secondaryCount{};
    std::string recipeInfo{};
    std::string info{};

    std::cout << "=========================================" << std::endl;
    std::cout << "              포션 레시피                " << std::endl;
    std::cout << "=========================================" << std::endl;

    for (int index = 0; index < size; index++) {
        FPotionRecipeState potionRecipeState = *selectedPrs[index];

        if (potionRecipeState.isUnlocked) {
            if (!itemDataBase.
                    GetName(potionRecipeState.GetId(),
                            recipeName)
                || !itemDataBase.
                        GetName(potionRecipeState.GetPrimaryId(),
                                primaryName)
                || !itemDataBase.
                        GetName(potionRecipeState.GetSecondaryId(),
                                secondaryName)) {
                continue;
            }

            primaryCount = potionRecipeState.GetPrimaryCount();
            secondaryCount = potionRecipeState.GetSecondaryCount();

            recipeInfo = std::format("{} ({} x{}, {} x{})",
                                        recipeName,
                                        primaryName,
                                        primaryCount,
                                        secondaryName,
                                        secondaryCount);
        } else {
            recipeInfo = "???";
        }

        info = std::format("{}. {}", index + 1, recipeInfo);

        std::cout << info << std::endl;
    }

    if (size == 0) {
        std::cout << std::endl;
        std::cout << "검색된 레시피가 없습니다." << std::endl;
    }
}

void PotionWorkshop::HandleRecipeSelection() {
    int size = static_cast<int>(selectedPrs.size());
    int number{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "레시피 번호 입력(0: 돌아가기): ";
        std::cin >> number;

        isOk = true;

        if (number == 0) {
            std::cout << "이전으로 돌아갑니다." << std::endl;
        } else if (1 <= number && number <= size) {
            PrintRecipeInfo(number - 1);
        } else {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "다시 입력해주세요." << std::endl;
        }
    }
}

void PotionWorkshop::PrintRecipeInfo(int index) const {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    FPotionRecipeState prs = *selectedPrs[index];
    std::string name{};
    std::string description{};

    if (prs.isUnlocked) {
        FItemData recipeData;
        FItemData primaryData;
        FItemData secondaryData;

        if (!itemDataBase.
                GetItemData(prs.GetId(), recipeData)
            || !itemDataBase.
                    GetItemData(prs.GetPrimaryId(), primaryData)
            || !itemDataBase.
                    GetItemData(prs.GetSecondaryId(), secondaryData)) {
            return;
        }

        name = std::format("이름: {}", recipeData.GetName());

        std::string substr1 =
            std::format("{}\n\n원재료로 {}이(가) {}개,\n",
                         recipeData.GetDescription(),
                         primaryData.GetName(),
                         prs.GetPrimaryCount());
        std::string substr2 =
            std::format("부재료로{}이(가) {}개 들어갑니다.",
                secondaryData.GetName(),
                prs.GetSecondaryCount());

        description = substr1 + substr2;
    } else {
        name = "이름: ???";
        description = "아직 해금되지 않은 레시피입니다.";
    }

    std::cout << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << name << std::endl;
    std::cout << std::endl;
    std::cout << description << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

void PotionWorkshop::HandleSearchByName() {
    bool isOk{};
    std::string str{};

    while (!isOk) {
        std::cout << "포션 레시피를 이름을 기준으로 검색합니다. ";
        std::cout << "단어마다 띄어쓰기를 해주세요." << std::endl;
        std::cout << "검색(돌아가기: 돌아가기): ";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, str);

        isOk = true;

        if (str == "돌아가기") {
            isOk = true;
            std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
            ClearScreen();
        } else {
            bool isEnd{};

            std::cout << std::endl;
            SetSelectedPrsByName(str);

            while (!isEnd) {
                PrintSelectedPotionRecipes();
                HandleRecipeOptions(isEnd);
                ClearScreen();
            }
        }
    }
}

void PotionWorkshop::HandleSearchByIngredient() {
    bool isOk{};
    std::string str{};

    while (!isOk) {
        std::cout << "포션 레시피를 재료를 기준으로 검색합니다. ";
        std::cout << "단어마다 띄어쓰기를 해주세요." << std::endl;
        std::cout << "검색(돌아가기: 돌아가기): ";

        std::cin >> str;

        isOk = true;

        if (str == "돌아가기") {
            isOk = true;
            std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
            ClearScreen();
        } else {
            bool isEnd{};

            std::cout << std::endl;
            SetSelectedPrsByIngredient(str);

            while (!isEnd) {
                PrintSelectedPotionRecipes();
                HandleRecipeOptions(isEnd);
                ClearScreen();
            }
        }
    }
}

void PotionWorkshop::SplitString(const std::string& str,
                                 std::vector<std::string>& result) {
    std::istringstream iss(str);
    std::string word{};

    while (iss >> word) {
        result.push_back(word);
    }
}

bool PotionWorkshop::ContainsAllString(const std::string& str,
                                       const std::string& target) {
    std::string newStr(str);
    std::string newTarget(target);

    std::transform(str.begin(),
                   str.end(),
                   newStr.begin(),
                   [](unsigned char c) {
                       return std::toupper(c);
                   });

    std::transform(target.begin(),
                   target.end(),
                   newTarget.begin(),
                   [](unsigned char c) {
                       return std::toupper(c);
                   });

    std::vector<std::string> result{};
    SplitString(newTarget, result);

    for (std::string substr : result) {
        if (newStr.find(substr) == std::string::npos) {
            return false;
        }
    }

    return true;
}

void PotionWorkshop::SetSelectedPrsByName(const std::string& str) {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();

    selectedPrs.clear();

    std::string name{};

    for (FPotionRecipeState& prs : potionRecipeStates) {
        if (!itemDataBase.GetName(prs.GetId(), name)) {
            continue;
        }

        if (ContainsAllString(name, str)) {
            selectedPrs.push_back(&prs);
        }
    }
}

void PotionWorkshop::SetSelectedPrsByIngredient(const std::string& str) {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();

    selectedPrs.clear();

    std::string primaryName{};
    std::string secondaryName{};

    for (FPotionRecipeState& prs : potionRecipeStates) {
        if (!itemDataBase.
                GetName(prs.GetPrimaryId(), primaryName)
            || !itemDataBase.
                GetName(prs.GetSecondaryId(), secondaryName)) {
            return;
        }

        if (ContainsAllString(primaryName, str) ||
                ContainsAllString(secondaryName, str)) {
            selectedPrs.push_back(&prs);
        }
    }
}

void PotionWorkshop::HandleCraftPotion() {
    bool isEnd{};

    selectedPrs.clear();

    for (FPotionRecipeState& prs : potionRecipeStates) {
        selectedPrs.push_back(&prs);
    }

    while (!isEnd) {
        PrintSelectedPotionRecipes();
        HandleCraftOptions(isEnd);
        ClearScreen();
    }
}

void PotionWorkshop::HandleCraftOptions(bool& isEnd) {
    int number{};
    bool isOk{};

    std::cout << std::endl;
    std::cout << "======== 선택 ========" << std::endl;
    std::cout << "1. 레시피로 제작" << std::endl;
    std::cout << "2. 직접 제작" << std::endl;
    std::cout << "0. 돌아가기" << std::endl;

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "번호 입력: ";
        std::cin >> number;

        isOk = true;

        switch (number) {
        case 1:
        {
            HandleCraftByRecipe();
            break;
        }
        case 2:
        {
            HandleCraftBySelf();
            break;
        }
        case 0:
        {
            isEnd = true;
            std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
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

void PotionWorkshop::HandleCraftByRecipe() {
    int size = static_cast<int>(selectedPrs.size());
    int recipeIndex{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "레시피 번호 입력(0: 돌아가기): ";
        std::cin >> recipeIndex;

        isOk = true;

        if (recipeIndex == 0) {
            std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
        } else if (1 <= recipeIndex && recipeIndex <= size) {
            if (selectedPrs[recipeIndex - 1]->GetIsUnlocked()) {
                HandleCraftRecipeSelection(recipeIndex - 1);
            } else {
                isOk = false;
                std::cout << "미지의 레시피입니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            }
        } else {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "다시 입력해주세요." << std::endl;
        }
    }
}

void PotionWorkshop::HandleCraftRecipeSelection(int recipeIndex) {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    InventorySystem& inventorySystem = InventorySystem::GetInstance();
    int size = static_cast<int>(selectedPrs.size());
    int potionCount{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "제작할 포션 개수 입력(0: 돌아가기): ";
        std::cin >> potionCount;

        isOk = true;

        if (potionCount == 0) {
            std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
        } else if (potionCount < 0) {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
        } else {
            FPotionRecipeState potionRecipeState =
                *selectedPrs[recipeIndex];
            std::string potionId = potionRecipeState.GetId();

            FItemData potionData;

            if (!itemDataBase.GetItemData(potionId, potionData)) {
                isOk = false;
                std::cout << "제작에 실패했습니다. ";
                std::cout << "유효하지 않은 포션입니다." << std::endl;

                continue;
            }

            std::vector<std::pair<int, int>> materials{};

            int primaryIndex =
                inventorySystem.FindItem(potionRecipeState.GetPrimaryId());
            int secondaryIndex =
                inventorySystem.FindItem(potionRecipeState.GetSecondaryId());

            if (primaryIndex == -1 || secondaryIndex == -1) {
                isOk = false;
                std::cout << "제작에 실패했습니다. ";
                std::cout << "재료를 가지고 있지 않습니다." << std::endl;

                continue;
            }

            int totalPrimaryCount =
                    potionRecipeState.GetPrimaryCount() * potionCount;
            int totalSecondaryCount =
                    potionRecipeState.GetSecondaryCount() * potionCount;

            materials.push_back(std::make_pair(primaryIndex,
                                               totalPrimaryCount));
            materials.push_back(std::make_pair(secondaryIndex,
                                               totalSecondaryCount));

            int result =
                    inventorySystem.CanCraftPotion(materials,
                                                   potionId,
                                                   potionCount);

            if (result == 0) {
                std::string potionName{};
                itemDataBase.GetName(potionId, potionName);

                std::cout << std::endl;
                std::cout << "제작 완료!" << std::endl;
                std::string message =
                                std::format("{}을(를) {}개 제작했습니다.",
                                              potionName,
                                              potionCount);
                std::cout << message << std::endl;
            } else if (result == 1) {
                isOk = false;
                std::cout << "인벤토리에 공간이 부족합니다. ";
                std::cout << "비우고 다시 시도해주세요." << std::endl;
            } else if (result == 2) {
                isOk = false;
                std::cout << "재료가 부족합니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            } else if (result == 3) {
                isOk = false;
                std::cout << "제작에 실패했습니다. ";
                std::cout << "유효하지 않은 재료입니다." << std::endl;
            }
        }
    }
}

void PotionWorkshop::HandleCraftBySelf() {
    InventorySystem& inventorySystem = InventorySystem::GetInstance();

    std::cout << std::endl;
    inventorySystem.ShowInventoryInPotionWorkshop();
    HandlePrimarySelection();
}

void PotionWorkshop::HandlePrimarySelection() {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    InventorySystem& inventorySystem = InventorySystem::GetInstance();
    int primaryIndex{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "포션 제작에 사용할 원재료 번호 입력";
        std::cout << "(0: 돌아가기) : ";
        std::cin >> primaryIndex;

        isOk = true;

        if (primaryIndex == 0) {
            std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
        } else if (primaryIndex < 0) {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "다시 입력해주세요." << std::endl;
        } else {
            FItemData itemData;

            if (!inventorySystem.
                    GetItemData(primaryIndex - 1, itemData)) {
                isOk = false;
                std::cout << "유효하지 않은 아이템입니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            } else {
                EMaterialType materialType{};

                if (itemDataBase.GetMaterialType(itemData.GetId(),
                                                 materialType)) {
                    if (materialType == EMaterialType::Primary) {
                        HandlePrimaryCount(primaryIndex - 1);
                    } else {
                        isOk = false;
                        std::cout << "원재료가 아닙니다. ";
                        std::cout << "다시 입력해주세요." << std::endl;
                    }
                } else {
                    isOk = false;
                    std::cout << "포션 재료가 아닙니다. ";
                    std::cout << "다시 입력해주세요." << std::endl;
                }
            }
        }
    }
}

void PotionWorkshop::HandlePrimaryCount(int primaryIndex) {
    InventorySystem& inventorySystem = InventorySystem::GetInstance();
    int primaryCount{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "원재료 개수 입력(범위: 1 ~ 3, 0: 돌아가기): ";
        std::cin >> primaryCount;

        isOk = true;

        if (primaryCount == 0) {
            std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
        } else if (1 <= primaryCount && primaryCount <= 3) {
            if (primaryCount <=
                    inventorySystem.GetTotalItemCount(primaryIndex)) {
                HandleSecondarySelection(primaryIndex, primaryCount);
            } else {
                isOk = false;
                std::cout << "재료 개수가 부족합니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            }
        } else {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "다시 입력해주세요." << std::endl;
        }
    }
}

void PotionWorkshop::HandleSecondarySelection(int primaryIndex,
                                              int primaryCount) {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    InventorySystem& inventorySystem = InventorySystem::GetInstance();
    int secondaryIndex{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "포션 제작에 사용할 부재료 번호 입력";
        std::cout << "(0: 돌아가기) : ";
        std::cin >> secondaryIndex;

        isOk = true;

        if (secondaryIndex == 0) {
            std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
        } else if (secondaryIndex < 0) {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "다시 입력해주세요." << std::endl;
        } else {
            FItemData itemData;

            if (!inventorySystem.GetItemData(secondaryIndex - 1,
                                             itemData)) {
                isOk = false;
                std::cout << "유효하지 않은 아이템입니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            } else {
                EMaterialType materialType{};

                if (itemDataBase.GetMaterialType(itemData.GetId(),
                                                 materialType)) {
                    if (materialType == EMaterialType::Secondary) {
                        HandleSecondaryCount(primaryIndex,
                                             primaryCount,
                                             secondaryIndex - 1);
                    } else {
                        isOk = false;
                        std::cout << "부재료가 아닙니다. ";
                        std::cout << "다시 입력해주세요." << std::endl;
                    }
                } else {
                    isOk = false;
                    std::cout << "포션 재료가 아닙니다. ";
                    std::cout << "다시 입력해주세요." << std::endl;
                }
            }
        }
    }
}

void PotionWorkshop::HandleSecondaryCount(int primaryIndex,
                                          int primaryCount,
                                          int secondaryIndex) {
    InventorySystem& inventorySystem = InventorySystem::GetInstance();
    int secondaryCount{};
    bool isOk{};

    while (!isOk) {
        std::cout << std::endl;
        std::cout << "부재료 개수 입력(범위: 1 ~ 3, 0: 돌아가기): ";
        std::cin >> secondaryCount;

        isOk = true;

        if (secondaryCount == 0) {
            std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
        } else if (1 <= secondaryCount && secondaryCount <= 3) {
            if (secondaryCount <=
                    inventorySystem.GetTotalItemCount(secondaryIndex)) {
                HandleCraftPotionResult(primaryIndex,
                                        primaryCount,
                                        secondaryIndex,
                                        secondaryCount);
            } else {
                isOk = false;
                std::cout << "재료 개수가 부족합니다. ";
                std::cout << "다시 입력해주세요." << std::endl;
            }
        } else {
            isOk = false;
            std::cout << "잘못된 번호입니다. ";
            std::cout << "다시 입력해주세요." << std::endl;
        }
    }
}

void PotionWorkshop::HandleCraftPotionResult(int primaryIndex,
                                             int primaryCount,
                                             int secondaryIndex,
                                             int secondaryCount) {
    ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
    ShopDataBase& shopDataBase = ShopDataBase::GetInstance();
    InventorySystem& inventorySystem = InventorySystem::GetInstance();

    std::vector<std::pair<int, int>> materials{};
    materials.push_back(std::make_pair(primaryIndex, primaryCount));
    materials.push_back(std::make_pair(secondaryIndex, secondaryCount));

    std::vector<FPotionRecipeState*> candidatePrs{};
    std::string primaryId = inventorySystem.GetId(primaryIndex);
    std::string secondaryId = inventorySystem.GetId(secondaryIndex);
    std::string potionId{};
    int potionCount{};

    // 제작 로직
    for (FPotionRecipeState& prs : potionRecipeStates) {
        if (prs.GetPrimaryId() == primaryId &&
            prs.GetPrimaryCount() <= primaryCount &&
            prs.GetSecondaryId() == secondaryId &&
            prs.GetSecondaryCount() <= secondaryCount) {
            candidatePrs.push_back(&prs);
        }
    }

    if (candidatePrs.empty()) {
        potionId = failedPotionId;
        potionCount = 1;
    } else {
        std::sort(candidatePrs.begin(), candidatePrs.end(), compareMaterial);

        FPotionRecipe pr = candidatePrs[0]->potionRecipe;
        potionId = pr.id;
        potionCount =
            std::min(primaryCount / pr.GetPrimaryCount(),
                     secondaryCount / pr.GetSecondaryCount());
    }

    std::string potionName{};

    if (!itemDataBase.GetName(potionId, potionName)) {
        std::cout << "제작에 실패했습니다. ";
        std::cout << "유효하지 않은 포션입니다." << std::endl;

        return;
    }

    int result =
        inventorySystem.CanCraftPotion(materials, potionId, potionCount);

    if (result == 0) {
        if (potionId == failedPotionId) {
            std::cout << std::endl;
            std::cout << "제작 실패" << std::endl;
            std::string message =
                std::format("{}을(를) {}개 획득했습니다.",
                             potionName,
                             potionCount);
            std::cout << message << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "제작 완료!" << std::endl;
            std::string message =
                std::format("{}을(를) {}개 제작했습니다.",
                             potionName,
                             potionCount);
            std::cout << message << std::endl;

            // 레시피 해금
            if (!candidatePrs.empty() && !candidatePrs[0]->isUnlocked) {
                candidatePrs[0]->isUnlocked = true;
                shopDataBase.SetShopItemUnlocked(potionId, true);

                std::cout << std::endl;
                std::cout << "★ New! ★" << std::endl;
                std::cout << "새로운 레시피를 발견했습니다!" << std::endl;
            }
        }
    } else if (result == 1) {
        std::cout << "인벤토리에 공간이 부족합니다. ";
        std::cout << "비우고 다시 시도해주세요." << std::endl;
    } else if (result == 2) {
        std::cout << "재료가 부족합니다. ";
        std::cout << "다시 시도해주세요." << std::endl;
    } else if (result == 3) {
        std::cout << "제작에 실패했습니다. ";
        std::cout << "유효하지 않은 재료입니다." << std::endl;
    }
}
