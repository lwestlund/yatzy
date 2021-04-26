#ifndef DICE_SET_HPP_
#define DICE_SET_HPP_

#include "rules.hpp"

#include <array>
#include <random>

namespace yatzy {
class DiceSet {
public:
  DiceSet(std::mt19937 &generator,
          std::uniform_int_distribution<> &distribution);

  void roll(const std::array<bool, rules::NUM_DICE> &saveDice);

  void printDice(std::ostream &os) const;

  int getSetScore(const std::size_t combinationIndex) const;

  friend std::ostream &operator<<(std::ostream &os, const DiceSet &diceSet);

protected:
  int getUpperSectionSetScore(const std::size_t combinationIndex) const;

  std::array<int, rules::NUM_DICE> m_dice;
  std::mt19937 &m_generator;
  std::uniform_int_distribution<> &m_distribution;
};
} // namespace yatzy

#endif // DICE_SET_HPP_
