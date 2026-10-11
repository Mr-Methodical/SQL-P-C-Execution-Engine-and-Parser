#ifndef SQLP_MAPPING_H
#define SQLP_MAPPING_H

#include <string>
#include <vector>

struct ReferenceMapping {
    std::string source_table;
    std::string feature;
    std::string source_column;
    std::string target_table;
    std::string target_column;
    bool operator==(const ReferenceMapping &other) const = default;
};

const ReferenceMapping &find_reference(
    const std::vector<ReferenceMapping> &references,
    const std::string &source_table,
    const std::string &feature
);

#endif