#include "Item/Item.h"

void Item::PrintUseMessage() const
{
	std::string message = std::format("{}을(를) 사용했습니다.", itemData.name);
	std::cout << message << std::endl;
	// AddLog(message);
}

void Item::SetItemData(std::string id)
{
	itemData = ItemDataBase::GetInstance().GetItemData(id);
}

const FItemData& Item::GetItemData() const
{
	return itemData;
}

const std::string Item::GetId() const
{
	return itemData.id;
}

const EItemCategory Item::GetCategory() const
{
	return itemData.category;
}

const std::string Item::GetName() const
{
	return itemData.name;
}

const std::string Item::GetDescription() const
{
	return itemData.description;
}

const int Item::GetPrice() const
{
	return itemData.price;
}

const int Item::GetMaxStackCount() const
{
	return itemData.maxStackCount;
}
