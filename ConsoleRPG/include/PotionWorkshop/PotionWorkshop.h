#pragma once
#include <iostream>
#include <sstream>
#include <conio.h>
#include <vector>
#include <string>
#include <algorithm>
#include "DataBase/ItemDataBase.h"
#include "DataBase/ShopDataBase.h"
#include "DataBase/PotionRecipeDataBase.h"
#include "InventorySystem/InventorySystem.h"

inline bool compareMaterial(const FPotionRecipeState* a, const FPotionRecipeState* b)
{
	if (a->potionRecipe.GetPrimaryCount() == b->potionRecipe.GetPrimaryCount())
	{
		return a->potionRecipe.GetSecondaryCount() > b->potionRecipe.GetSecondaryCount();
	}

	return a->potionRecipe.GetPrimaryCount() > b->potionRecipe.GetPrimaryCount();
}

class PotionWorkshop
{
private:
	std::vector<FPotionRecipeState> potionRecipeStates;
	std::vector<FPotionRecipeState*> selectedPrs;
	std::string failedPotionId = "ITEM_MATERIAL_FAILED_POTION";

private:
	PotionWorkshop() {
		SetPotionWorkshopData();
	}

	// 복사 방지
	PotionWorkshop(const PotionWorkshop&) = delete;
	PotionWorkshop& operator=(const PotionWorkshop&) = delete;

	// 이동 방지
	PotionWorkshop(const PotionWorkshop&&) = delete;
	PotionWorkshop& operator=(PotionWorkshop&&) = delete;

public:
	// 싱글톤
	static PotionWorkshop& GetInstance() {
		static PotionWorkshop instance;
		return instance;
	}

	void ShowPotionWorkshop();
	void PrintAllPotionRecipes(); // 테스트용. 전부 보이게 출력

private:
	void SetPotionWorkshopData();

	void ClearScreen() const;
	void HandlePotionWorkshopOptions(bool& isEnd);
	void HandleShowAllRecipes();
	void HandleRecipeOptions(bool& isEnd);
	void PrintSelectedPotionRecipes() const;
	void HandleRecipeSelection();
	void PrintRecipeInfo(int index) const;
	void HandleSearchByName();
	void HandleSearchByIngredient();
	void SplitString(const std::string& str, std::vector<std::string>& result);
	bool ContainsAllString(const std::string& str, const std::string& target);
	void SetSelectedPrsByName(const std::string& str);
	void SetSelectedPrsByIngredient(const std::string& str);
	void HandleCraftPotion();
	void HandleCraftOptions(bool& isEnd);
	void HandleCraftByRecipe();
	void HandleCraftRecipeSelection(int recipeIndex);
	void HandleCraftBySelf();
	void HandlePrimarySelection();
	void HandlePrimaryCount(int primaryIndex);
	void HandleSecondarySelection(int primaryIndex, int primaryCount);
	void HandleSecondaryCount(int primaryIndex, int primaryCount, int secondaryIndex);
	void HandleCraftPotionResult(int primaryIndex, int primaryCount, int secondaryIndex, int secondaryCount);
};

