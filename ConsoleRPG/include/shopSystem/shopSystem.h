#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include "Types/ShopTypes.h"
#include "DataBase/ShopDataBase.h"
#include "Player/Player.h"

class InventorySystem;

class ShopSystem
{
private:
	std::vector<FShopSlot*>* shopItems;
	double buybackRate = 0.6;

private:
	ShopSystem() : buybackRate(0.6) {
		SetShopData();
	}

	// 복사 방지
	ShopSystem(const ShopSystem&) = delete;
	ShopSystem& operator=(const ShopSystem&) = delete;

	// 이동 방지
	ShopSystem(ShopSystem&&) = delete;
	ShopSystem& operator=(ShopSystem&&) = delete;

public:
	// 싱글톤
	static ShopSystem& GetInstance() {
		static ShopSystem instance;
		return instance;
	}

	void ShowShop();

private:
	void SetShopData();

	void ClearScreen() const;
	void HandleShopOptions(bool& isEnd);
	void HandleSell();
	void PrintShopItems() const;
	void PrintPlayerGold() const;
	void HandleSellOptions(bool& isEnd);
	void HandleBuy() const;
	void HandleShowItem();
	void PrintItemInfo(int index) const;
	void HandleSellItemSelection();
	void HandleSellItemCount(int index);

	bool SellToPlayer(int index, int count, int price);
	void BuyFromPlayer(int totalBuyPrice) const;
};

