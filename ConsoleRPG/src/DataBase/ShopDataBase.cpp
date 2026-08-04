#include "DataBase/ShopDataBase.h"

void ShopDataBase::LoadShopData()
{
	ItemDataBase& itemDataBase = ItemDataBase::GetInstance();

	std::ifstream file("data/shopItems.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패" << std::endl;
		return;
	}

	nlohmann::json data;
	file >> data;

	std::string id = "ID";
	bool defaultUnlocked = false;
	bool hasStockLimit = false;
	int initialCount = 0;
	int index{};

	for (const auto& item : data)
	{
		FShopItemData shopItemData;
		FShopSlot shopSlot;
		FItemData itemData;

		shopItemData.SetId(item["id"]);
		shopItemData.SetDefaultUnlocked(item["defaultUnlocked"]);
		shopItemData.SetHasStockLimit(item["hasStockLimit"]);
		shopItemData.SetInitialCount(item["initialCount"]);

		shopItemDatas.push_back(shopItemData);

		if (!itemDataBase.GetItemData(shopItemData.GetId(), itemData))
		{
			continue;
		}

		shopSlot.SetItemData(itemData);
		shopSlot.SetIsUnlocked(shopItemData.GetDefaultUnlocked());
		shopSlot.SetHasStockLimit(shopItemData.GetHasStockLimit());
		shopSlot.SetCurrentCount(shopItemData.GetInitialCount());

		shopSlots.push_back(shopSlot);

		shopSlotIndexMap.emplace(shopSlot.GetId(), index);
		index += 1;
	}
}

void ShopDataBase::PrintAllShopDatas() const
{
	for (const FShopItemData& item : shopItemDatas)
	{
		std::cout << std::format("id: {}", item.GetId()) << std::endl;
		std::cout << std::format("defaultUnlocked: {}", item.GetDefaultUnlocked()) << std::endl;
		std::cout << std::format("hasStockLimit: {}", item.GetHasStockLimit()) << std::endl;
		std::cout << std::format("initialCount: {}", item.GetInitialCount()) << std::endl;
	}
}

void ShopDataBase::SetShopItemUnlocked(std::string id, bool isUnlocked)
{
	if (!shopSlotIndexMap.contains(id))
	{
		return;
	}

	int index = shopSlotIndexMap.at(id);

	if ((int)shopSlots.size() <= index)
	{
		return;
	}

	shopSlots[index].SetIsUnlocked(isUnlocked);
}

const std::vector<FShopItemData>& ShopDataBase::GetShopItemDatas() const
{
	return shopItemDatas;
}

std::vector<FShopSlot>* ShopDataBase::GetShopSlots()
{
	return &shopSlots;
}

std::vector<FShopSlot*>* ShopDataBase::GetSellableShopSlots()
{
	sellableShopSlots.clear();

	for (FShopSlot& slot : shopSlots)
	{
		if (slot.GetIsUnlocked() 
			&& (!slot.GetHasStockLimit() 
				|| slot.GetHasStockLimit() && 0 < slot.GetCurrentCount()))
		{
			sellableShopSlots.push_back(&slot);
		}
	}

	return &sellableShopSlots;
}
