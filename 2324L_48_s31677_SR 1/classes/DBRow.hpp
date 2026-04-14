#pragma once

#include <list>
#include "DBRowValue.hpp"

class DBRow {
public:
    list<DBRowValue *> *rowValues;

    DBRow(list<DBRowValue *> *rowValues) : rowValues(rowValues) {}
    bool matchesCondition(string columnName, string value) {
        for (DBRowValue *rowValue : *rowValues) {
            if (rowValue->columnName == columnName && rowValue->value == value) {
                return true;
            }
        }
        return false;
    }
};