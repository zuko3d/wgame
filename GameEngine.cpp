#include "GameEngine.h"

void GameEngine::log(const GameState& gs, const std::string& str) const {
    if (withLogs_) {
        logger_("Player " + std::to_string(gs.activePlayer) + ": " + str);
    }
}

void GameEngine::log(const std::string& str) const {
    if (withLogs_) {
        logger_(str);
    }
}

void GameEngine::setLogger(std::function<void(const std::string&)> logger) {
    logger_ = logger;
}

void GameEngine::logCheckpoint() const {
    if (withLogs_) {
        logCheckpointer_();
    }
}

void GameEngine::logEvent(const GameState& gs, LogEventType type, int param) const {
    if (eventLogger_) {
        eventLogger_(LogEvent{
            .round = gs.round,
            .activePlayer = gs.activePlayer,
            .type = type,
            .param = param,
        });
    }
}

void GameEngine::setEventLogger(std::function<void(LogEvent)> logger) {
    eventLogger_ = logger;
}

void GameEngine::setLogCheckpointer(std::function<void()> logCheckpointer) {
    logCheckpointer_ = logCheckpointer;
}

GameEngine::GameEngine(std::vector<IBot*> bots, const GameData& gd, bool withLogs)
    : bots_(std::move(bots))
    , gd_(gd)
    , withLogs_(withLogs)
{ }

void GameEngine::doTurnGuided(GameState& gs) const {
    const auto bot = bots_.at(gs.activePlayer);
    auto actions = generateActions(gs);
    auto action = bot->chooseAction(gs, actions);
    
    doAction(action, gs);

    // trigger tapped actions
    assert (false);
}

bool GameEngine::gameEnded(const GameState& gs) const {
    return gs.round >= 5;
}

void GameEngine::advanceGs(GameState& gs) const {
    if (!gameEnded(gs)) {
        dealWithUpkeep(gs);
        doTurnGuided(gs);
        doAfterTurnActions(gs);
    }
}

void GameEngine::playGame(GameState& gs) const {
    while (!gameEnded(gs)) {
        const auto field = gs.field();
        gs.cache->reset();
        gs.fieldStateIdx = 0;
        gs.cache->fieldByState_.push_back(field);
        advanceGs(gs);
    }
}

// void GameEngine::awardWp(int amount, GameState& gs) const {
//     if (amount != 0) {
//         getPs(gs).resources.winPoints += amount;
//     }
// }

// void GameEngine::awardWp(EventType event, GameState& gs) const {
//     auto& ps = getPs(gs);
//     const auto amount = ps.wpPerEvent[event];
//     if (amount != 0) {
//         ps.resources.winPoints += amount;
//     }
// }

PlayerState& GameEngine::getPs(GameState& gs) const {
    assert (gs.activePlayer < 2);
    return gs.players[gs.activePlayer];
}


// --------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------
void GameEngine::initializeRandomly(GameState& gs, std::default_random_engine& rng) const {
    for (int8_t i = 0; i < bots_.size(); ++i) {
        gs.playersTurnOrder.push_back(i);
    }

    gs.activePlayer = 0;
    gs.round = 0; // pre-game

    for (int8_t i = 0; i < bots_.size(); i++) {
        int p = bots_[i]->choosePreset(gs, gd_.presets);
        const auto& preset = gd_.presets[p];
        auto& ps = gs.players[i];
        for (int j = 0; j < preset.boundCardOrigins.size(); ++j) {
            ps.craftsmenSlots[j] = preset.boundCardOrigins[j];
            if (preset.boundCardOrigins[j] >= 0) {
                ps.boundSlots[j] = true;
            } else {
                ps.boundSlots[j] = false;
            }
        }
        for (const auto& cardOrigin : preset.cardOrigins) {
            ps.hand.push_back(cardOrigin);
        }
    }

    // init field
    Field staringField;
    for (auto& boss: staringField.bossOrigins) {
        boss = rng() % gd_.bosses.size();
    }
    auto possibleHexes = gd_.hexes;
    rshuffle(possibleHexes, rng);
    for (int i = 0; i < staringField.hexes.size(); ++i) {
        staringField.hexes[i] = possibleHexes[i];
    }

    for (auto& o: staringField.owner) {
        o = -1;
    }
    
    gs.staticGs = staticGs_.get();
    cache_ = std::make_shared<PrecalcCache>();
    gs.cache = cache_.get();
    gs.cache->fieldByState_.reserve(50000);
    gs.cache->fieldByState_.push_back(staringField);
    gs.fieldStateIdx = 0;

    for (int i = 0; i < gs.players.size() + 1; ++i) {
        Party party;

        int partySize = rng() % 3 + 4;
        for (int j = 0; j < partySize; ++j) {
            party.adventurers.push_back(AdventurerOnField{
                .origin = &gd_.adventurers[rng() % gd_.adventurers.size()],
                .equippedItem = {},
                .isAlive = true,
                .partyIdx = i
            });
        }

        gs.parties.push_back(party);
    }
}

void GameEngine::reset() {
}
