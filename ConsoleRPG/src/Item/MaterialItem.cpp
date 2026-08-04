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
	ItemDataBase::GetInstance().GetMaterialData(id, materialItemData);
}

const FMaterialItemData& MaterialItem::GetMaterialData() const
{
	return materialItemData;
}

EMaterialType MaterialItem::GetMaterialType() const
{
	return materialItemData.GetMaterialType();
}
