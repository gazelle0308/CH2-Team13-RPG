#include "Item/MaterialItem.h"

void MaterialItem::Use()
{
	PrintUseMessage();
}

void MaterialItem::PrintUseMessage() const
{
	Item::PrintUseMessage();
}

void MaterialItem::SetMaterialData(std::string id)
{
	materialItemData = ItemDataBase::GetInstance().GetMaterialData(id);
}

const FMaterialItemData& MaterialItem::GetMaterialData() const
{
	return materialItemData;
}

const EMaterialType MaterialItem::GetMaterialType() const
{
	return materialItemData.materialType;
}
