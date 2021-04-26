#include "dice_set.hpp"

#include "rules.hpp"

#include <doctest/doctest.h>

#include <array>
#include <random>

using namespace yatzy;

namespace {
class DiceSetFixture : protected DiceSet {
public:
  DiceSetFixture()
      : DiceSet(m_generator, m_distribution), m_generator(),
        m_distribution(rules::DICE_MIN_VALUE, rules::DICE_MAX_VALUE) {
    // Seed the generator to be able to check the roll of specific dice.
    m_generator.seed(1);
  }

private:
  std::mt19937 m_generator;
  std::uniform_int_distribution<> m_distribution;
};
} // namespace

TEST_CASE_FIXTURE(DiceSetFixture, "Roll dice") {
  SUBCASE("Roll no dice") {
    // GIVEN
    std::array<bool, rules::NUM_DICE> saveDice{};
    saveDice.fill(true);
    const auto oldDice = m_dice;

    // WHEN
    roll(saveDice);

    // THEN
    for (std::size_t i{0}; i < rules::NUM_DICE; ++i) {
      CHECK_EQ(m_dice[i], oldDice[i]);
    }
  }

  SUBCASE("Roll one dice") {
    // GIVEN
    std::array<bool, rules::NUM_DICE> saveDice{};
    saveDice.fill(true);
    saveDice[0] = false;
    const auto oldDice = m_dice;

    // WHEN
    roll(saveDice);

    // THEN
    CHECK_EQ(m_dice[0], 3);
    for (std::size_t i{1}; i < rules::NUM_DICE; ++i) {
      CHECK_EQ(m_dice[i], oldDice[i]);
    }
  }
}

TEST_CASE_FIXTURE(DiceSetFixture, "getSetScore") {
  SUBCASE("Ones") {
    // GIVEN
    m_dice = {1, 1, 2, 5, 5};

    // WHEN
    const int score{getSetScore(1)};

    // THEN
    CHECK_EQ(score, 2);
  }

  SUBCASE("Twos") {
    // GIVEN
    m_dice = {1, 2, 2, 2, 5};

    // WHEN
    const int score{getSetScore(2)};

    // THEN
    CHECK_EQ(score, 6);
  }

  SUBCASE("Threes") {
    // GIVEN
    m_dice = {1, 2, 2, 2, 5};

    // WHEN
    const int score{getSetScore(3)};

    // THEN
    CHECK_EQ(score, 0);
  }

  SUBCASE("Fours") {
    // GIVEN
    m_dice = {4, 4, 4, 4, 5};

    // WHEN
    const int score{getSetScore(4)};

    // THEN
    CHECK_EQ(score, 16);
  }

  SUBCASE("Fives") {
    // GIVEN
    m_dice = {4, 5, 4, 4, 5};

    // WHEN
    const int score{getSetScore(5)};

    // THEN
    CHECK_EQ(score, 10);
  }

  SUBCASE("Sixes") {
    // GIVEN
    m_dice = {6, 6, 6, 6, 6};

    // WHEN
    const int score{getSetScore(6)};

    // THEN
    CHECK_EQ(score, 30);
  }
}
