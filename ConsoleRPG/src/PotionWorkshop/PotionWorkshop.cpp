#include "PotionWorkshop/PotionWorkshop.h"

void PotionWorkshop::ShowPotionWorkshop()
{
	bool isEnd{};

	while (!isEnd)
	{
		HandlePotionWorkshopOptions(isEnd);
	}
}

void PotionWorkshop::PrintAllPotionRecipes()
{
	int size = (int)potionRecipeStates.size();
	std::string recipeName{};
	std::string primaryName{};
	std::string secondaryName{};
	int primaryCount{};
	int secondaryCount{};
	std::string recipeInfo{};
	std::string info{};

	std::cout << "================================================================" << std::endl;
	std::cout << "                          포션 레시피                           " << std::endl;
	std::cout << "================================================================" << std::endl;


	for (int index = 0; index < size; index++)
	{
		FPotionRecipeState potionRecipeState = potionRecipeStates[index];

		recipeName = ItemDataBase::GetInstance().GetName(potionRecipeState.potionRecipe.id);
		primaryName = ItemDataBase::GetInstance().GetName(potionRecipeState.potionRecipe.primaryId);
		secondaryName = ItemDataBase::GetInstance().GetName(potionRecipeState.potionRecipe.secondaryId);
		primaryCount = potionRecipeState.potionRecipe.primaryCount;
		secondaryCount = potionRecipeState.potionRecipe.secondaryCount;

		recipeInfo = std::format("{} ({} x{}, {} x{})", recipeName, primaryName, primaryCount, secondaryName, secondaryCount);

		info = std::format("{}. {}", index + 1, recipeInfo);

		std::cout << info << std::endl;
	}
}

void PotionWorkshop::SetPotionWorkshopData()
{
	std::vector<FPotionRecipe> potionRecipes = PotionRecipeDataBase::GetInstance().GetPotionRecipes();

	for (const FPotionRecipe& potionRecipe : potionRecipes)
	{
		FPotionRecipeState potionRecipeState;
		potionRecipeState.potionRecipe = potionRecipe;
		potionRecipeState.isUnlocked = potionRecipe.defaultUnlocked;

		potionRecipeStates.push_back(potionRecipeState);
	}
}

void PotionWorkshop::ClearScreen() const
{
	std::cout << std::endl;
	std::cout << "...아무 키나 누르세요..." << std::endl;

	(void)_getch();

	system("cls");
}

