#ifndef SQLP_CATALOG_H
#define SQLP_CATALOG_H

#include "mapping.h"

#include <string>
#include <vector>

enum class ColumnType { Integer, String };

struct ColumnSchema {
    std::string name;
    ColumnType type;
    bool unique = false;
};

struct TableSchema {
    std::string name;
    std::vector<ColumnSchema> columns;
};

struct Catalog {
    std::vector<TableSchema> tables;
    std::vector<ReferenceMapping> references;
};

const ColumnSchema &find_column(
    const Catalog &catalog,
    const std::string &table_name,
    const std::string &column_name
);

#endif