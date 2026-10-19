#include "sql.h"

#include <stdexcept>

std::string render_column(const ColumnRef &column) {
    return column.alias + "." + column.column;
}

std::string render_join(const JoinSpec &join) {
    return "JOIN " + join.target_table +
           " AS " + join.target.alias +
           " ON " + render_column(join.source) +
           " = " + render_column(join.target);
}

std::string render_join(
    const ReferenceMapping &mapping,
    const std::string &source_alias,
    const std::string &target_alias
) {
    return render_join(JoinSpec{
        mapping.target_table,
        {source_alias, mapping.source_column},
        {target_alias, mapping.target_column}
    });
}

ResolvedPath resolve_path(
    const Path &path,
    const std::string &source_table,
    const std::string &target_alias,
    const Catalog &catalog
) {
    if (path.features().size() != 2) {
        throw std::invalid_argument{
            "This resolver requires exactly two features"
        };
    }

    const ReferenceMapping &mapping = find_reference(
        catalog.references, source_table, path.features()[0]
    );

    find_column(catalog, source_table, mapping.source_column);
    find_column(catalog, mapping.target_table, mapping.target_column);
    find_column(catalog, mapping.target_table, path.features()[1]);

    const JoinSpec join{
        mapping.target_table,
        {path.root(), mapping.source_column},
        {target_alias, mapping.target_column}
    };

    const ColumnRef column{target_alias, path.features()[1]};

    return ResolvedPath{join, column};
}