#include "path.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

int main() {
    const Path path{"w", {"author", "name"}};
    const std::vector<std::string> expected{"author", "name"};

    if (path.root() != "w" || path.features() != expected) {
        std::cerr << "the element fields did not match" << std::endl;
        return 1;
    }

    try {
        const Path path{"", expected};

        std::cerr << "accepted an empty root" << std::endl;
        return 1;
    } catch(const std::invalid_argument &) {
        // do nothing this is good behavior
    }

    try {
        Path path{"w", {"hello", "world", "", "bah"}};

        std::cerr << "accepted an empty feature" << std::endl;
        return 1;
    } catch(const std::invalid_argument &) {
        // do nothing as this is what we wanted
    }

    try {
        Path path{"w", {}};

        std::cerr << "accepted an empty vector" << std::endl;
    } catch(const std::invalid_argument &) {
        // nothing we want this
    }

    std::cout << "all 4 tests passed" << std::endl;
    return 0;
}