#include "sql.h"

#include <string>

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