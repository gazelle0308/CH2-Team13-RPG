#include "DataBase/ShopDataBase.h"

void ShopDataBase::LoadShopData()
{
	std::ifstream file("data/shopItems.json");

	if (!file.is_open())
	{
		std::cout << "파일 열기 실패" << std::endl;
		return;
	}

	nlohmann::json data;
	file >> data;

	for (const auto& item : data)
	{
		FShopItemData shopItemData;

		shopItemData.SetId(item["id"]);
		shopItemData.SetCount(item["count"]);

		shopItemDatas.push_back(shopItemData);
	}
}

void ShopDataBase::PrintAllShopDatas() const
{
	for (const FShopItemData& item : shopItemDatas)
	{
		std::cout << std::format("id: {}", item.GetId()) << std::endl;
		std::cout << std::format("count: {}", item.GetCount()) << std::endl;
	}
}

const std::vector<FShopItemData>& ShopDataBase::GetShopItemDatas() const
{
	return shopItemDatas;
}