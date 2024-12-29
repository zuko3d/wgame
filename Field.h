#pragma once

#include "ResizableArray.h"
#include "Types.h"

#include <array>
#include <vector>

struct GameState;
struct PrecalcCache;

struct FieldOrigin {
    static constexpr int8_t width = 7;
    static constexpr int8_t height = 11;
    static constexpr size_t FIELD_SIZE = width * height;
    std::array<ResizableArray<int8_t, 6>, FIELD_SIZE> neibs;

    void init();
};

// Don't forget to make it Copy-on-write
class Field {
public:
    // static Field& newField(PrecalcCache& cache);

    // std::vector<int8_t> hexesByPlayer(Building b, int p, bool withNeutrals = false) const;

    std::array<uint8_t, FieldOrigin::FIELD_SIZE> bossOrigins; // -1 for empty
    std::array<FieldHex, FieldOrigin::FIELD_SIZE> hexes;

    // std::array<TerrainType, FieldOrigin::FIELD_SIZE> type;
    std::array<int8_t, FieldOrigin::FIELD_SIZE> owner = {};
    std::array<ResizableArray<int8_t, 15>, 5> ownedByPlayer = {};
    int stateIdx = 0;


    std::array<int8_t, FieldOrigin::FIELD_SIZE> bfs(int owner, int reach) const;
    // void populateField(GameState& gs, FieldActionType action, int pos, int param1 = 0, int param2 = 0);
};

struct PrecalcCache {
    std::vector<Field> fieldByState_;

    void reset() {
        fieldByState_.clear();
    }
};
