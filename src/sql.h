#ifndef SQLP_SQL_H
#define SQLP_SQL_H

#include "mapping.h"
#include "path.h"

#include <string>
#include <vector>

// create a join for them based of the aliases we want to give them
std::string render_join(
    const ReferenceMapping &mapping,
    const std::string &source_alias,
    const std::string &target_alias
);

struct ResolvedPath {
    std::string join;
    std::string expression;
};

ResolvedPath resolve_path(
    const Path &path,
    const std::string &source_table,
    const std::string &target_alias,
    const std::vector<ReferenceMapping> &references
);

#endif