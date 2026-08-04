  // Copyright 2026 ShinStella

#pragma once

#include <vector>
#include <string>
#include <unordered_map>

class ItemDataBase;

enum class EItemCategory {
    None,
    Consumable,  // 소비 아이템
    Upgrade,  // 인벤토리 업그레이드
    Material,  // 몬스터 드랍 아이템
};

enum class EConsumableType {
    None,
    Hp,
    Mp,
    Power,
    Defence,
};

enum class EUpgradeType {
    None,
    Inventory,
};

enum class EMaterialType {
    None,
    Primary,
    Secondary,
};

// ==========================================================================================//

struct FItemData {
 public:
    std::string id = "ITEM";
    EItemCategory category = EItemCategory::None;
    std::string name = "item";
    std::string description = "description";
    int price = 0;
    int maxStackCount = 0;

 public:
    void SetId(std::string id_) {
        id = id_;
    }
    void SetCategory(EItemCategory category_) {
        category = category_;
    }
    void SetName(std::string name_) {
        name = name_;
    }
    void SetDescription(std::string description_)  {
        description = description_;
    }
    void SetPrice(int price_) {
        price = price_;
    }
    void SetMaxStackCount(int maxStackCount_) {
        maxStackCount = maxStackCount_;
    }

    std::string GetId() const {
        return id;
    }
    EItemCategory GetCategory() const {
        return category;
    }
    std::string GetName() const {
        return name;
    }
    std::string GetDescription() const {
        return description;
    }
    int GetPrice() const {
        return price;
    }
    int GetMaxStackCount() const {
        return maxStackCount;
    }
};

struct FConsumableEffect {
 public:
    EConsumableType consumableType = EConsumableType::None;
    int value = 0;

 public:
    void SetConsumableType(EConsumableType consumableType_) {
        consumableType = consumableType_;
    }
    void SetValue(int value_) {
        value = value_;
    }

    EConsumableType GetConsumableType() const {
        return consumableType;
    }
    int GetValue() const {
        return value;
    }
};

struct FConsumableItemData {
 public:
    std::string id = "ITEM";
    std::vector<FConsumableEffect> effects;

 public:
    void SetId(std::string id_) {
        id = id_;
    }
    void SetEffects(const std::vector<FConsumableEffect>& effects_) {
        effects = effects_;
    }

    std::string GetId() const {
        return id;
    }
    const std::vector<FConsumableEffect>& GetConsumableEffects() const {
        return effects;
    }
    const std::vector<EConsumableType>& GetConsumableTypes() const {
        std::vector<EConsumableType> consumableTypes{};

        for (const FConsumableEffect& effect : effects) {
            consumableTypes.push_back(effect.consumableType);
        }

        return consumableTypes;
    }
};

struct FUpgradeItemData {
 public:
    std::string id = "ITEM";
    EUpgradeType upgradeType = EUpgradeType::None;
    int value = 0;

 public:
    void SetId(std::string id_) {
        id = id_;
    }
    void SetUpgradeType(EUpgradeType upgradeType_) {
        upgradeType = upgradeType_;
    }
    void SetValue(int value_) {
        value = value_;
    }

    std::string GetId() const {
        return id;
    }
    EUpgradeType GetUpgradeType() const {
        return upgradeType;
    }
    int GetValue() const {
        return value;
    }
};

struct FMaterialItemData {
 public:
    std::string id = "ITEM";
    EMaterialType materialType = EMaterialType::None;

 public:
    void SetId(std::string id_) {
        id = id_;
    }
    void SetMaterialType(EMaterialType materialType_) {
        materialType = materialType_;
    }

    std::string GetId() const {
        return id;
    }
    EMaterialType GetMaterialType() const {
        return materialType;
    }
};

// ==========================================================================================//

struct FEnumDisplay {
 private:
    // Item
    std::unordered_map<EItemCategory, std::string>
            itemCategoryToStringMap = {
                {EItemCategory::None, "None"},
                {EItemCategory::Consumable, "Consumable"},
                {EItemCategory::Upgrade, "Upgrade"},
                {EItemCategory::Material, "Material"},
            };
    std::unordered_map<std::string, EItemCategory>
            itemCategoryToEnumMap = {
                {"None", EItemCategory::None},
                {"Consumable", EItemCategory::Consumable},
                {"Upgrade", EItemCategory::Upgrade},
                {"Material", EItemCategory::Material},
            };
    std::unordered_map<EItemCategory, std::string>
            itemCategoryDisplayNameMap = {
                {EItemCategory::None, ""},
                {EItemCategory::Consumable, "소비"},
                {EItemCategory::Upgrade, "강화"},
                {EItemCategory::Material, "기타"},
            };

