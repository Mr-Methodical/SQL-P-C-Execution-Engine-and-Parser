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

    // this is with these 3 features
    try {
        ResolvedPath join_and_expr_invalid = 
            resolve_path(invalid_path, std::string{"WROTE"}, 
                         std::string{"a"}, references);
        std::cerr << "failed: accepted an invalid path\n";
        return 1;
    } catch(const std::invalid_argument &) {
        // this is the expected behavior
    }
    // this is with these 1 features
    try {
        ResolvedPath join_and_expr_invalid = 
            resolve_path(Path{"w", std::vector{std::string{"hi"}}}, 
                         std::string{"WROTE"}, 
                         std::string{"a"}, references);
        std::cerr << "failed: accepted an invalid path\n";
        return 1;
    } catch(const std::invalid_argument &) {
        // this is the expected behavior
    }
    // this is with a bad feature so basically find_ref will throw because
    //   because it won't be able to look it up in references
    try {
        ResolvedPath join_and_expr_invalid = 
            resolve_path(Path{"w", {"missing", "name"}}, std::string{"WROTE"}, 
                         std::string{"a"}, references);
        std::cerr << "failed: accepted an invalid path\n";
        return 1;
    } catch(const std::invalid_argument &) {
        // this is the expected behavior
    }
    // this is with a bad source table again find_ref won't be able to search
    //   it up
    try {
        ResolvedPath join_and_expr_invalid = 
            resolve_path(path, std::string{"UNKNOWN"}, 
                         std::string{"a"}, references);
        std::cerr << "failed: accepted an invalid path\n";
        return 1;
    } catch(const std::invalid_argument &) {
        // this is the expected behavior
    }
    if (join_and_expr.join != "JOIN AUTHOR AS a ON w.author_aid = a.aid" ||
        join_and_expr.expression != "a.name") {
            std::cerr << "didn't produce the right join or expression\n";
            return 1;
    }
    // let's try it with different aliases as well:
    join_and_expr =
        resolve_path(Path{"r", {"paper", "title"}}, 
        std::string{"WROTE"}, std::string{"a"}, references);
    if (join_and_expr.join != "JOIN PAPER AS a ON r.paper_pid = a.pid" ||
        join_and_expr.expression != "a.title") {
            std::cerr << "didn't produce the right join or expression\n";
            return 1;
    }
    // assemble the complete query
    // Test 10: assemble the complete example query.
    const std::string source_alias{"w"};
    const Path select_path{source_alias, {"author", "name"}};
    const Path filter_path{source_alias, {"paper", "title"}};

    const ResolvedPath select_result =
        resolve_path(select_path, source_table, "a", references);
    const ResolvedPath filter_result =
        resolve_path(filter_path, source_table, "p", references);

    const std::string query =
        std::string{"SELECT DISTINCT "} + select_result.expression +
        " AS author_name\n" +
        "FROM " + source_table + " AS " + source_alias + "\n" +
        select_result.join + "\n" +
        filter_result.join + "\n" +
        "WHERE " + filter_result.expression + " = 'Databases';";

    const std::string expected_query =
        "SELECT DISTINCT a.name AS author_name\n"
        "FROM WROTE AS w\n"
        "JOIN AUTHOR AS a ON w.author_aid = a.aid\n"
        "JOIN PAPER AS p ON w.paper_pid = p.pid\n"
        "WHERE p.title = 'Databases';";

    if (query != expected_query) {
        std::cerr << "complete query did not match\n"
                << "Expected:\n" << expected_query << "\n"
                << "Actual:\n" << query << "\n";
        return 1;
    }

    std::cout << "passed all 10 SQL tests\n";
    return 0;
}