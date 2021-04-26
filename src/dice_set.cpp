#include "dice_set.hpp"

#include "ascii_dice.hpp"
#include "rules.hpp"

#include <algorithm>
#include <ostream>
#include <random>
#include <stdexcept>

namespace yatzy {

DiceSet::DiceSet(std::mt19937 &generator,
                 std::uniform_int_distribution<> &distribution)
    : m_dice(), m_generator(generator), m_distribution(distribution) {
  m_dice.fill(rules::DICE_MIN_VALUE - 1);
}

void DiceSet::roll(const std::array<bool, rules::NUM_DICE> &saveDice) {
  for (std::size_t i{0}; i < rules::NUM_DICE; ++i) {
    if (!saveDice[i]) {
      m_dice[i] = m_distribution(m_generator);
    }
  }
}

void DiceSet::printDice(std::ostream &os) const {
  for (std::size_t line{0}; line < ASCII_DICE_SIZE; ++line) {
    for (const auto &diceValue : m_dice) {
      os << ASCII_DICE[static_cast<std::size_t>(diceValue - 1)].lines[line]
         << "  ";
    }
    os << '\n';
  }
}

int DiceSet::getSetScore(const std::size_t combinationIndex) const {
  if (1 <= combinationIndex && combinationIndex <= 6) {
    return getUpperSectionSetScore(combinationIndex);
  }
  throw std::invalid_argument(
      "Unknown combinationIndex, this should never happen!");
  return -1;
}

int DiceSet::getUpperSectionSetScore(const std::size_t combinationIndex) const {
  const auto scoreUpperSection = [&](const int diceValue) {
    return diceValue * static_cast<int>(
                           std::count(m_dice.begin(), m_dice.end(), diceValue));
  };

  switch (combinationIndex) {
  case 1:
    return scoreUpperSection(1);
  case 2:
    return scoreUpperSection(2);
  case 3:
    return scoreUpperSection(3);
  case 4:
    return scoreUpperSection(4);
  case 5:
    return scoreUpperSection(5);
  case 6:
    return scoreUpperSection(6);
  default:
    throw std::invalid_argument(
        "Unknown dice combination, this should never happen!");
  }
}

std::ostream &operator<<(std::ostream &os, const DiceSet &diceSet) {
  diceSet.printDice(os);
  return os;
}

} // namespace yatzy
