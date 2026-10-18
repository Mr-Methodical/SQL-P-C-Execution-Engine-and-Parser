#include "sql.h"
#include "mapping.h"

#include <string>
#include <stdexcept>

std::string render_join(
    const ReferenceMapping &mapping,
    const std::string &source_alias,
    const std::string &target_alias
) {
    return std::string{"JOIN "} + mapping.target_table +
           " AS " + target_alias + " ON " + 
           source_alias + "." + mapping.source_column + 
           " = " + target_alias + "." + mapping.target_column; 
}

ResolvedPath resolve_path(
    const Path &path,
    const std::string &source_table,
    const std::string &target_alias,
    const std::vector<ReferenceMapping> &references
) {
    if (path.features().size() != 2) {
        throw std::invalid_argument(
            "There must be two features.\n"
        );
    }
    const ReferenceMapping &mapping =
        find_reference(references, source_table, path.features()[0]);
    std::string join_result = render_join(mapping, path.root(), target_alias);
    std::string expression = target_alias + '.' + path.features()[1];
    return ResolvedPath{join_result, expression};
}