#pragma once

#include "FlatMap.h"

enum class ResourceGrade {
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary,
    None,
};

struct ResourceOrigin {
    ResourceGrade tier = ResourceGrade::None;
    int sellPrice = 0;
};

struct Resources {
    std::array<int, 10> cubes = {{ 0 }};
    int gold = 0;
    // int winPoints = 0;
};

struct IncomableResources {
    std::array<int, 10> resources = {{ 0 }};
    int gold = 0;
    // int winPoints = 0;

    int anyResource = 0;
};

