#include "mapping.h"
#include "sql.h"
#include "path.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::vector<ReferenceMapping> references{
        {"WROTE", "author", "author_aid", "AUTHOR", "aid"},
        {"WROTE", "paper",  "paper_pid",  "PAPER",  "pid"}
    };

    const std::string source_table{"WROTE"};
    const std::string author_feature{"author"};
    const std::string paper_feature{"paper"};

    const ReferenceMapping &author_mapping =
        find_reference(references, source_table, author_feature);

    const ReferenceMapping &paper_mapping =
        find_reference(references, source_table, paper_feature);

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

    const Path path{"w", {"author", "name"}};
    // now let's test the resolve path function 
    ResolvedPath join_and_expr = 
        resolve_path(path, std::string{"WROTE"}, std::string{"a"}, references);

    const Path invalid_path{"w", {"author", "name", "hello"}};

    try {
        ResolvedPath join_and_expr_invalid = 
            resolve_path(invalid_path, std::string{"WROTE"}, 
                         std::string{"a"}, references);
        std::cerr << "failed: accepted an invalid path\n";
        return 1;
    } catch(const std::invalid_argument &) {
        // this is the expected behavior
    }
    if (join_and_expr.join != "JOIN AUTHOR AS a ON w.author_aid = a.aid" ||
        join_and_expr.expression != "a.name") {
            std::cerr << "didn't produce the right join or expression";
            return 1;
    }
    std::cout << "passed all 5 SQL tests\n";
    return 0;
}