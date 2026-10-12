#include "mapping.h"
#include "sql.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::vector<ReferenceMapping> references{
        {"WROTE", "author", "author_aid", "AUTHOR", "aid"},
        {"WROTE", "paper",  "paper_pid",  "PAPER",  "pid"}
    };

    const ReferenceMapping &author_mapping =
        find_reference(references, "WROTE", "author");

    const ReferenceMapping &paper_mapping =
        find_reference(references, "WROTE", "paper");

    // Test 1: AUTHOR relationship.
    const std::string author_sql =
        render_join(author_mapping, "w", "a");

    const std::string expected_author =
        "JOIN AUTHOR AS a ON w.author_aid = a.aid";

    if (author_sql != expected_author) {
        std::cerr << "first test did not match\n";
        return 1;
    }

    // Test 2: PAPER relationship.
    const std::string paper_sql =
        render_join(paper_mapping, "w", "p");

    const std::string expected_paper =
        "JOIN PAPER AS p ON w.paper_pid = p.pid";

    if (paper_sql != expected_paper) {
        std::cerr << "Second test did not match\n";
        return 1;
    }

    // Test 3: same AUTHOR relationship, different aliases.
    const std::string renamed_sql =
        render_join(author_mapping, "r", "writer");

    const std::string expected_renamed =
        "JOIN AUTHOR AS writer ON r.author_aid = writer.aid";

    if (renamed_sql != expected_renamed) {
        std::cerr << "Third test did not match\n";
        return 1;
    }

    std::cout << "passed all 3 SQL tests\n";
    return 0;
}