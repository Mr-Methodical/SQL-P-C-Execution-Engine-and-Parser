#ifndef SQLP_MAPPING_H
#define SQLP_MAPPING_H

#include <string>
#include <vector>

// ex. ReferenceMapping{"WROTE", "author", "author_aid", "AUTHOR", "aid"};
// maps the ARM feature w.author to the SQL relationship:
// JOIN AUTHOR AS a ON w.author_aid = a.aid
// this allows us to resolve a path like w.author.name into a.name.
struct ReferenceMapping {
    std::string source_table;
    std::string feature;
    std::string source_column;
    std::string target_table;
    std::string target_column;
    bool operator==(const ReferenceMapping &other) const = default;
};

// will take in a feature which is what we are mapping the source table to
// and we will return a reference to it so that we know how to join them
const ReferenceMapping &find_reference(
    const std::vector<ReferenceMapping> &references,
    const std::string &source_table,
    const std::string &feature
);

#endif