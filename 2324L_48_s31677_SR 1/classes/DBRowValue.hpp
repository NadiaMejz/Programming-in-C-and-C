#pragma once

#include <string>

using namespace std;

class DBRowValue {
public:
    string columnName;
    string value;

    DBRowValue(string columnName, string value) : columnName(columnName), value(value) {}
};