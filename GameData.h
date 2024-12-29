#pragma once

#include "FlatMap.h"
#include "Types.h"
#include "Field.h"

#include <vector>
#include <unordered_map>

struct GameData {
    ResizableArray<ResourceOrigin, 12> resourceOrigins;
    std::vector<Boss> bosses;
    std::vector<std::vector<Boss>> bossesByGrade;

    std::vector<Adventurer> adventurers;
    std::vector<CraftedItem> craftedItems;
    std::vector<CraftsmanCard> craftsmen;
    std::unordered_map<Profession, std::vector<const CraftsmanCard*>> craftsmenByProfession;
    std::vector<Preset> presets;
    std::vector<FieldHex> hexes;

    FieldOrigin fieldOrigin;

    // There might be some presets
    std::array<ActionType, 7> startingBoundActions; // None for non-bound actions
};

GameData createBasicData();