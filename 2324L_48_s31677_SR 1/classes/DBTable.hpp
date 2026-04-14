#pragma once

#include <list>
#include "DBColumn.hpp"
#include "DBRow.hpp"

class DBTable {
public:
    string name;
    list<DBColumn *> *columns;
    list<DBRow *> *rows;

    DBTable(string name, list<DBColumn *> *columns) : name(name), columns(columns), rows(new list<DBRow *>()) {}
};