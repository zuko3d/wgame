#pragma once

#include "ResizableArray.h"
#include "Types.h"

struct PlayerState
{
    Resources resources;

    ResizableArray<const CraftsmanCard*, 10> hand;
    std::array<const CraftsmanCard*, 7> craftsmenSlots; // nullptr for empty

    std::array<bool, 7> boundSlots;
};
