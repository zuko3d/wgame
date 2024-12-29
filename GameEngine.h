#pragma once

#include "GameState.h"
#include "GameData.h"
#include "IBot.h"
#include "Types.h"

#include <functional>
#include <optional>

class GameEngine {
public:
    GameEngine(std::vector<IBot*> bots, const GameData& gd, bool withLogs = false);
    void reset();

    void initializeRandomly(GameState& gs, std::default_random_engine& g) const;

    void playGame(GameState& gs) const;

    std::vector<Action> generateActions(const GameState& gs) const;
    void doAction(Action action, GameState& gs) const;
    void dealWithUpkeep(GameState& gs) const;
    void doAfterTurnActions(GameState& gs) const;
    void doTurnGuided(GameState& gs) const;
    void advanceGs(GameState& gs) const;
    
    void doFinalScoring(GameState& gs) const;

    // ---- player actions --------------------------------


    // ---
    // void awardWp(int amount, GameState& gs) const;
    // void awardWp(GameState& gs) const;
    void spendResources(IncomableResources resources, GameState& gs) const;
    void spendResources(Resources resources, GameState& gs) const;
    void awardResources(IncomableResources resources, GameState& gs) const;
    void awardResources(Resources resources, GameState& gs) const;
    // ---

    bool gameEnded(const GameState& gs) const;

    // --- internal/technical methods --------------------------------
    void log(const std::string& str) const;
    void log(const GameState& gs, const std::string& str) const;
    void setLogger(std::function<void(const std::string&)> logger);

    void logEvent(const GameState& gs, LogEventType type, int param) const;
    void setEventLogger(std::function<void(LogEvent)> logger);

    void logCheckpoint() const;
    void setLogCheckpointer(std::function<void()> logCheckpointer);

private:
    PlayerState& getPs(GameState& gs) const;

    std::vector<IBot*> bots_;

    bool withLogs_ = false;

    std::function<void(const std::string&)> logger_;
    std::function<void(LogEvent)> eventLogger_;
    std::function<void()> logCheckpointer_;

    mutable std::shared_ptr<StaticGameState> staticGs_ = std::shared_ptr<StaticGameState>(new StaticGameState());
    mutable std::shared_ptr<PrecalcCache> cache_;

    const GameData gd_;
};
