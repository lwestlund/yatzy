#include "io.hpp"
#include "rules.hpp"
#include "yatzy.hpp"

#include <iostream>

int main() {
  while (true) {
    const auto numPlayers{io::parseIntegralInRange<int>(
        "Enter the number of players: ", yatzy::rules::MIN_NUM_PLAYERS,
        yatzy::rules::MAX_NUM_PLAYERS)};

    try {
      yatzy::Yatzy yatzy(numPlayers);
      return yatzy.play();
    } catch (const std::runtime_error &e) {
      std::cout << e.what() << '\n';
    }
  }
}
