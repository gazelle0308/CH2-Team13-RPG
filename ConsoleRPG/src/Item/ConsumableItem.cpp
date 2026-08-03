#include "Item/ConsumableItem.h"

void ConsumableItem::Use()
{
	PrintUseMessage();
	
	Player& player = Player::GetInstance();

	// Player stat change
	for (const FConsumableEffect& effect : consumableItemData.GetConsumableEffects())
	{
		switch (effect.GetConsumableType())
		{
		case EConsumableType::Hp:
			std::cout << "hp" << std::endl;

			player.ApplyEffect(Pstat::Hp, effect.GetValue());
			break;
		case EConsumableType::Mp:
			std::cout << "mp" << std::endl;

			player.ApplyEffect(Pstat::Mp, effect.GetValue());
			break;
		case EConsumableType::Power:
			std::cout << "power" << std::endl;

			player.ApplyEffect(Pstat::BuffPower, effect.GetValue());
			break;
		case EConsumableType::Defence:
			std::cout << "defence" << std::endl;

			player.ApplyEffect(Pstat::BuffDefence, effect.GetValue());
			break;
		}
	}
}

void ConsumableItem::PrintUseMessage() const
{
	Item::PrintUseMessage();

	FEnumDisplay enumDisplay;

	for (const FConsumableEffect& effect : consumableItemData.GetConsumableEffects())
	{
		std::string displayName = enumDisplay.GetConsumableTypeDisplayName(effect.GetConsumableType());
		std::string message = std::format("{}이(가) {} 증가했습니다.", displayName, effect.GetValue());
		std::cout << message << std::endl;
		// AddLog(message);
	}
}

void ConsumableItem::SetConsumableData(std::string id)
{
	ItemDataBase::GetInstance().GetConsumableData(id, consumableItemData);
}

const FConsumableItemData& ConsumableItem::GetConsumableData() const
{
	return consumableItemData;
}

const std::vector<FConsumableEffect>& ConsumableItem::GetConsumableEffects() const
{
	return consumableItemData.GetConsumableEffects();
}

const std::vector<EConsumableType>& ConsumableItem::GetConsumableTypes() const
{
	static std::vector<EConsumableType> consumableTypes{};
	
	if (consumableTypes.empty())
	{
		for (const FConsumableEffect& effect : consumableItemData.GetConsumableEffects())
		{
			consumableTypes.push_back(effect.GetConsumableType());
		}
	}

	return consumableTypes;
}