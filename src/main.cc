#include <iostream>
#include "path.h"

int main() {
  const Path path{"w", {"author", "name"}};

  std::cout << path.root();

  for (const auto &feature : path.features()) {
    std::cout << '.' << feature;
  }

  std::cout << '\n';
}
