#include "InventorySystem/InventorySystem.h"

void InventorySystem::ShowInventoryInNormal()
{
	bool isEnd{};

	while (!isEnd)
	{
		PrintInventoryItems(EInventoryViewMode::Normal);
		HandleNormalInventoryOptions(isEnd);
	}
}

void InventorySystem::ShowInventoryInShop(float buybackRate, int& totalBuyPrice)
{
	bool isEnd{};

	while (!isEnd)
	{
		PrintInventoryItems(EInventoryViewMode::Shop, buybackRate);
		HandleShopInventoryOptions(buybackRate, totalBuyPrice, isEnd);
	}
}

void InventorySystem::ExpandInventory(int size)
{
	inventorySize += size;
}

void InventorySystem::ClearScreen() const
{
	std::cout << std::endl;
	std::cout << "...아무 키나 누르세요..." << std::endl;

	(void)_getch();

	system("cls");
}

void InventorySystem::PrintInventoryItems(EInventoryViewMode mode, float buybackRate) const
{
	std::cout << "========================================" << std::endl;
	std::string str
		= std::format("            인벤토리 ({}/{})            ", inventoryCount, inventorySize);
	std::cout << str << std::endl;
	std::cout << "========================================" << std::endl;

	for (int index = 0; index < inventoryCount; index++)
	{
		std::string info{};
		std::string itemInfo{};
		//std::string itemName = items[index].item->GetName();
		std::string itemName = items[index].itemData.name;
		int itemCount = items[index].count;

		if (mode == EInventoryViewMode::Normal)
		{
			itemInfo = std::format("{} x{}", itemName, itemCount);
		}
		else if (mode == EInventoryViewMode::Shop)
		{
			//int itemPrice = items[index].item->GetPrice() * buybackRate; // 낮춘 가격으로 판매 가능
			int itemPrice = int(items[index].itemData.price * buybackRate); // 낮춘 가격으로 판매 가능
			itemInfo = std::format("{} ({}G) x{}", itemName, itemPrice, itemCount);
		}

		info = std::format("{}. {}", index + 1, itemInfo);

		std::cout << info << std::endl;
	}
}

