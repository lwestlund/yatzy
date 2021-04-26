#include "io.hpp"

namespace io {
void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
} // namespace io
