#ifndef SQLP_SQL_H
#define SQLP_SQL_H

#include "catalog.h"
#include "mapping.h"
#include "path.h"

#include <string>

// the aliases for the columns
struct ColumnRef {
    std::string alias;
    std::string column;
};

// reference mapping describes a relationship that exists in schema, but
// joinSpec is the way we use that relationship
// it describes the actual JOIN required for a particular query, with aliases
struct JoinSpec {
    std::string target_table;
    ColumnRef source;
    ColumnRef target;
};

// Represents a resolved SQLP path: the JOIN needed to follow
// the reference and the final column being accessed.
struct ResolvedPath {
    JoinSpec join;
    ColumnRef column;
};

// Converts a ColumnRef into SQL text.
// Example: ColumnRef{"a", "name"} -> "a.name"
std::string render_column(const ColumnRef &column);
// Converts a JoinSpec into an SQL JOIN statement.
// Example: JoinSpec{"AUTHOR", {"w", "author_aid"}, {"a", "aid"}}
// -> "JOIN AUTHOR AS a ON w.author_aid = a.aid"
std::string render_join(const JoinSpec &join);

// we will leave this for now so our old tests still work, we will get rid
// of the tests later
// create a join for them based of the aliases we want to give them
std::string render_join(
    const ReferenceMapping &mapping,
    const std::string &source_alias,
    const std::string &target_alias
);

ResolvedPath resolve_path(
    const Path &path,
    const std::string &source_table,
    const std::string &target_alias,
    const Catalog &catalog
);


#endif