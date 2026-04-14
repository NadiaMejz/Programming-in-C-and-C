#pragma once

#include <string>

using namespace std;


class DBColumn {
public:
    string name;
    int type;
    string attribute;
    string foreignTableName;
    string foreignTableColumn;

    DBColumn(string name, int type, string attribute)
        : name(name), type(type), attribute(attribute) {} // parameterized constructor

    DBColumn(string name, int type, string attribute, string foreignTableName, string foreignTableColumn)
        : name(name), type(type), attribute(attribute), foreignTableName(foreignTableName), foreignTableColumn(foreignTableColumn) {} // parameterized constructor
};