#ifndef YATZY_HPP_
#define YATZY_HPP_

#include "player.hpp"

#include <vector>

namespace yatzy {
class Yatzy {
public:
  explicit Yatzy(const int numPlayers);

  int play();

private:
  void printResults();

  std::vector<Player> m_players;
};
} // namespace yatzy

#endif // YATZY_HPP_
