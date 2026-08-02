#include "Item/ConsumableItem.h"

void ConsumableItem::Use()
{
	PrintUseMessage();
	
	// Player stat change
	for (const FConsumableEffect& effect : consumableItemData.effects)
	{
		switch (effect.consumableType)
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
}

void ConsumableItem::PrintUseMessage() const
{
	Item::PrintUseMessage();

	FEnumDisplay enumDisplay;

	for (const FConsumableEffect& effect : consumableItemData.effects)
	{
		std::string displayName = enumDisplay.GetConsumableTypeDisplayName(effect.consumableType);
		std::string message = std::format("{}이(가) {} 증가했습니다.", displayName, effect.value);
		std::cout << message << std::endl;
		// AddLog(message);
	}
}

void ConsumableItem::SetConsumableData(std::string id)
{
	consumableItemData = ItemDataBase::GetInstance().GetConsumableData(id);
}

const FConsumableItemData& ConsumableItem::GetConsumableData() const
{
	return consumableItemData;
}

const std::vector<FConsumableEffect>& ConsumableItem::GetConsumableEffects() const
{
	return consumableItemData.effects;
}

const std::vector<EConsumableType>& ConsumableItem::GetConsumableTypes() const
{
	std::vector<EConsumableType> consumableTypes{};

	for (const FConsumableEffect& effect : consumableItemData.effects)
	{
		consumableTypes.push_back(effect.consumableType);
	}

	return consumableTypes;
}