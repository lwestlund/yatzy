#include "player.hpp"

#include "rules.hpp"

#include <array>
#include <doctest/doctest.h>

using namespace yatzy;

namespace {
constexpr int PLAYER_NUM{3};

class PlayerFixture : public Player {
public:
  PlayerFixture() : Player(PLAYER_NUM) {}
};
} // namespace

TEST_CASE_FIXTURE(PlayerFixture, "getUpperSectionScore") {
  // GIVEN
  m_combinationScoreUpperSection = {1, 2, 3, 4, 5, 6};

  // WHEN
  const int upperSectionScore{getUpperSectionScore()};

  // THEN
  CHECK_EQ(upperSectionScore, 1 + 2 + 3 + 4 + 5 + 6);
}

TEST_CASE_FIXTURE(PlayerFixture, "getScore") {
  SUBCASE("Bonus NOT achieved") {
    // GIVEN
    // Upper section score of 62 that should be less than the upper section
    // score bonus threshold.
    const std::array<int, rules::NUM_DICE_COMBINATIONS_UPPER_SECTION>
        upperSectionScores{2 * 1, 3 * 2, 3 * 3, 3 * 4, 3 * 5, 3 * 6};
    m_combinationScoreUpperSection = upperSectionScores;
    CHECK_LT(getUpperSectionScore(),
             rules::UPPER_SECTION_BONUS_SCORE_THRESHOLD);

    // WHEN
    const int score{getScore()};

    // THEN
    CHECK_EQ(score,
             std::reduce(upperSectionScores.begin(), upperSectionScores.end()));
  }

  SUBCASE("Bonus achieved") {
    // GIVEN
    // Upper section score of 62 that should be less than the upper section
    // score bonus threshold.
    const std::array<int, rules::NUM_DICE_COMBINATIONS_UPPER_SECTION>
        upperSectionScores{3 * 1, 3 * 2, 3 * 3, 3 * 4, 3 * 5, 3 * 6};
    m_combinationScoreUpperSection = upperSectionScores;
    CHECK_EQ(getUpperSectionScore(),
             rules::UPPER_SECTION_BONUS_SCORE_THRESHOLD);

    // WHEN
    const int score{getScore()};

    // THEN
    CHECK_EQ(score, rules::UPPER_SECTION_BONUS_SCORE +
                        std::reduce(upperSectionScores.begin(),
                                    upperSectionScores.end()));
  }
}

TEST_CASE_FIXTURE(PlayerFixture, "Player number is correct") {
  // GIVEN
  // A player, which we have in the fixture.

  // WHEN
  const int playerNum{getPlayerNumber()};

  // THEN
  CHECK_EQ(playerNum, PLAYER_NUM);
}
