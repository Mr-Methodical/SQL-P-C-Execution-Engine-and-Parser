#ifndef SQLP_SQL_H
#define SQLP_SQL_H

#include "mapping.h"

#include <string>

// create a join for them based of the aliases we want to give them
std::string render_join(
    const ReferenceMapping &mapping,
    const std::string &source_alias,
    const std::string &target_alias
);

#endif