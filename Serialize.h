#pragma once

#include "json.hpp"

#include "Field.h"
#include "FlatMap.h"
#include "ResizableArray.h"
#include "Types.h"
#include "Utils.h"
#include "PlayerState.h"
#include "GameState.h"
#include "GameHistory.h"

#include <array>
#include <string>
#include <vector>

struct ScoreWeights;

// int toJson(int8_t v);

ScoreWeights fromJsonStr(const std::string& str);

double toJson(double v);

nlohmann::json toJson(const std::string& v);

nlohmann::json toJson(const IncomableResources& res);

nlohmann::json toJson(const Resources& res);

nlohmann::json toJson(const Action& op);

nlohmann::json toJson(const PlayerState& ps);

nlohmann::json toJson(const Field& f);

nlohmann::json toJson(const StaticGameState& sgs);

nlohmann::json toJson(const GameState& gs);

nlohmann::json toJson(const GameInfo& gi);

nlohmann::json toJson(const LogEvent& le);

template <typename T1, typename T2>
inline nlohmann::json toJson(std::pair<T1, T2> p) {
    nlohmann::json j = nlohmann::json::array();
    j.push_back(toJson(p.first));
    j.push_back(toJson(p.second));

    return j;
}

template <typename KeyType, typename ValueType, size_t Size>
inline nlohmann::json toJson(const FlatMap<KeyType, ValueType, Size>& mp) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& v : mp.values()) {
        j.push_back(toJson(v));
    }

    return j;
}

template <typename T, size_t N>
inline nlohmann::json toJson(const std::array<T, N>& arr) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& v : arr) {
        j.push_back(toJson(v));
    }

    return j;
}

template <typename J, typename T, size_t N>
inline void fromJson(const J& j, std::array<T, N>& dst) {
    for (const auto [idx, v] : enumerate(j)) {
        dst.at(idx) = (T) v;
    }
}

inline void fromJson(const nlohmann::json& j, NewGameParams& dst) {
    dst.seed = j["seed"].get<int>();
    fromJson(j["usedPresetIdx"], dst.usedPresetIdx);
    fromJson(j["isHuman"], dst.isHuman);
}

template <typename T>
inline nlohmann::json toJson(const std::vector<T>& arr) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& v : arr) {
        j.push_back(toJson(v));
    }

    return j;
}

template <typename T, size_t N>
inline nlohmann::json toJson(const ResizableArray<T, N>& arr) {
    nlohmann::json j = nlohmann::json::array();
    for (const auto& v : arr) {
        j.push_back(toJson(v));
    }

    return j;
}
