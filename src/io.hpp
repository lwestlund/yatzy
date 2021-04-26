#ifndef IO_HPP_
#define IO_HPP_

#include <iostream>
#include <limits>
#include <string_view>
#include <type_traits>

namespace io {
void ignoreLine();

template <typename Integral,
          typename = std::enable_if_t<std::is_integral<Integral>::value, bool>>
Integral parseIntegralInRange(
    std::string_view query,
    const Integral lowerBound = std::numeric_limits<Integral>::min(),
    const Integral upperBound = std::numeric_limits<Integral>::max()) {
  while (true) {
    Integral integral{};
    std::cout << query;
    std::cin >> integral;
    if (std::cin.fail()) {
      std::cout << "Invalid input, try again.\n";
      std::cin.clear();
      ignoreLine();
    } else {
      ignoreLine();
      if (lowerBound <= integral && integral <= upperBound) {
        return integral;
      } else {
        std::cout << "Number must be within range [" << lowerBound << ", "
                  << upperBound << "], try again.\n";
      }
    }
  }
}

} // namespace io

#endif // IO_HPP_
