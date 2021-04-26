#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "dice_set.hpp"
#include "rules.hpp"

#include <array>
#include <utility>

namespace yatzy {
class Player {
public:
  explicit Player(const int playerNumber);

  std::string getScoreCard() const;

  int getUpperSectionScore() const;

  int getUpperSectionBonus() const;

  int getScore() const;

  int getPlayerNumber() const;

  void playRound();

protected:
  std::pair<bool, std::array<bool, rules::NUM_DICE>> getDiceToSave();
  void saveRoundResult();

  const int m_playerNumber;
  std::array<bool, rules::NUM_DICE_COMBINATIONS_UPPER_SECTION>
      m_savedDiceCombinations;
  std::array<int, rules::NUM_DICE_COMBINATIONS_UPPER_SECTION>
      m_combinationScoreUpperSection;
  mutable int m_upperSectionBonus;
  DiceSet m_diceSet;
};

} // namespace yatzy

#endif // PLAYER_HPP_
