  // Copyright 2026 ShinStella

#include <iostream>
#include <vector>

#include "DataBase/PotionRecipeDataBase.h"

void PotionRecipeDataBase::LoadPotionRecipeData() {
    std::ifstream file("data/potionRecipes.json");

    if (!file.is_open()) {
        std::cout << "파일 열기 실패" << std::endl;
        return;
    }

    nlohmann::json data;
    file >> data;

    for (const auto& recipe : data) {
        FPotionRecipe potionRecipe;

        potionRecipe.id = recipe["id"];
        potionRecipe.primaryId = recipe["primaryId"];
        potionRecipe.primaryCount = recipe["primaryCount"];
        potionRecipe.secondaryId = recipe["secondaryId"];
        potionRecipe.secondaryCount = recipe["secondaryCount"];
        potionRecipe.defaultUnlocked = recipe["defaultUnlocked"];

        potionRecipes.push_back(potionRecipe);
    }
}

const std::vector<FPotionRecipe>& PotionRecipeDataBase::GetPotionRecipes() {
    return potionRecipes;
}
