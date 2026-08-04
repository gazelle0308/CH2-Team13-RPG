#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "Types/PotionWorkshopTypes.h"

class PotionRecipeDataBase
{
private:
	std::vector<FPotionRecipe> potionRecipes;

private:
	PotionRecipeDataBase() {
		LoadPotionRecipeData();
	}

	// 복사 방지
	PotionRecipeDataBase(const PotionRecipeDataBase&) = delete;
	PotionRecipeDataBase& operator=(const PotionRecipeDataBase&) = delete;

	// 이동 방지
	PotionRecipeDataBase(const PotionRecipeDataBase&&) = delete;
	PotionRecipeDataBase& operator=(PotionRecipeDataBase&&) = delete;

	void LoadPotionRecipeData();

public:
	// 싱글톤
	static PotionRecipeDataBase& GetInstance() {
		static PotionRecipeDataBase instance;
		return instance;
	}

	const std::vector<FPotionRecipe>& GetPotionRecipes();
};

