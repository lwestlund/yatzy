#include "player.hpp"

#include "io.hpp"
#include "rules.hpp"

#include <array>
#include <bits/c++config.h>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <utility>

namespace yatzy {
namespace {
std::mt19937 s_generator{std::random_device()()};
std::uniform_int_distribution<> s_distribution(rules::DICE_MIN_VALUE,
                                               rules::DICE_MAX_VALUE);
} // namespace

Player::Player(const int playerNumber)
    : m_playerNumber(playerNumber), m_savedDiceCombinations(),
      m_combinationScoreUpperSection(), m_upperSectionBonus(0),
      m_diceSet(s_generator, s_distribution) {
  m_savedDiceCombinations.fill(false);
  m_combinationScoreUpperSection.fill(0);
}
std::string Player::getScoreCard() const {
  std::stringstream ss;
  for (std::size_t i{0}; i < rules::NUM_DICE_COMBINATIONS_UPPER_SECTION; ++i) {
    ss << rules::DICE_COMBINATIONS_UPPER_SECTION[i] << ":\t"
       << m_combinationScoreUpperSection[i] << '\n';
  }
  ss << "Bonus:\t" << m_upperSectionBonus << '\n';
  return ss.str();
}

int Player::getUpperSectionScore() const {

  return std::reduce(m_combinationScoreUpperSection.begin(),
                     m_combinationScoreUpperSection.end());
}

int Player::getUpperSectionBonus() const {
  if (getUpperSectionScore() >= rules::UPPER_SECTION_BONUS_SCORE_THRESHOLD) {
    m_upperSectionBonus = rules::UPPER_SECTION_BONUS_SCORE;
  }
  return m_upperSectionBonus;
}

int Player::getScore() const {
  return getUpperSectionScore() + getUpperSectionBonus();
}

int Player::getPlayerNumber() const { return m_playerNumber; }

void Player::playRound() {
  std::cout << "---------------------------------\n";
  std::cout << "Player " << m_playerNumber << '\n';
  std::cout << "---------------------------------\n";
  std::cout << "Your score card:\n" << getScoreCard() << '\n';
  std::cout << "Total score: " << getScore() << "\n\n";
  std::cout << "Press enter to roll dice!\n";
  io::ignoreLine();
  std::array<bool, rules::NUM_DICE> saveDice{};
  saveDice.fill(false);
  for (int action = 0; action < rules::ACTIONS_PER_ROUND; ++action) {
    m_diceSet.roll(saveDice);
    if (action < rules::ACTIONS_PER_ROUND - 1) {
      std::cout << m_diceSet << '\n';
      const auto [endRound, diceToSave] = getDiceToSave();
      if (!endRound) {
        saveDice = diceToSave;
      } else {
        break;
      }
    }
  }
  saveRoundResult();
}

std::pair<bool, std::array<bool, rules::NUM_DICE>> Player::getDiceToSave() {
  std::array<bool, rules::NUM_DICE> saveDice;
  bool hasInput = false;
  bool endRound = false;
  while (!hasInput && !endRound) {
    saveDice.fill(false);
    std::cout << "Enter which dice to save, enter zero to end round: ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) {
      std::stringstream ss(input);
      std::size_t diceIndex{};
      while (ss >> diceIndex) {
        if (diceIndex == 0) {
          saveDice.fill(true);
          hasInput = true;
          endRound = true;
        } else if (diceIndex > 0 && diceIndex <= rules::NUM_DICE) {
          saveDice[diceIndex - 1] = true;
          hasInput = true;
        }
      }
      if (!hasInput) {
        std::cout << "Invalid input, try again.\n";
      }
    } else {
      // Don't save any dice, reroll all.
      hasInput = true;
    }
  }
  return {endRound, saveDice};
}

void Player::saveRoundResult() {
  while (true) {
    std::cout << "Your dice are:\n" << m_diceSet << '\n';
    std::cout << "Your score card:\n" << getScoreCard() << '\n';
    // TODO(lovewg): This should probably not be an integer input, especially
    // if a lower section is added to the scoring.
    const auto combinationIndex{
        io::parseIntegralInRange<std::size_t>(
            "Enter combination that you would like to save them as: ", 1,
            rules::NUM_DICE_COMBINATIONS_UPPER_SECTION) -
        1}; // Subtract one because of zero indexing.
    if (m_savedDiceCombinations[combinationIndex]) {
      std::cout << "You already have an entry for "
                << rules::DICE_COMBINATIONS_UPPER_SECTION[combinationIndex]
                << ", choose another combination!\n";
    } else {
      m_savedDiceCombinations[combinationIndex] = true;
      m_combinationScoreUpperSection[combinationIndex] =
          m_diceSet.getSetScore(combinationIndex + 1);
      if (getUpperSectionScore() >=
          rules::UPPER_SECTION_BONUS_SCORE_THRESHOLD) {
        m_upperSectionBonus = rules::UPPER_SECTION_BONUS_SCORE;
      }
      return;
    }
  }
}
} // namespace yatzy
