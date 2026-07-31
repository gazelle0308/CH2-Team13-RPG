#include "Factory/ItemFactory.h"

std::unique_ptr<ConsumableItem> ItemFactory::CreateConsumableItem(std::string id) const
{
    std::unique_ptr<ConsumableItem> itemPtr = std::make_unique<ConsumableItem>(id);

    return itemPtr;
}

std::unique_ptr<UpgradeItem> ItemFactory::CreateUpgradeItem(std::string id) const
{
    std::unique_ptr<UpgradeItem> itemPtr = std::make_unique<UpgradeItem>(id);

    return itemPtr;
}

std::unique_ptr<MaterialItem> ItemFactory::CreateMaterialItem(std::string id) const
{
    std::unique_ptr<MaterialItem> itemPtr = std::make_unique<MaterialItem>(id);

    return itemPtr;
}
