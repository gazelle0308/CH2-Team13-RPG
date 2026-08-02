#pragma once
#include <string>

struct FPotionRecipe
{
	std::string id = "ID";
	std::string primaryId = "PrimaryId";
	int primaryCount = 0;
	std::string secondaryId = "SecondaryId";
	int secondaryCount = 0;
	bool defaultUnlocked = false;
};

struct FPotionRecipeState
{
	FPotionRecipe potionRecipe;
	bool isUnlocked = false;
};