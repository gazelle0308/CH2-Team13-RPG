#pragma once

#include <iostream>
#include <format>
#include <string>

#include "Types/ItemTypes.h"
#include "DataBase/ItemDataBase.h"

class Item
{
protected:
	FItemData itemData;

public:
	Item(std::string id) {
		SetItemData(id);
	}

	virtual void Use() = 0; // Player 인자 넣기
	virtual void PrintUseMessage() const;

	void SetItemData(std::string id);

	const FItemData& GetItemData() const;
	const std::string GetId() const;
	const EItemCategory GetCategory() const;
	const std::string GetName() const;
	const std::string GetDescription() const;
	const int GetPrice() const;
	const int GetMaxStackCount() const;
};

