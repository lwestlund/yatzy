#ifndef RULES_HPP_
#define RULES_HPP_

#include <array>
#include <string_view>

namespace yatzy {
namespace rules {
// General.
constexpr int MIN_NUM_PLAYERS{2};
constexpr int MAX_NUM_PLAYERS{100};
constexpr int ACTIONS_PER_ROUND{3};
constexpr int NUM_DICE_COMBINATIONS_UPPER_SECTION{6};
constexpr std::array<std::string_view, NUM_DICE_COMBINATIONS_UPPER_SECTION>
    DICE_COMBINATIONS_UPPER_SECTION{
        {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes"}};
constexpr int UPPER_SECTION_BONUS_SCORE{50};
constexpr int UPPER_SECTION_BONUS_SCORE_THRESHOLD{63};
constexpr int NUM_GAME_ROUNDS{NUM_DICE_COMBINATIONS_UPPER_SECTION};
constexpr int NUM_DICE{5};

// Dice.
constexpr int DICE_MIN_VALUE{1};
constexpr int DICE_MAX_VALUE{6};
} // namespace rules
} // namespace yatzy

#endif // RULES_HPP_
