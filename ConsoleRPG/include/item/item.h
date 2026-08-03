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

	virtual void Use() = 0;

protected:
	virtual void PrintUseMessage() const;
	void SetItemData(std::string id);

public:
	const FItemData& GetItemData() const;
	std::string GetId() const;
	EItemCategory GetCategory() const;
	std::string GetName() const;
	std::string GetDescription() const;
	int GetPrice() const;
	int GetMaxStackCount() const;
};

