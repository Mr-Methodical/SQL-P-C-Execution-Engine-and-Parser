#include "catalog.h"

#include <stdexcept>

// we take our catalog and get told the table it is in and the column
// and we return that table, but throw if it is not there
const ColumnSchema &find_column(
    const Catalog &catalog,
    const std::string &table_name,
    const std::string &column_name
) {
    // go through all tables, check if equal to our table name
    // once we find the row, cycle through all columns to find our column
    for (const auto &table : catalog.tables) {
        if (table.name == table_name) {
            for (const auto &column : table.columns) {
                if (column.name == column_name) {
                    return column;
                }
            }

            throw std::invalid_argument{
                "Unknown column: " + table_name + "." + column_name
            };
        }
    }

    throw std::invalid_argument{"Unknown table: " + table_name};
}