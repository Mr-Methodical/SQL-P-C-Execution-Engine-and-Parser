#include "mapping.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

int main() {
    const std::vector<ReferenceMapping> references{
        {"WROTE", "author", "author_aid", "AUTHOR", "aid"},
        {"WROTE", "paper",  "paper_pid",  "PAPER",  "pid"}
    };
    if (references[0] != find_reference(references, "WROTE", "author")) {
        std::cerr << "find_reference error; wrote, author";
        return 1;
    }
    if (references[1] != find_reference(references, "WROTE", "paper")) {
        std::cerr << "find_reference error; wrote, paper";
        return 1;
    }
    try {
        find_reference(references, "WROTE", "ryan");

        std::cerr << "find_reference didn't throw error on non-existent feature\n";
        return 1;
    } catch(const std::invalid_argument &) {
        // good this is what we want
    }
    try {
        find_reference(references, "UNKNOWN", "author");

        std::cerr << "accepted an unknown source table\n";
        return 1;
    } catch (const std::invalid_argument &) {
        // Expected.
    }

    std::cout << "passed all 4 tests\n";
    return 0;
}