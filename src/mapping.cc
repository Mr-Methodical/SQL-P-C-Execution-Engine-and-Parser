#include "mapping.h"

#include <stdexcept>

const ReferenceMapping &find_reference(
    const std::vector<ReferenceMapping> &references,
    const std::string &source_table,
    const std::string &feature
) {
    for (const auto &ref : references) {
        if (ref.source_table == source_table && ref.feature == feature) {
            return ref;
        }
    }
    // invalid argument as there is no source table and feature in references
    throw std::invalid_argument{
        "references doesn't contain source table and feature mapping"
    };
}