#pragma once

#include <string>
#include "DBTable.hpp"

class Join {
public:
    string columnName;
    string joinColumnName;
    DBTable *joinTable;

    Join(string columnName, string joinColumnName, DBTable *joinTable) : columnName(columnName), joinColumnName(joinColumnName), joinTable(joinTable) {}
};