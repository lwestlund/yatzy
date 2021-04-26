#include "yatzy.hpp"

#include "player.hpp"
#include "rules.hpp"

#include <bits/c++config.h>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace yatzy {
Yatzy::Yatzy(const int numPlayers) : m_players() {
  if (numPlayers < 2) {
    throw std::runtime_error("Cannot play yatzy with less than two players.");
  }
  m_players.reserve(static_cast<std::size_t>(numPlayers));
  for (int i = 1; i <= numPlayers; ++i) {
    m_players.emplace_back(i);
  }
}

int Yatzy::play() {
  for (int round = 0; round < rules::NUM_GAME_ROUNDS; ++round) {
    std::cout << "=================================\n";
    std::cout << "Round " << round + 1 << '\n';
    std::cout << "=================================\n";
    for (auto &p : m_players) {
      p.playRound();
    }
  }
  printResults();
  return 0;
}

void Yatzy::printResults() {
  std::vector<int> highestScorePlayers;
  int highestScore{-1};
  std::cout << "\nPlayer scores\n =============\n";
  for (const auto &p : m_players) {
    std::cout << "Player " << p.getPlayerNumber() << '\n';
    std::cout << "-------------\n";
    std::cout << p.getScoreCard() << '\n';
    std::cout << "\nTotal score: " << p.getScore() << '\n';
    const int score{p.getScore()};
    if (score == highestScore) {
      highestScorePlayers.push_back(p.getPlayerNumber());
    } else if (score > highestScore) {
      highestScorePlayers.clear();
      highestScorePlayers.push_back(p.getPlayerNumber());
      highestScore = score;
    }
  }

  std::cout << '\n';
  if (highestScorePlayers.size() > 1) {
    std::cout << "The winners are players ";
    for (std::size_t i{0}; i < highestScorePlayers.size() - 1; ++i) {
      std::cout << highestScorePlayers[i] << ' ';
    }
    std::cout << "and " << highestScorePlayers.back() << "!\n";
    std::cout << "They were tied at " << highestScore << " points!\n";
  } else {
    std::cout << "The winner is player " << highestScorePlayers.front()
              << " with " << highestScore << " points!\n";
  }
}
} // namespace yatzy