void InventorySystem::HandleNormalInventoryOptions(bool& isEnd)
{
	int number{};
	bool isOk{};

	std::cout << std::endl;
	std::cout << "======= 선택 =======" << std::endl;
	std::cout << "1. 조회" << std::endl;
	std::cout << "2. 정렬 (이름순)" << std::endl;
	std::cout << "3. 정렬 (가격순)" << std::endl;
	std::cout << "4. 정렬 (기능순)" << std::endl;
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
			HandleNormalItemSelection();
			break;
		case 2:
			SortByName();
			ClearScreen();
			break;
		case 3:
			SortByPrice();
			ClearScreen();
			break;
		case 4:
			SortByFunc();
			ClearScreen();
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

void InventorySystem::HandleShopInventoryOptions(float buybackRate, int& totalBuyPrice, bool& isEnd)
{
	int number{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "판매할 아이템 번호 입력(0: 돌아가기): ";
		std::cin >> number;

		isOk = true;

		if (number == 0)
		{
			isEnd = true;
			std::cout << "상점 메뉴로 돌아갑니다." << std::endl;
			ClearScreen();
		}
		else if (1 <= number && number <= inventoryCount)
		{
			HandleShopItemOptions(number - 1, buybackRate, totalBuyPrice);
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void InventorySystem::HandleNormalItemSelection()
{
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
			ClearScreen();
		}
		else if (1 <= number && number <= inventoryCount)
		{
			PrintItemInfo(number - 1);
			HandleNormalItemOptions(number - 1);
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void InventorySystem::PrintItemInfo(int index) const
{
	//std::string name = std::format("이름: {}", items[index].item->GetName());
	//std::string description = std::format("설명: {}", items[index].item->GetDescription());
	//std::string price = std::format("가격: {}G", items[index].item->GetPrice());
	std::string name = std::format("이름: {}", items[index].itemData.name);
	std::string description = std::format("설명: {}", items[index].itemData.description);
	std::string price = std::format("가격: {}G", items[index].itemData.price);
	std::string count = std::format("개수: {}개", GetTotalItemCount(index));

	std::cout << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << name << std::endl;
	std::cout << description << std::endl;
	std::cout << price << std::endl;
	std::cout << count << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

void InventorySystem::HandleNormalItemOptions(int index)
{
	if (items[index].itemData.category == EItemCategory::Material)
	{
		HandleNormalNonUsableItemOptions(index);
	}
	else
	{
		HandleNormalUsableItemOptions(index);
	}
}

void InventorySystem::HandleNormalUsableItemOptions(int index)
{
	int number{};
	bool isOk{};

	std::cout << std::endl;
	std::cout << "======= 선택 =======" << std::endl;
	std::cout << "1. 사용" << std::endl;
	std::cout << "2. 버리기" << std::endl;
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
			UseItem(index);
			ClearScreen();
			break;
		case 2:
			HandleDiscardItem(index);
			break;
		case 0:
			std::cout << "인벤토리 목록으로 돌아갑니다." << std::endl;
			ClearScreen();
			break;
		default:
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}

void InventorySystem::HandleNormalNonUsableItemOptions(int index)
{
	int number{};
	bool isOk{};

	std::cout << std::endl;
	std::cout << "======= 선택 =======" << std::endl;
	std::cout << "1. 버리기" << std::endl;
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
			HandleDiscardItem(index);
			break;
		case 0:
			std::cout << "인벤토리 목록으로 돌아갑니다." << std::endl;
			ClearScreen();
			break;
		default:
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
}

void InventorySystem::HandleShopItemOptions(int index, float buybackRate, int& totalBuyPrice)
{
	int number{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "판매할 아이템 개수 입력(0: 돌아가기): ";
		std::cin >> number;

		isOk = true;

		if (number == 0)
		{
			std::cout << "판매 목록을 조회합니다." << std::endl;
			ClearScreen();
		}
		else if (1 <= number && number <= items[index].count)
		{
			//std::string messages = std::format("{}을(를) {}개 판매했습니다.", items[index].item->GetName(), number);
			std::string messages = std::format("{}을(를) {}개 판매했습니다.", items[index].itemData.name, number);
			std::cout << messages << std::endl;
			//totalBuyPrice += items[index].item->GetPrice() * buybackRate * number;
			totalBuyPrice += int(items[index].itemData.price * buybackRate) * number;
			RemoveItem(index, number);
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 번호입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

void InventorySystem::HandleDiscardItem(int index)
{
	//int itemCount = items[index].count;
	int itemCount = GetTotalItemCount(index);
	int number{};
	bool isOk{};

	while (!isOk)
	{
		std::cout << std::endl;
		std::cout << "버릴 아이템 개수 입력(0: 돌아가기): ";
		std::cin >> number;

		isOk = true;

		if (number == 0)
		{
			std::cout << "다시 선택합니다." << std::endl;
			HandleNormalItemOptions(index);
		}
		else if (1 <= number && number <= itemCount)
		{
			//std::string message = std::format("{}을(를) {}개 버렸습니다.", items[index].item->GetName(), number);
			std::string message = std::format("{}을(를) {}개 버렸습니다.", items[index].itemData.name, number);
			std::cout << message << std::endl;
			RemoveItem(index, number);
			ClearScreen();
		}
		else
		{
			isOk = false;
			std::cout << "잘못된 숫자입니다. 다시 입력해주세요." << std::endl;
		}
	}
}

bool InventorySystem::AddItem(std::string id, int itemCount)
{
	//ItemFactory itemFactory;

	int result = FindItem(id);
	int itemMaxStackCount = ItemDataBase::GetInstance().GetMaxStackCount(id);
	int fullSlotCount{};
	int partiallyFullSlotCount{};

	if (result == -1)
	{
		fullSlotCount = itemCount / itemMaxStackCount;
		partiallyFullSlotCount = itemCount % itemMaxStackCount == 0 ? 0 : 1;

		if (inventoryCount + fullSlotCount + partiallyFullSlotCount <= inventorySize)
		{
			FInventorySlot inventorySlot;
			//inventorySlot.item = std::move(itemFactory.CreateItem(id));
			inventorySlot.itemData = ItemDataBase::GetInstance().GetItemData(id);
			inventorySlot.count = itemMaxStackCount;
			//inventorySlot.maxCount = itemMaxStackCount;

			for (int i = 0; i < fullSlotCount; i++)
			{
				inventoryCount += 1;
				items.push_back(inventorySlot);
			}

			if (partiallyFullSlotCount == 1)
			{
				inventoryCount += 1;
				inventorySlot.count = itemCount % itemMaxStackCount;
				items.push_back(inventorySlot);
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		int count = items[result].count;
		//int maxCount = items[result].maxCount;
		int maxCount = items[result].itemData.maxStackCount;

		if (count + itemCount <= maxCount)
		{
			items[result].count += itemCount;
			
			return true;
		}
		else
		{
			fullSlotCount = (itemCount - (maxCount - count)) / itemMaxStackCount;
			partiallyFullSlotCount = (itemCount - (maxCount - count)) % itemMaxStackCount == 0 ? 0 : 1;

			if (inventoryCount + fullSlotCount + partiallyFullSlotCount <= inventorySize)
			{
				items[result].count = maxCount;

				FInventorySlot inventorySlot;
				//inventorySlot.item = itemFactory.CreateItem(id);
				inventorySlot.itemData = ItemDataBase::GetInstance().GetItemData(id);
				inventorySlot.count = itemMaxStackCount;
				//inventorySlot.maxCount = itemMaxStackCount;

				for (int i = 0; i < fullSlotCount; i++)
				{
					inventoryCount += 1;
					items.push_back(inventorySlot);
				}

				if (partiallyFullSlotCount == 1)
				{
					inventoryCount += 1;
					inventorySlot.count = itemCount % itemMaxStackCount;
					items.push_back(inventorySlot);
				}

				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

bool InventorySystem::RemoveItem(int index, int count)
{
	if (index < 0 || inventoryCount <= index)
	{
		return false;
	}

	int result = GetTotalItemCount(index);
	
	if (count <= result)
	{
		//std::string itemId = items[index].item->GetId();
		std::string itemId = items[index].itemData.id;
		int left = count;
		int slotIndex = index;
		int number{};

		while (left != 0)
		{
			number = std::min(left, items[slotIndex].count);
			left -= number;
			items[slotIndex].count -= number;

			if (items[slotIndex].count == 0)
			{
				inventoryCount -= 1;
				items.erase(items.begin() + slotIndex);
			}

			slotIndex = FindItem(itemId);
		}

		return true;
	}
	
	return false;
}

int InventorySystem::FindItem(std::string id) const
{
	int index = -1;
	int minNum = ItemDataBase::GetInstance().GetMaxStackCount(id) + 1;

	for (int i = 0; i < inventoryCount; i++)
	{
		//if (items[i].item->GetId() == id)
		if (items[i].itemData.id == id)
		{
			if (items[i].count < minNum)
			{
				index = i;
				minNum = items[i].count;
			}
		}
	}

	return index;
}

int InventorySystem::GetTotalItemCount(int index) const
{
	//std::string itemId = items[index].item->GetId();
	std::string itemId = items[index].itemData.id;
	int total{};

	for (int i = 0; i < inventoryCount; i++)
	{
		//if (items[i].item->GetId() == itemId)
		if (items[i].itemData.id == itemId)
		{
			total += items[i].count;
		}
	}

	return total;
}

bool InventorySystem::UseItem(int index)
{
	if (index < 0 || inventoryCount <= index)
	{
		return false;
	}

	ItemFactory itemFactory;
	//std::string itemId = items[index].item->GetId();
	//EItemCategory itemCategory = items[index].item->GetCategory();
	std::string itemId = items[index].itemData.id;
	EItemCategory itemCategory = items[index].itemData.category;

	switch (itemCategory)
	{
	case EItemCategory::Consumable:
		itemFactory.CreateConsumableItem(itemId)->Use();
		break;
	case EItemCategory::Upgrade:
		itemFactory.CreateUpgradeItem(itemId)->Use();
		break;
	//case EItemCategory::Material:
		//itemFactory.CreateMaterialItem(itemId)->Use();
		//break;
	}
	
	RemoveItem(index);

	return true;
}

void InventorySystem::SortByName()
{
	std::sort(items.begin(), items.end(), compareName);
	MergeSameItems();
}

void InventorySystem::SortByPrice()
{
	std::sort(items.begin(), items.end(), comparePrice);
	MergeSameItems();
}

void InventorySystem::SortByFunc()
{
	std::sort(items.begin(), items.end(), compareFunc);
	MergeSameItems();
}

void InventorySystem::MergeSameItems()
{
	// 정렬 후를 전제로 함
	std::vector<FInventorySlot> newItems{};
	std::string prevId{};
	int newInventoryCount{};
	int totalCount{};
	int fullSlot{};
	int remainder{};
	int itemMaxStackCount{};

	for (int i = 0; i < inventoryCount; i++)
	{
		if (items[i].itemData.id != prevId)
		{
			prevId = items[i].itemData.id;
			totalCount = GetTotalItemCount(i);
			itemMaxStackCount = items[i].itemData.maxStackCount;
			fullSlot = totalCount / itemMaxStackCount;
			remainder = totalCount % itemMaxStackCount;

			std::cout << fullSlot << " " << remainder << std::endl;
			
			FInventorySlot inventorySlot;
			inventorySlot.itemData = items[i].itemData;
			inventorySlot.count = itemMaxStackCount;

			for (int j = 0; j < fullSlot; j++)
			{
				newInventoryCount += 1;
				newItems.push_back(inventorySlot);
			}

			if (remainder != 0)
			{
				newInventoryCount += 1;
				inventorySlot.count = remainder;
				newItems.push_back(inventorySlot);
			}
		}
	}

	items = newItems;
	inventoryCount = newInventoryCount;
}
