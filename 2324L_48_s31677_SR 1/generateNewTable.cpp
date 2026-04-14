#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBTable.hpp"

extern std::list<DBTable *> *tables;

extern DBColumn *getColumnByName(string table, string column);

void generateNewTable() {
    string tableName;
    cin >> tableName;
    string tag;
    cin >> tag;
    if (tag != "(") {
        throw runtime_error("missing ( tag");
    }
    string columnName = "";
    string columnType = "";
    list<DBColumn *> *columns = new list<DBColumn *>();
    cin >> tag;
    while (tag != ")") {
        columnName = tag;
        cin >> columnType;
        if (columnType == ")") {
            throw runtime_error("invalid column definition");
        }
        if (columnType == TYPE_STRING_NAME) {
            columns->push_back(new DBColumn(columnName, TYPE_STRING, ATTRIBUTE_DEFAULT));
        } else if (columnType == TYPE_INT_NAME) {
            columns->push_back(new DBColumn(columnName, TYPE_INT, ATTRIBUTE_DEFAULT));
        } else if (columnType == TYPE_REAL_NAME) {
            columns->push_back(new DBColumn(columnName, TYPE_REAL, ATTRIBUTE_DEFAULT));
        } else if (columnType == ATTRIBUTE_PRIMARY) {
            columns->push_back(new DBColumn(columnName, TYPE_INT, ATTRIBUTE_PRIMARY));
        } else if (columnType == ATTRIBUTE_FOREIGN) {
            string foreignTableName;
            string foreignTableColumn;
            cin >> foreignTableName;
            cin >> foreignTableColumn;
            DBColumn *foreignColumn = getColumnByName(foreignTableName, foreignTableColumn);
            if (foreignColumn != nullptr && foreignColumn->attribute == ATTRIBUTE_PRIMARY) {
                columns->push_back(new DBColumn(columnName, TYPE_INT, ATTRIBUTE_FOREIGN, foreignTableName, foreignTableColumn));
            } else {
                throw runtime_error("Invalid foreign key definition");
            }
        } else {
            throw runtime_error("Invalid column type");
        }
        cin >> tag;
    }
    tables->push_back(new DBTable(tableName, columns));
}
