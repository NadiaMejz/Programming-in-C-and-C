#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBTable.hpp"

extern std::list<DBTable *> *tables;

extern DBTable *getTableByName(string table);
extern DBColumn *getColumnByName(string table, string column);

void deleteRecord() {
    string tableName;
    cin >> tableName;
    DBTable *table = getTableByName(tableName);
    if (table == nullptr) {
        throw runtime_error("Table doesn't exist");
    }
    string tag;
    cin >> tag;
    if (tag != "(") {
        throw runtime_error("Missing ( tag");
    }
    string columnName, value;
    cin >> columnName >> value;
    cin >> tag;
    if (tag != ")") {
        throw runtime_error("Missing ) tag");
    }

    for (auto it = table->rows->begin(); it != table->rows->end(); ++it) {
        DBRow *row = *it;
        if (row->matchesCondition(columnName, value)) {
            delete row;
            it = table->rows->erase(it);
            --it;
        }
    }
}