    // Consumable
    std::unordered_map<EConsumableType, std::string>
            consumableToStringMap = {
                {EConsumableType::None, "None"},
                {EConsumableType::Hp, "Hp"},
                {EConsumableType::Mp, "Mp"},
                {EConsumableType::Power, "Power"},
                {EConsumableType::Defence, "Defence"}
            };
    std::unordered_map<std::string, EConsumableType>
            consumableToEnumMap = {
                {"None", EConsumableType::None},
                {"Hp", EConsumableType::Hp},
                {"Mp", EConsumableType::Mp},
                {"Power", EConsumableType::Power},
                {"Defence", EConsumableType::Defence}
    };
    std::unordered_map<EConsumableType, std::string>
            consumableDisplayNameMap = {
                {EConsumableType::None, ""},
                {EConsumableType::Hp, "체력"},
                {EConsumableType::Mp, "마력"},
                {EConsumableType::Power, "공격력"},
                {EConsumableType::Defence, "방어력"}
            };

    // Upgrade
    std::unordered_map<EUpgradeType, std::string>
            upgradeToStringMap = {
                {EUpgradeType::None, "None"},
                {EUpgradeType::Inventory, "Inventory"}
            };
    std::unordered_map<std::string, EUpgradeType>
            upgradeToEnumMap = {
                {"None", EUpgradeType::None},
                {"Inventory", EUpgradeType::Inventory}
            };
    std::unordered_map<EUpgradeType, std::string>
            upgradeDisplayNameMap = {
                {EUpgradeType::None, ""},
                {EUpgradeType::Inventory, "인벤토리"}
            };

    // Material
    std::unordered_map<EMaterialType, std::string>
            materialToStringMap = {
                {EMaterialType::None, "None"},
                {EMaterialType::Primary, "Primary"},
                {EMaterialType::Secondary, "Secondary"}
            };
    std::unordered_map<std::string, EMaterialType>
            materialToEnumMap = {
                {"None", EMaterialType::None},
                {"Primary", EMaterialType::Primary},
                {"Secondary", EMaterialType::Secondary}
            };
    std::unordered_map<EMaterialType, std::string>
            materialDisplayNameMap = {
                {EMaterialType::None, ""},
                {EMaterialType::Primary, "원재료"},
                {EMaterialType::Secondary, "부재료"}
            };

 public:
    // Item
    inline std::string GetItemCategoryToString(
                        EItemCategory itemCategory) const {
                            return itemCategoryToStringMap.at(itemCategory);
                        }
    inline bool GetItemCategoryToEnum(
                    std::string str,
                    EItemCategory& itemCategory) const {
                        if (itemCategoryToEnumMap.contains(str)) {
                            itemCategory = itemCategoryToEnumMap.at(str);

                            return true;
                        }

        return false;
    }
    inline std::string GetItemCategoryDisplayName(
                        EItemCategory itemCategory) const {
                            return itemCategoryDisplayNameMap.at(itemCategory);
                        }

    // Consumable
    inline std::string GetConsumableTypeToString(
                        EConsumableType consumableType) const {
                            return consumableToStringMap.at(consumableType);
                        }
    inline bool GetConsumableTypeToEnum(
                    std::string str,
                    EConsumableType& consumableType) const {
                        if (consumableToEnumMap.contains(str)) {
                            consumableType = consumableToEnumMap.at(str);

                            return true;
                    }

        return false;
    }
    inline std::string GetConsumableTypeDisplayName(
                        EConsumableType consumableType) const {
                            return consumableDisplayNameMap.at(consumableType);
                        }

    // Upgrade
    inline std::string GetUpgradeTypeToString(
                            EUpgradeType upgradeType) const {
                                return upgradeToStringMap.at(upgradeType);
                            }
    inline bool GetUpgradeTypeToEnum(
                    std::string str,
                    EUpgradeType& upgradeType) const {
                        if (upgradeToEnumMap.contains(str)) {
                            upgradeType = upgradeToEnumMap.at(str);

                            return true;
                    }

        return false;
    }
    inline std::string GetUpgradeTypeDisplayName(
                            EUpgradeType upgradeType) const {
                                return upgradeDisplayNameMap.at(upgradeType);
                            }

    // Material
    inline std::string GetMaterialTypeToString(
                            EMaterialType materialType) const {
                                return materialToStringMap.at(materialType);
                            }
    inline bool GetMaterialTypeToEnum(
                    std::string str,
                    EMaterialType& materialType) const {
                    if (materialToEnumMap.contains(str)) {
                        materialType = materialToEnumMap.at(str);

                        return true;
                    }

        return false;
    }
    inline std::string
        GetMaterialTypeDisplayName(EMaterialType materialType) const {
            return materialDisplayNameMap.at(materialType);
        }
};
