#pragma once

#include "Types.h"
#include "ResizableArray.h"

#include <array>

struct StaticTechTree {
    static constexpr size_t GRADES = 5;
    ResizableArray<std::array<Technology, GRADES>, 6> technologies;
    std::array<std::array<Boss, StaticTechTree::GRADES>, 2> bosses; // left and right
};

struct TechTree {
    const StaticTechTree* stt;
    ResizableArray<std::array<int8_t, StaticTechTree::GRADES>, 6> owner;
};
