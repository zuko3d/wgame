#include "GameData.h"

#include <cmath>

GameData createBasicData(std::default_random_engine& rng) {
    GameData ret;

    ret.fieldOrigin.init();

    for (int i = 0; i < ret.fieldOrigin.neibs.size() * 2; i++) {
        int grade = rng() % SC(ResourceGrade::None);
        FieldHex hex{
                .bonus = FieldHexBonus{
                    .type = static_cast<FieldHexBonusType>(rng() % SC(FieldHexBonusType::None)),
                    .param = grade
                },
                .grade = static_cast<ResourceGrade>(grade)
            };

        ret.hexes.push_back(hex);
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) {
            ret.resourceOrigins.push_back(ResourceOrigin{
                .tier = ResourceGrade{j},
                .sellPrice = j * 2 + i,
            });
        }
    }

    const auto randomBossAbility = [&] () { return static_cast<BossAbility>(rng() % SC(BossAbility::None)); };
    
    // Add bosses
    for (int i = 0; i < 100; i++) {
        Boss boss;

        const int n = rng() % 5;
        for (int j = 0; j < n; j++) {
            boss.abilities.push_back(randomBossAbility());
        }
        
        boss.power = rng() % 50 + 1;
        int bossWorth = boss.power + boss.abilities.size() * 4;

        IncomableResources rewardedResources;
        const int nResources = rng() % 4;
        std::vector<int> resourceTypes;
        for (int j = 0; j < nResources; j++) {
            const int type = rng() % ret.resourceOrigins.size();
            resourceTypes.push_back(type);
        }

        for (int place = 0; place < boss.rewardedResources.size(); place++) {
            auto& p = boss.rewardedResources.at(place);
            int gold = bossWorth / (place + 1);
            for (const auto& rtype: resourceTypes) {
                gold -= ret.resourceOrigins[rtype].sellPrice;
                p.resources[rtype]++;
            }
            if (gold > 0) p.gold = gold;
            resourceTypes.pop_back();
        }
        
        const int nTrinkets = rng() % 3;
        for (int i = 0; i < nTrinkets; i++) {
            boss.rewardedTrinkets.push_back(randomBossAbility());
        }

        boss.picIdx = ret.bosses.size();

        ret.bosses.push_back(boss);
    }

    for (int i = 0; i < 50; i++) {
        Adventurer adventurer;

        adventurer.role = (AdventurerRole) (rng() % SC(AdventurerRole::None));
        if (adventurer.role == AdventurerRole::Tank) {
            adventurer.power = 3 + rng() % 3;
            if (rng() % 2) adventurer.abilities.push_back(randomBossAbility());
        } else if (adventurer.role == AdventurerRole::Support) {
            adventurer.power = 2 + rng() % 2;
            int nAbilities = rng() % 3 + 2;
            for (int j = 0; j < nAbilities; j++) {
                adventurer.abilities.push_back(randomBossAbility());
            }
        } else {
            adventurer.power = 6 + rng() % 5;
        }

        adventurer.picIdx = ret.adventurers.size();

        ret.adventurers.push_back(adventurer);
    }

    int nItems = 50;
    for (int i = 0; i < nItems; i++) {
        CraftedItem item;
        item.type = (CraftedItemType) (rng() % SC(CraftedItemType::None));
        item.picIdx = ret.craftedItems.size();
        item.resourcesCost = 2 + (rng()  % 8);

        item.sellPrice = 0;
        for (int j = 0; j < item.resourcesCost; j++) {
            item.sellPrice += ret.resourceOrigins[j].sellPrice;
        }

        if (item.type == CraftedItemType::Weapon) {
            item.power = 3 + std::pow(1.5, item.resourcesCost);
            item.slots = 0;
        } else if (item.type == CraftedItemType::Armor) {
            item.power = 1 + std::pow(1.2, item.resourcesCost);
            item.slots = item.resourcesCost / 2;
        } else if (item.type == CraftedItemType::Tool) {
            item.power = 0;
            item.slots = 0;
            item.toolResourcesFromBoss.resources[item.resourcesCost] = 1;
        }

        ret.craftedItems.push_back(item);
    }

    int nCraftsmen = 50;
    for (int i = 0; i < nCraftsmen; i++) {
        CraftsmanCard card;
        card.proccedColor = (CraftsmanColor) (rng() % SC(CraftsmanColor::None));
        card.profession = (Profession) (rng() % SC(Profession::None));

        card.basicAbility.type = (CraftsmanAbilityType) (rng() % SC(CraftsmanAbilityType::None));
        card.basicAbility.param1 = rng() % 10;
        card.basicAbility.param2 = rng() % 10;

        card.triggeredAbility.type = (CraftsmanAbilityType) (rng() % SC(CraftsmanAbilityType::None));
        card.triggeredAbility.param1 = rng() % 10;
        card.triggeredAbility.param2 = rng() % 10;

        card.staticAbility = (CraftsmanStaticAbility) (rng() % SC(CraftsmanStaticAbility::None));

        card.picIdx = SC(card.profession);
        card.idx = ret.craftsmen.size();
        ret.craftsmen.push_back(card);
        ret.craftsmenByProfession[card.profession].push_back(&ret.craftsmen.back());
    }

    int nPresets = rng() % 6;
    const auto randomCrafter = [&] (Profession prof) {
        return ret.craftsmenByProfession[prof].at(rng() % ret.craftsmenByProfession[prof].size())->idx;
    };
    for (int i = 0; i < nPresets; i++) {
        Preset preset;
        preset.boundCardOrigins.at(0) = randomCrafter(Profession::Miner);
        if (rng() % 2) preset.boundCardOrigins.at(2) = rng() % ret.craftsmen.size();
        if (rng() % 2) preset.boundCardOrigins.at(4) = rng() % ret.craftsmen.size();
        preset.boundCardOrigins.at(6) = randomCrafter(Profession::Commander);

        for (int j = 0; j < 6; j++) {
            preset.cardOrigins.push_back(rng() % ret.craftsmen.size());
        }

        ret.presets.push_back(preset);
    }

    return ret;
}
