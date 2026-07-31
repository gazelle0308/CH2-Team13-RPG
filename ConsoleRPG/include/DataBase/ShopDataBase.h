#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include "Types/ItemTypes.h"
#include "Types/ShopTypes.h"
#include "DataBase/ItemDataBase.h"

class ShopDataBase
{
private:
	std::vector<FShopItemData> shopItemDatas;
	std::unordered_map<std::string, FItemData> shopItemDataMap;

public:
	ShopDataBase() {
		LoadShopData();
	}

	// 복사 방지
	ShopDataBase(const ShopDataBase&) = delete;
	ShopDataBase& operator=(const ShopDataBase&) = delete;

	// 이동 방지
	ShopDataBase(ShopDataBase&&) = delete;
	ShopDataBase& operator=(ShopDataBase&&) = delete;

	void LoadShopData();

public:
	// 싱글톤
	static ShopDataBase& GetInstance() {
		static ShopDataBase instance;
		return instance;
	}

	void PrintAllShopDatas() const;

	const std::vector<FShopItemData>& GetShopItemDatas() const;
	const FItemData& GetShopItemData(std::string id) const;
};

