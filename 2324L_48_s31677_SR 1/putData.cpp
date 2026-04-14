#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBTable.hpp"

extern std::list<DBTable *> *tables;

extern DBTable *getTableByName(string table);
extern DBColumn *getColumnByName(string table, string column);

void putData() {
    string tableName;
    cin >> tableName;
    DBTable *table = getTableByName(tableName);
    if (table == nullptr) {
        throw runtime_error("Table doesn't exist");
    }
    string tag;
    cin >> tag;
    if (tag != "(") {
        throw runtime_error("missing ( tag");
    }
    string columnName = "";
    string columnValue = "";
    list<DBRowValue *> *rowValues = new list<DBRowValue *>();
    cin >> tag;
    while (tag != ")") {
        columnName = tag;
        cin >> tag;
        if (tag == ")") {
            throw runtime_error("Missing column value");
        }
        columnValue = tag;
        DBColumn *column = getColumnByName(tableName, columnName);
        if (column == nullptr) {
            throw runtime_error("Column doesn't exist");
        }
        if (column->type == TYPE_STRING) {
            rowValues->push_back(new DBRowValue(columnName, columnValue));
        } else if (column->type == TYPE_INT) {
            try {
                stoi(columnValue); // convert string to int
                rowValues->push_back(new DBRowValue(columnName, columnValue));
            } catch (...) {
                throw runtime_error("Value should be an integer");
            }
        } else if (column->type == TYPE_REAL) {
            try {
                stof(columnValue); // convert string to float
                rowValues->push_back(new DBRowValue(columnName, columnValue));
            } catch (...) {
                throw runtime_error("Value should be a real");
            }
        }
        cin >> tag;
    }
    table->rows->push_back(new DBRow(rowValues));
}