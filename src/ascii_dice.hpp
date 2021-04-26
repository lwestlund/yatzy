#ifndef ASCII_DICE_HPP_
#define ASCII_DICE_HPP_

#include <array>
#include <string_view>

namespace yatzy {
constexpr int ASCII_DICE_SIZE{5};

struct AsciiDice {
  std::array<std::string_view, ASCII_DICE_SIZE> lines;
};

constexpr AsciiDice DICE_ONE{{
    "-----",
    "|   |",
    "| o |",
    "|   |",
    "-----",
}};

constexpr AsciiDice DICE_TWO{{
    "-----",
    "|o  |",
    "|   |",
    "|  o|",
    "-----",
}};

constexpr AsciiDice DICE_THREE{{
    "-----",
    "|o  |",
    "| o |",
    "|  o|",
    "-----",
}};

constexpr AsciiDice DICE_FOUR{{
    "-----",
    "|o o|",
    "|   |",
    "|o o|",
    "-----",
}};

constexpr AsciiDice DICE_FIVE{{
    "-----",
    "|o o|",
    "| o |",
    "|o o|",
    "-----",
}};

constexpr AsciiDice DICE_SIX{{
    "-----",
    "|o o|",
    "|o o|",
    "|o o|",
    "-----",
}};

constexpr std::array ASCII_DICE{DICE_ONE,  DICE_TWO,  DICE_THREE,
                                DICE_FOUR, DICE_FIVE, DICE_SIX};
} // namespace yatzy

#endif // ASCII_DICE_HPP_
