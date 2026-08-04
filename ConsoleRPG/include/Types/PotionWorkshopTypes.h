#pragma once
#include <string>

// 포션 레시피 초기 데이터
struct FPotionRecipe
{
public:
	std::string id = "ID";
	std::string primaryId = "PrimaryId";
	int primaryCount = 0;
	std::string secondaryId = "SecondaryId";
	int secondaryCount = 0;
	bool defaultUnlocked = false;

public:
	std::string GetId() const {
		return id;
	}
	std::string GetPrimaryId() const {
		return primaryId;
	}
	int GetPrimaryCount() const {
		return primaryCount;
	}
	std::string GetSecondaryId() const {
		return secondaryId;
	}
	int GetSecondaryCount() const {
		return secondaryCount;
	}
	bool GetDefaultUnlocked() const {
		return defaultUnlocked;
	}
};

// 포션 레시피 런타임 데이터
struct FPotionRecipeState
{
public:
	FPotionRecipe potionRecipe;
	bool isUnlocked = false;

public:
	void SetPotionRecipe(const FPotionRecipe& potionRecipe_) {
		potionRecipe = potionRecipe_;
	}
	void SetIsUnlocked(bool isUnlocked_) {
		isUnlocked = isUnlocked_;
	}

	std::string GetId() const {
		return potionRecipe.GetId();
	}
	std::string GetPrimaryId() const {
		return potionRecipe.GetPrimaryId();
	}
	int GetPrimaryCount() const {
		return potionRecipe.GetPrimaryCount();
	}
	std::string GetSecondaryId() const {
		return potionRecipe.GetSecondaryId();
	}
	int GetSecondaryCount() const {
		return potionRecipe.GetSecondaryCount();
	}
	bool GetDefaultUnlocked() const {
		return potionRecipe.GetDefaultUnlocked();
	}
	bool GetIsUnlocked() const {
		return isUnlocked;
	}
};