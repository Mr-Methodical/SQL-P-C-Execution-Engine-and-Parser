#ifndef SQLP_SQL_H
#define SQLP_SQL_H

#include "mapping.h"

#include <string>

std::string render_join(
    const ReferenceMapping &mapping,
    const std::string &source_alias,
    const std::string &target_alias
);

#endif