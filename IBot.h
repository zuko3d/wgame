#pragma once

#include "GameState.h"
#include "Types.h"

class IBot {
public:
    virtual ~IBot() = default;

    virtual int choosePreset(const GameState& gs, const std::vector<Preset>& presets) { return 0; };

    virtual Action chooseAction(const GameState& gs, const std::vector<Action>& actions) = 0;

    virtual void triggerFinal(const GameState& gs) { };
    virtual void stop() { };
    virtual void reset() { };
    virtual std::string paramsAsString() { return "{}"; };
};
