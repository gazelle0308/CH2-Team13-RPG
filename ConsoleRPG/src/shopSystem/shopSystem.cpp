#include "ShopSystem/ShopSystem.h"
#include "InventorySystem/InventorySystem.h"
#include "Player/Player.h"

void ShopSystem::ShowShop()
{
	bool isEnd{};
	
	while (!isEnd)
	{
		HandleShopOptions(isEnd);
	}
}

void ShopSystem::SetShopData()
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

	std::cout << "================================================================" << std::endl;
	std::cout << "                              상점                              " << std::endl;
	std::cout << "================================================================" << std::endl;
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
			HandleSell();
			break;
		case 2:
			ClearScreen();
			HandleBuy();
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

void ShopSystem::HandleSell()
{
	bool isEnd{};

	while (!isEnd)
	{
		PrintShopItems();
		PrintPlayerGold();
		HandleSellOptions(isEnd);
		ClearScreen();
	}
}

void ShopSystem::PrintShopItems() const
{
	ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
	int size = (int)shopItems.size();
	std::string itemName{};
	int itemPrice{};
	int itemCount{};
	std::string info{};
	std::string itemInfo{};

	std::cout << "================================================================" << std::endl;
	std::cout << "                              상점                              " << std::endl;
	std::cout << "================================================================" << std::endl;

	for (int index = 0; index < size; index++)
	{
		FShopItemData item = shopItems[index];
		FItemData itemData;
		
		if (!itemDataBase.GetItemData(item.id, itemData))
		{
			continue;
		}

		itemName = itemData.GetName();
		itemPrice = itemData.GetPrice();
		itemCount = item.GetCount();

		itemInfo = std::format("{} ({}G) x{}", itemName, itemPrice, itemCount);
		info = std::format("{}. {}", index + 1, itemInfo);

		std::cout << info << std::endl;
	}
}

void ShopSystem::PrintPlayerGold() const
{
	Player& player = Player::GetInstance();
	int playerGold = player[Pstat::Gold];
	std::string message = std::format("소지 골드: {}G", playerGold);

	std::cout << std::endl;
	std::cout << message << std::endl;
}

void ShopSystem::HandleSellOptions(bool& isEnd)
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
			isEnd = true;
			std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
			break;
		default:
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}

void ShopSystem::HandleBuy() const
{
	InventorySystem& inventorySystem = InventorySystem::GetInstance();
	int totalBuyPrice{};
	bool isEnd{};

	while (!isEnd)
	{
		totalBuyPrice = 0;
		inventorySystem.ShowInventoryInShop(buybackRate, totalBuyPrice, isEnd);
		BuyFromPlayer(totalBuyPrice);
	}
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
			std::cout << "이전으로 돌아갑니다." << std::endl;
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
	ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
	std::string id = shopItems[index].GetId();
	FItemData itemData;
	
	if (!itemDataBase.GetItemData(id,itemData))
	{
		return;
	}

	std::string name = std::format("이름: {}", itemData.GetName());
	std::string description = std::format("{}", itemData.GetDescription());
	std::string price = std::format("가격: {}G", itemData.GetPrice());
	std::string count = std::format("보유: {}개", shopItems[index].GetCount());

	std::cout << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << name << std::endl;
	std::cout << std::endl;
	std::cout << description << std::endl;
	std::cout << std::endl;
	std::cout << price << std::endl;
	std::cout << count << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
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
			std::cout << "구매 초기로 돌아갑니다." << std::endl;
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
	ItemDataBase& itemDataBase = ItemDataBase::GetInstance();
	Player& player = Player::GetInstance();
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
		else if (1 <= number && number <= shopItems[index].GetCount())
		{
			FItemData itemData;

			if (!itemDataBase.GetItemData(shopItems[index].GetId(), itemData))
			{
				isOk = false;
				std::cout << "아이템 정보가 유효하지 않습니다. 다시 선택해 주세요." << std::endl;
				
				continue;
			}

			int price = itemData.GetPrice() * number;

			if (price <= player[Pstat::Gold]) // Player 재화 확인
			{
				std::string message = std::format("{}을(를) {}개 구매했습니다.", itemData.GetName(), number);
				std::cout << message << std::endl;
				SellToPlayer(index, number, price);
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
	Player& player = Player::GetInstance();
	InventorySystem& inventorySystem = InventorySystem::GetInstance();

	int shopCount{};
	
	player[Pstat::Gold] -= price;

	inventorySystem.AddItem(shopItems[index].GetId(), count);

	shopCount = shopItems[index].GetCount();
	shopItems[index].SetCount(shopCount - count);
	shopCount = shopItems[index].GetCount();

	if (shopCount == 0)
	{
		shopItems.erase(shopItems.begin() + index);
	}
}

void ShopSystem::BuyFromPlayer(int totalBuyPrice) const
{
	 //Player 재화 변경
	Player& player = Player::GetInstance();

	player[Pstat::Gold] += totalBuyPrice;
}