void PotionWorkshop::HandlePotionWorkshopOptions(bool& isEnd)
{
	int number{};
	bool isOk{};

	std::cout << "================================================================" << std::endl;
	std::cout << "                          포션 제작소                           " << std::endl;
	std::cout << "================================================================" << std::endl;
	std::cout << std::endl;
	std::cout << "======== 선택 ========" << std::endl;
	std::cout << "1. 전체 레시피 검색" << std::endl;
	std::cout << "2. 레시피 검색(이름)" << std::endl;
	std::cout << "3. 레시피 검색(재료)" << std::endl;
	std::cout << "4. 포션 제작" << std::endl;
	std::cout << "0. 돌아가기" << std::endl;

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "번호 입력: ";
		std::cin >> number;

		isOk = true;

		switch (number)
		{
		case 1:
			ClearScreen();
			HandleShowAllRecipes();
			break;
		case 2:
			ClearScreen();
			HandleSearchByName();
			break;
		case 3:
			ClearScreen();
			HandleSearchByIngredient();
			break;
		case 4:
			ClearScreen();
			HandleCraftPotion();
			break;
		case 0:
			isEnd = true;
			std::cout << "메인 메뉴로 돌아갑니다." << std::endl;
			ClearScreen();
			break;
		default:
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}

void PotionWorkshop::HandleShowAllRecipes()
{
	bool isEnd{};

	selectedPrs.clear();

	for (FPotionRecipeState& prs : potionRecipeStates)
	{
		selectedPrs.push_back(&prs);
	}

	while (!isEnd)
	{
		PrintSelectedPotionRecipes();
		HandleRecipeOptions(isEnd);
		ClearScreen();
	}
}

void PotionWorkshop::HandleRecipeOptions(bool& isEnd)
{
	if (selectedPrs.empty())
	{
		isEnd = true;
		return;
	}

	int number{};
	bool isOk{};

	std::cout << std::endl;
	std::cout << "======== 선택 ========" << std::endl;
	std::cout << "1. 상세 정보" << std::endl;
	std::cout << "0. 돌아가기" << std::endl;

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "번호 입력: ";
		std::cin >> number;

		isOk = true;

		switch (number)
		{
		case 1:
			HandleRecipeSelection();
			break;
		case 0:
			isEnd = true;
			std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
			break;
		default:
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}

void PotionWorkshop::PrintSelectedPotionRecipes() const
{
	int size = (int)selectedPrs.size();
	std::string recipeName{};
	std::string primaryName{};
	std::string secondaryName{};
	int primaryCount{};
	int secondaryCount{};
	std::string recipeInfo{};
	std::string info{};

	std::cout << "================================================================" << std::endl;
	std::cout << "                           포션 레시피                          " << std::endl;
	std::cout << "================================================================" << std::endl;

	for (int index = 0; index < size; index++)
	{
		FPotionRecipeState potionRecipeState = *selectedPrs[index];

		if (potionRecipeState.isUnlocked)
		{
			recipeName = ItemDataBase::GetInstance().GetName(potionRecipeState.potionRecipe.id);
			primaryName = ItemDataBase::GetInstance().GetName(potionRecipeState.potionRecipe.primaryId);
			secondaryName = ItemDataBase::GetInstance().GetName(potionRecipeState.potionRecipe.secondaryId);
			primaryCount = potionRecipeState.potionRecipe.primaryCount;
			secondaryCount = potionRecipeState.potionRecipe.secondaryCount;

			recipeInfo = std::format("{} ({} x{}, {} x{})", recipeName, primaryName, primaryCount, secondaryName, secondaryCount);
		}
		else
		{
			recipeInfo = "???";
		}

		info = std::format("{}. {}", index + 1, recipeInfo);

		std::cout << info << std::endl;
	}

	if (size == 0)
	{
		std::cout << std::endl;
		std::cout << "검색된 레시피가 없습니다." << std::endl;
	}
}

void PotionWorkshop::HandleRecipeSelection()
{
	int size = (int)selectedPrs.size();
	int number{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "레시피 번호 입력(0: 돌아가기): ";
		std::cin >> number;

		isOk = true;

		if (number == 0)
		{
			std::cout << "이전으로 돌아갑니다." << std::endl;
		}
		else if (1 <= number && number <= size)
		{
			PrintRecipeInfo(number - 1);
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void PotionWorkshop::PrintRecipeInfo(int index) const
{
	FPotionRecipeState prs = *selectedPrs[index];
	std::string name{};
	std::string description{};

	if (prs.isUnlocked)
	{
		FItemData recipeData = ItemDataBase::GetInstance().GetItemData(prs.potionRecipe.id);
		FItemData primaryData = ItemDataBase::GetInstance().GetItemData(prs.potionRecipe.primaryId);
		FItemData secondaryData = ItemDataBase::GetInstance().GetItemData(prs.potionRecipe.secondaryId);

		name = std::format("이름: {}", recipeData.name);
		description = std::format("{}\n\n원재료로 {}이(가) {}개,\n부재료로 {}이(가) {}개 들어갑니다.",
			recipeData.description, primaryData.name, prs.potionRecipe.primaryCount, secondaryData.name, prs.potionRecipe.secondaryCount);
	}
	else
	{
		name = "이름: ???";
		description = "아직 해금되지 않은 레시피입니다.";
	}

	std::cout << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;
	std::cout << name << std::endl;
	std::cout << std::endl;
	std::cout << description << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;
}

void PotionWorkshop::HandleSearchByName()
{
	bool isOk{};
	std::string str{};

	while (!isOk)
	{
		std::cout << "포션 레시피를 이름을 기준으로 검색합니다." << std::endl;
		std::cout << "검색할 단어 입력(돌아가기: 돌아가기): ";

		std::cin >> str;

		isOk = true;

		if (str == "돌아가기")
		{
			isOk = true;
			std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
		}
		else
		{
			bool isEnd{};

			std::cout << std::endl;
			SetSelectedPrsByName(str);
			
			while (!isEnd)
			{
				PrintSelectedPotionRecipes();
				HandleRecipeOptions(isEnd);
				ClearScreen();
			}
		}
	}
}

void PotionWorkshop::HandleSearchByIngredient()
{
	bool isOk{};
	std::string str{};

	while (!isOk)
	{
		std::cout << "포션 레시피를 재료를 기준으로 검색합니다." << std::endl;
		std::cout << "검색할 단어 입력(돌아가기: 돌아가기): ";

		std::cin >> str;

		isOk = true;

		if (str == "돌아가기")
		{
			isOk = true;
			std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
		}
		else
		{
			bool isEnd{};

			std::cout << std::endl;
			SetSelectedPrsByIngredient(str);

			while (!isEnd)
			{
				PrintSelectedPotionRecipes();
				HandleRecipeOptions(isEnd);
				ClearScreen();
			}
		}
	}
}

void PotionWorkshop::SetSelectedPrsByName(std::string str)
{
	selectedPrs.clear();

	std::string name{};

	for (FPotionRecipeState& prs : potionRecipeStates)
	{
		name = ItemDataBase::GetInstance().GetName(prs.potionRecipe.id);

		if (name.find(str) != std::string::npos)
		{
			selectedPrs.push_back(&prs);
		}
	}
}

void PotionWorkshop::SetSelectedPrsByIngredient(std::string str)
{
	selectedPrs.clear();

	std::string primaryName{};
	std::string secondaryName{};

	for (FPotionRecipeState& prs : potionRecipeStates)
	{
		primaryName = ItemDataBase::GetInstance().GetName(prs.potionRecipe.primaryId);
		secondaryName = ItemDataBase::GetInstance().GetName(prs.potionRecipe.secondaryId);

		if (primaryName.find(str) != std::string::npos || secondaryName.find(str) != std::string::npos)
		{
			selectedPrs.push_back(&prs);
		}
	}
}

void PotionWorkshop::HandleCraftPotion()
{
	bool isEnd{};

	selectedPrs.clear();

	for (FPotionRecipeState& prs : potionRecipeStates)
	{
		selectedPrs.push_back(&prs);
	}

	while (!isEnd)
	{
		PrintSelectedPotionRecipes();
		std::cout << std::endl;
		InventorySystem::GetInstance().ShowInventoryInPotionWorkshop();
		HandlePrimarySelection(isEnd);
		ClearScreen();
	}
}

void PotionWorkshop::HandlePrimarySelection(bool& isEnd)
{
	int primaryIndex{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "포션 제작에 사용할 원재료 번호 입력(0: 돌아가기): ";
		std::cin >> primaryIndex;

		isOk = true;

		if (primaryIndex == 0)
		{
			isEnd = true;
			std::cout << "포션 제작소 메뉴로 돌아갑니다." << std::endl;
		}
		else if (1 <= primaryIndex)
		{
			const FItemData itemData = InventorySystem::GetInstance().GetItemData(primaryIndex - 1);
			if (ItemDataBase::GetInstance().GetMaterialType(itemData.id) == EMaterialType::Primary)
			{
				HandlePrimaryCount(primaryIndex - 1);
			}
			else
			{
				isOk = false;
				std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			}
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void PotionWorkshop::HandlePrimaryCount(int primaryIndex)
{
	int primaryCount{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "원재료 개수 입력(범위: 1 ~ 3, 0: 돌아가기): ";
		std::cin >> primaryCount;

		isOk = true;

		if (primaryCount == 0)
		{
			std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
		}
		else if (1 <= primaryCount && primaryCount <= 3)
		{
			HandleSecondarySelection(primaryIndex, primaryCount);
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void PotionWorkshop::HandleSecondarySelection(int primaryIndex, int primaryCount)
{
	int secondaryIndex{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "포션 제작에 사용할 부재료 번호 입력(0: 돌아가기): ";
		std::cin >> secondaryIndex;

		isOk = true;

		if (secondaryIndex == 0)
		{
			std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
		}
		else
		{
			const FItemData itemData = InventorySystem::GetInstance().GetItemData(secondaryIndex - 1);
			if (ItemDataBase::GetInstance().GetMaterialType(itemData.id) == EMaterialType::Secondary)
			{
				HandleSecondaryCount(primaryIndex, primaryCount, secondaryIndex - 1);
			}
			else
			{
				isOk = false;
				std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			}
		}
	}
}

void PotionWorkshop::HandleSecondaryCount(int primaryIndex, int primaryCount, int secondaryIndex)
{
	int secondaryCount{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "부재료 개수 입력(범위: 1 ~ 3, 0: 돌아가기): ";
		std::cin >> secondaryCount;

		isOk = true;

		if (secondaryCount == 0)
		{
			std::cout << "포션 제작 초기로 돌아갑니다." << std::endl;
		}
		else if (1 <= secondaryCount && secondaryCount <= 3)
		{
			HandleCraftPotionResult(primaryIndex, primaryCount, secondaryIndex, secondaryCount);
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void PotionWorkshop::HandleCraftPotionResult(int primaryIndex, int primaryCount, int secondaryIndex, int secondaryCount)
{
	std::vector<std::pair<int, int>> materials{};
	materials.push_back(std::make_pair(primaryIndex, primaryCount));
	materials.push_back(std::make_pair(secondaryIndex, secondaryCount));

	std::vector<FPotionRecipeState*> candidatePrs{};
	std::string primaryId = InventorySystem::GetInstance().GetItemData(primaryIndex).id;
	std::string secondaryId = InventorySystem::GetInstance().GetItemData(secondaryIndex).id;
	std::string potionId{};
	int potionCount{};

	// 제작 로직
	for (FPotionRecipeState& prs : potionRecipeStates)
	{
		if (prs.potionRecipe.primaryId == primaryId && prs.potionRecipe.primaryCount <= primaryCount
			&& prs.potionRecipe.secondaryId == secondaryId && prs.potionRecipe.secondaryCount <= secondaryCount)
		{
			candidatePrs.push_back(&prs);
		}
	}

	if (candidatePrs.empty())
	{
		potionId = failedPotionId;
		potionCount = 1;
	}
	else
	{
		std::sort(candidatePrs.begin(), candidatePrs.end(), compareMaterial);

		FPotionRecipe pr = candidatePrs[0]->potionRecipe;
		potionId = pr.id;
		potionCount = std::min(primaryCount / pr.primaryCount, secondaryCount / pr.secondaryCount);
	}

	if (InventorySystem::GetInstance().CanCraftPotion(materials, potionId, potionCount))
	{
		std::string potionName = ItemDataBase::GetInstance().GetName(potionId);

		std::cout << std::endl;
		std::cout << "제작 완료!" << std::endl;
		std::string message = std::format("{}을(를) {}개 제작했습니다.", potionName, potionCount);
		std::cout << message << std::endl;

		// 레시피 해금
		if (!candidatePrs.empty() && !candidatePrs[0]->isUnlocked)
		{
			candidatePrs[0]->isUnlocked = true;

			std::cout << std::endl;
			std::cout << "★ New! ★" << std::endl;
			std::cout << "새로운 레시피를 발견했습니다!" << std::endl;
		}
	}
	else
	{
		std::cout << "인벤토리에 공간이 부족합니다. 비우고 다시 시도해주세요." << std::endl;
	}
}