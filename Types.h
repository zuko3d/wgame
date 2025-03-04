#pragma once

#include <array>

#include "FlatMap.h"
#include "ResizableArray.h"
#include "Resources.h"

// =================================================================
// Boss
// =================================================================

enum class BossAbility {
    Deadly,
    AoePoison,
    DestructWeapon,
    LessLoot,
    AoeDamage,
    Curse,
    NoConquer,

    MoreLoot,
    None,
};

enum class ProfessionTrigger {
    CraftDiscount2,
    SellX2,
    None,
};

struct Boss {
    int power;
    ResizableArray<BossAbility, 10> abilities;

    std::array<IncomableResources, 3> rewardedResources; // per-place
    ResizableArray<BossAbility, 3> rewardedTrinkets; // 1st place only
    
    // ProfessionTrigger profTrigger = ProfessionTrigger::None;

    int picIdx;
};

// =================================================================
// Equipment
// =================================================================

enum class CraftedItemType {
    Weapon,
    Armor,
    Tool,
    Consumable,
    None,
};

struct CraftedItem {
    CraftedItemType type = CraftedItemType::None;
    int power = 0;
    int sellPrice = 0;
    int resourcesCost = 0;
    int slots = 0;

    IncomableResources toolResourcesFromBoss;

    int picIdx = 0;
};

struct CraftedItemOnTable {
    const CraftedItem* origin = nullptr;
    ResizableArray<BossAbility, 4> slottedTrinkets;

    // int attachedToCharIdx; // partyIdx * 10 + charIdx
};

// ==================================================================================================================================
// Adventurer
// ==================================================================================================================================

enum class AdventurerRole {
    Tank,
    DPS,
    Support,
    None,
};

struct Adventurer {
    int power;
    ResizableArray<BossAbility, 10> abilities;
    AdventurerRole role;

    int picIdx;
};

struct AdventurerOnField {
    const Adventurer* origin;
    CraftedItemOnTable equippedItem;
    
    bool isAlive;
    // int power;
    // ResizableArray<BossAbility, 10> abilities;

    int partyIdx;
};

struct Party {
    ResizableArray<AdventurerOnField, 6> adventurers;
    ResizableArray<CraftedItemOnTable, 10> spareItems;
};

// --------------------------------------------------------------------------------------------------------------------------------
// Cradftsmen ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------

enum class Profession {
    Miner,
    Trader,
    Inventor, // fuse resources
    Tanner, // tools and low-tier armor
    Alchemist,
    Blacksmith, // weapons and high-tier armor
    Recruiter,
    Commander,
    None,
};

using ActionType = Profession;

enum class CraftsmanColor {
    Red,
    Blue,
    Green,
    Yellow,
    Purple,
    None,
};

// triggered or activated
enum class CraftsmanAbilityType {
    GiveResource,
    UpgradeResource,
    CraftBlacksmith,
    CraftTanner,
    CraftAlchemy,
    Trade,
    Hire,
    Attack,
    None,
};

struct CraftsmanAbility {
    CraftsmanAbilityType type = CraftsmanAbilityType::None;
    int param1 = -1;
    int param2 = -1;
};

enum class CraftsmanStaticAbility {
    DoesntTapWhenTriggered,
    ProduceExtraResource,
    Discount1ForCraft,
    None,
};

struct CraftsmanCard {
    CraftsmanColor ownColor = CraftsmanColor::None;
    CraftsmanColor proccedColor = CraftsmanColor::None;
    Profession profession = Profession::None;

    CraftsmanAbility basicAbility;
    CraftsmanAbility triggeredAbility;
    CraftsmanStaticAbility staticAbility = CraftsmanStaticAbility::None;

    int picIdx = -1;
    int idx = -1;
};

struct Preset {
    std::vector<const CraftsmanCard*> cardOrigins;
    std::array<int, 7> boundCardOrigins;
};
// struct CraftsmanOnField {
//     CraftsmanCard origin;

//     bool isTapped; // tapped when we use his triggered ability, not when we use HIM
// };

// --------------------------------------------------------------------------------------------------------------------------------
// Actions ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------

// struct MayorOrder {
//     ResizableArray<ActionType, 4> action;
// };

struct Action {
    Profession action;
    int param1 = -1;
    int param2 = -1;
};

struct ActionFromHand {
    int cardIdx;
    Action action;
};

enum class LogEventType : uint8_t {
    BuildPalace, // 0
    GetTech, // 1
    GetInnovation, // 2
    Market, // 3
    BookMarket, // 4
    GetFedTile, // 5
    BuildMine, // 6
    UpgradeNav, // 7
    UpgradeTerraformTo3,  // 8
    GetBooster, // 9
    UpgradeBuilding, // 10
    Annex, // 11
    Terraform, // 12
    None,
};

struct LogEvent {
    int round;
    int activePlayer;
    LogEventType type;
    int param;
};

// --------------------------------------------------------------------------------------------------------------------------------
// Technology ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// --------------------------------------------------------------------------------------------------------------------------------

enum class TechnologyBonusType {
    ResourceIncome,
    GoldIncome,
    CraftingCost,
    SellGoldCost,

    None,
};

struct TechnologyBonus {
    TechnologyBonusType type;
    int param;
};

struct Technology {
    TechnologyBonus bonus;
    ResourceGrade grade;
};

struct NewGameParams {
    uint32_t seed;
    std::array<int, 2> isHuman;
    std::array<int, 2> usedPresetIdx;
};
