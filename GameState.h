#pragma once

#include "Field.h"
#include "ResizableArray.h"
#include "Types.h"
#include "PlayerState.h"

#include <iostream>

struct StaticGameState {
    // ResizableArray<MayorOrder, 4> mayorOrdersByEpoch;
};

struct GameState {
    ResizableArray<PlayerState, 5> players;
    ResizableArray<int8_t, 5> playersTurnOrder;

    ResizableArray<Party, 6> parties;

    int round = 0;
    int activePlayer = 0;

    // technical ----------------------------------------------------------------

    uint32_t fieldStateIdx = 0;
    const Field& field() const {
        return cache->fieldByState_[fieldStateIdx];
    }
    Field& field() {
        return cache->fieldByState_[fieldStateIdx];
    }
        GameState clone() {
        GameState ret = *this;
        // ret.cache = std::shared_ptr<PrecalcCache>(new PrecalcCache(*cache));

        std::cerr << "Intentional MEMORY LEAK!" << std::endl;
        // Excuse me for that intentional memory leak
        ret.cache = new PrecalcCache(*cache);
        return ret;
    }

    const StaticGameState* staticGs;
    PrecalcCache* cache;
};
