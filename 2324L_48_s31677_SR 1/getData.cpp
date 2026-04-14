#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBTable.hpp"
#include "classes/Join.hpp"

extern std::list<DBTable *> *tables;

extern DBTable *getTableByName(string table);
extern DBColumn *getColumnByName(string table, string column);

void getData() {
    string tableName;
    cin >> tableName;
    DBTable *table = getTableByName(tableName);
    if (table == nullptr) {
        throw runtime_error("Table doesn't exist");
    }
    string tag;
    cin >> tag;
    if (tag != "(") {
        throw runtime_error("Missing '(' ");
    }
    list<string> selectedColumns;
    cin >> tag;
    while (tag != ")") {
        DBColumn *column = getColumnByName(tableName, tag);
        if (column == nullptr) {
            throw runtime_error("Column doesn't exist(1)");
        }
        selectedColumns.push_back(tag);
        cin >> tag;
    }
    list<Join> joinTables;
    cin >> tag;
    while (tag == TAG_JOIN) {
        string joinTableName;
        cin >> joinTableName;
        DBTable *joinTable = getTableByName(joinTableName);
        if (joinTable == nullptr) {
            throw runtime_error("Table doesn't exist");
        }
        cin >> tag;
        if (tag != "(") {
            throw runtime_error("Missing '(' ");
        }
        cin >> tag;
        while (tag != ")") {
            DBColumn *column = getColumnByName(joinTableName, tag);
            if (column == nullptr) {
                throw runtime_error("Column doesn't exist(2)");
            }
            selectedColumns.push_back(tag);
            cin >> tag;
        }
        string fromColumn, toColumn;
        cin >> fromColumn >> toColumn;
        DBColumn *column1 = getColumnByName(tableName, fromColumn);
        DBColumn *column2 = getColumnByName(joinTableName, toColumn);
        if (column1 == nullptr || column2 == nullptr) {
            throw runtime_error("Wrong joined columns names");
        }
        joinTables.push_back(Join(fromColumn, toColumn, joinTable));
        cin >> tag;
    }
    list<DBRow *> rows = *table->rows;
    if (!joinTables.empty()) {
        list<DBRow> joinedRows;
        for (DBRow *row : rows) {
            DBRow newRow(new list<DBRowValue *>);
            list<DBRowValue *> joinedValues;
            for (DBRowValue *value : *row->rowValues) {
                joinedValues.push_back(new DBRowValue(value->columnName, value->value));
            }
            bool validJoin = true;
            for (Join &join : joinTables) {
                string originTableValue = "";
                for (DBRowValue *value : *row->rowValues) {
                    if (value->columnName == join.columnName) {
                        originTableValue = value->value;
                        break;
                    }
                }
                if (originTableValue == "") {
                    validJoin = false;
                    break;
                }
                list<DBRow *> joinRows = *join.joinTable->rows;
                bool joinFound = false;
                for (DBRow *joinRow : joinRows) {
                    for (DBRowValue *joinValue : *joinRow->rowValues) {
                        if (joinValue->columnName == join.joinColumnName && joinValue->value == originTableValue) {
                            for (DBRowValue *joinValue2 : *joinRow->rowValues) {
                                joinedValues.push_back(new DBRowValue(joinValue2->columnName, joinValue2->value));
                            }
                            joinFound = true;
                            break;
                        }
                    }
                    if (joinFound) break;
                }
                if (!joinFound) {
                    validJoin = false;
                    break;
                }
            }
            if (validJoin) {
                newRow.rowValues = new list<DBRowValue *>(joinedValues);
                joinedRows.push_back(newRow);
            }
        }
        rows.clear();
        for (DBRow &joinedRow : joinedRows) {
            rows.push_back(&joinedRow);
        }
    }
    while (tag == TAG_CONDITION) {
        cin >> tag;
        if (tag != "(") {
            throw runtime_error("Missing '('");
        }
        string columnName, condition, value;
        cin >> columnName >> condition >> value;
        cin >> tag;
        if (tag != ")") {
            throw runtime_error("Missing ')'");
        }
        DBColumn *column = getColumnByName(tableName, columnName);
        if (column == nullptr) {
            throw runtime_error("Column doesn't exist(2)");
        }
        for (auto it = rows.begin(); it != rows.end();) {
            DBRow *row = *it;
            bool shouldEraseRow = false;
            list<DBRowValue *> *rowValues = row->rowValues;
            for (DBRowValue *valueIt : *rowValues) {
                if (columnName == valueIt->columnName) {
                    if (column->type == TYPE_STRING) {
                        if (condition == "==" && valueIt->value != value) {
                            shouldEraseRow = true;
                            break;
                        } else if (condition == "!=" && valueIt->value == value) {
                            shouldEraseRow = true;
                            break;
                        }
                    } else if (column->type == TYPE_INT) {
                        int value1, value2;
                        try {
                            value1 = stoi(value);
                            value2 = stoi(valueIt->value);
                        } catch (...) {
                            throw runtime_error("Invalid data type");
                        }
                        if (condition == "==" && value1 != value2) {
                            shouldEraseRow = true;
                            break;
                        } else if (condition == "!=" && value1 == value2) {
                            shouldEraseRow = true;
                            break;
                        } else if (condition == "<" && value2 >= value1) {
                            shouldEraseRow = true;
                            break;
                        } else if (condition == ">" && value2 <= value1) {
                            shouldEraseRow = true;
                            break;
                        }
                    } else if (column->type == TYPE_REAL) {
                        float value1, value2;
                        try {
                            value1 = stof(value);
                            value2 = stof(valueIt->value);
                        } catch (...) {
                            throw runtime_error("Invalid data type");
                        }
                        if (condition == "==" && value1 != value2) {
                            shouldEraseRow = true;
                            break;
                        } else if (condition == "!=" && value1 == value2) {
                            shouldEraseRow = true;
                            break;
                        } else if (condition == "<" && value2 >= value1) {
                            shouldEraseRow = true;
                            break;
                        } else if (condition == ">" && value2 <= value1) {
                            shouldEraseRow = true;
                            break;
                        }
                    }
                }
            }
            if (shouldEraseRow) {
                it = rows.erase(it);
            } else {
                it++;
            }
        }
        cin >> tag;
    }

    // Handling Sorting
    string sortColumn;
    string sortOrder;
    if (tag == TAG_ASC || tag == TAG_DESC) {
        sortOrder = tag;
        cin >> sortColumn;
        DBColumn *sortCol = getColumnByName(tableName, sortColumn);
        if (sortCol == nullptr) {
            throw runtime_error("Column doesn't exist for sorting");
        }
        rows.sort([&sortColumn, &sortOrder](DBRow *a, DBRow *b) {
            string valueA, valueB;
            for (DBRowValue *val : *a->rowValues) {
                if (val->columnName == sortColumn) {
                    valueA = val->value;
                    break;
                }
            }
            for (DBRowValue *val : *b->rowValues) {
                if (val->columnName == sortColumn) {
                    valueB = val->value;
                    break;
                }
            }
            if (sortOrder == TAG_ASC) {
                return valueA < valueB;
            } else {
                return valueA > valueB;
            }
        });
        cin >> tag;
    }

    if (tag != TAG_GET_END) {
        throw runtime_error("Missing 'END'");
    }
    if (!rows.empty()) {
        for (string &col : selectedColumns) {
            cout << col << "\t";
        }
        cout << endl;
        for (DBRow *row : rows) {
            for (string &col : selectedColumns) {
                for (DBRowValue *value : *row->rowValues) {
                    if (col == value->columnName) {
                        cout << value->value << "\t";
                    }
                }
            }
            cout << endl;
        }
    }
}
