#pragma once

#include "GameState.h"

#include <string>
#include <vector>

struct GameInfo
{
    GameState gs;
    // Field field;

    std::vector<std::string> logs;
    std::vector<LogEvent> logEvents;
};

using GameHistory = std::vector<GameInfo>;
