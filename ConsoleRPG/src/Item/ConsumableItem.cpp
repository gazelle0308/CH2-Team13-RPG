#include "Item/ConsumableItem.h"

void ConsumableItem::Use()
{
	PrintUseMessage();
	
	// Player stat change
	switch (consumableItemData.consumableType)
	{
	case EConsumableType::Hp:
		// hp
		break;
	case EConsumableType::Mp:
		// mp
		break;
	case EConsumableType::Power:
		// power
		break;
	case EConsumableType::Defence:
		// defence
		break;
	}
}

void ConsumableItem::PrintUseMessage() const
{
	Item::PrintUseMessage();

	FEnumDisplay enumDisplay;
	std::string displayName = enumDisplay.GetConsumableTypeDisplayName(consumableItemData.consumableType);
	std::string message = std::format("{}이(가) {} 증가했습니다.", displayName, consumableItemData.value);

	// AddLog(message);
}

void ConsumableItem::SetConsumableData(std::string id)
{
	ItemDataBase itemDataBase;
	consumableItemData = itemDataBase.GetConsumableData(id);
}

const FConsumableItemData& ConsumableItem::GetConsumableData() const
{
	return consumableItemData;
}

const EConsumableType ConsumableItem::GetConsumableType() const
{
	return consumableItemData.consumableType;
}

const int ConsumableItem::GetValue() const
{
	return consumableItemData.value;
}
