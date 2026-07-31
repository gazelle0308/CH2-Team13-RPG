#include "ShopSystem/ShopSystem.h"
#include "InventorySystem/InventorySystem.h"
#include "Player/Player.h"

void ShopSystem::ShowShop(Player* InPlayer)
{
	player = InPlayer;

	bool isEnd{};
	
	while (!isEnd)
	{
		HandleShopOptions(isEnd);
	}
}

const void ShopSystem::SetShopData()
{
	shopItems = ShopDataBase::GetInstance().GetShopItemDatas();
}

void ShopSystem::ClearScreen() const
{
	std::cout << std::endl;
	std::cout << "...아무 키나 누르세요..." << std::endl;

	(void)_getch();

	system("cls");
}

void ShopSystem::HandleShopOptions(bool& isEnd)
{
	int number{};
	bool isOk{};

	std::cout << "========================================" << std::endl;
	std::cout << "                  상점                  " << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "======= 선택 =======" << std::endl;
	std::cout << "1. 구매하기" << std::endl;
	std::cout << "2. 판매하기" << std::endl;
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
			PrintShopItems();
			HandleSellOptions();
			break;
		case 2:
			ClearScreen();
			HandleBuyOption();
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

void ShopSystem::PrintShopItems() const
{
	int size = (int)shopItems.size();
	int playerGold = player->GetGold(); // 수정
	std::string itemName{};
	int itemPrice{};
	int itemCount{};
	std::string info{};
	std::string itemInfo{};

	std::cout << "========================================" << std::endl;
	std::cout << "                  상점                  " << std::endl;
	std::cout << "========================================" << std::endl;

	for (int index = 0; index < size; index++)
	{
		FShopItemData item = shopItems[index];
		FItemData itemData = ShopDataBase::GetInstance().GetShopItemData(item.id);

		itemName = itemData.name;
		itemPrice = itemData.price;
		itemCount = item.count;

		itemInfo = std::format("{} ({}G) x{}", itemName, itemPrice, itemCount);
		info = std::format("{}. {}", index + 1, itemInfo);

		std::cout << info << std::endl;
	}

	std::cout << std::endl;
	std::cout << "소지 골드: " << playerGold << "G" << std::endl;
}

void ShopSystem::HandleSellOptions()
{
	int number{};
	bool isOk{};

	std::cout << std::endl;
	std::cout << "======= 선택 =======" << std::endl;
	std::cout << "1. 조회" << std::endl;
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
			HandleItemSelection();
			break;
		case 0:
			std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
			ClearScreen();
			break;
		default:
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}

void ShopSystem::HandleBuyOption()
{
	int totalBuyPrice{};
	InventorySystem::GetInstance().ShowInventoryInShop(buybackRate, totalBuyPrice);
	
	BuyFromPlayer(totalBuyPrice);
}

void ShopSystem::HandleItemSelection()
{
	int size = (int)shopItems.size();
	int number{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "아이템 번호 입력(0: 돌아가기): ";
		std::cin >> number;

		isOk = true;

		if (number == 0)
		{
			std::cout << "상점 목록으로 돌아갑니다." << std::endl;
			ClearScreen();
		}
		else if (1 <= number && number <= size)
		{
			PrintItemInfo(number - 1);
			HandleItemOptions(number - 1);
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void ShopSystem::PrintItemInfo(int index) const
{
	std::string id = shopItems[index].id;
	FItemData itemData = ShopDataBase::GetInstance().GetShopItemData(id);

	std::string name = std::format("이름: {}", itemData.name);
	std::string description = std::format("설명: {}", itemData.description);
	std::string price = std::format("가격: {}G", itemData.price);
	std::string count = std::format("개수: {}개", shopItems[index].count);

	std::cout << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << name << std::endl;
	std::cout << description << std::endl;
	std::cout << price << std::endl;
	std::cout << count << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

void ShopSystem::HandleItemOptions(int index)
{
	int number{};
	bool isOk{};

	std::cout << std::endl;
	std::cout << "======= 선택 =======" << std::endl;
	std::cout << "1. 구매하기" << std::endl;
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
			HandleSellItem(index);
			break;
		case 0:
			std::cout << "상점 목록으로 돌아갑니다." << std::endl;
			ClearScreen();
			break;
		default:
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}

void ShopSystem::HandleSellItem(int index)
{
	int number{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "구매할 아이템 개수 입력(0: 돌아가기): ";
		std::cin >> number;

		isOk = true;

		if (number == 0)
		{
			std::cout << "다시 선택합니다." << std::endl;
			HandleItemOptions(index);
		}
		else if (1 <= number && number <= shopItems[index].count)
		{
			FItemData itemData = ShopDataBase::GetInstance().GetShopItemData(shopItems[index].id);
			int price = itemData.price * number;

			if (price <= player->GetGold()) // Player 재화 확인
			{
				std::string message = std::format("{}을(를) {}개 구매했습니다.", itemData.name, number);
				std::cout << message << std::endl;
				SellToPlayer(index, number, price);
				ClearScreen();
			}
			else
			{
				isOk = false;
				std::cout << "골드가 부족합니다." << std::endl;
			}
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 숫자입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void ShopSystem::SellToPlayer(int index, int count, int price)
{
	int playerGold = player->GetGold();
	player->SetGold(playerGold - price);

	InventorySystem::GetInstance().AddItem(shopItems[index].id, count);

	shopItems[index].count -= count;

	if (shopItems[index].count == 0)
	{
		shopItems.erase(shopItems.begin() + index);
	}
}

void ShopSystem::BuyFromPlayer(int totalBuyPrice)
{
	// Player 재화 변경
	int playerGold = player->GetGold();
	player->SetGold(playerGold + totalBuyPrice);
}