#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBTable.hpp"
#include "classes/DBRowValue.hpp"
#include "classes/DBRow.hpp"

extern list<DBTable *> *tables;

void read() {
    string tag;
    cin >> tag;
    if (tag != "FROM") {
        throw runtime_error("Missing 'FROM' tag!");
    }
    string file;
    cin >> file;
    if (file.substr(file.find_last_of(".") + 1) != "nadia") {
        throw runtime_error("Invalid file extension, use .nadia");
    }
    ifstream inFile(file);
    if (!inFile) {
        throw runtime_error("Cannot open file for reading");
    }
    tables->clear();
    string line;
    while (getline(inFile, line)) {
        if (line.find("TABLE") == 0) {
            string tableName = line.substr(6);
            getline(inFile, line);
            if (line != "(") {
                throw runtime_error("Invalid file format");
            }
            list<DBColumn *> *columns = new list<DBColumn *>();
            while (getline(inFile, line) && line != ")") {
                stringstream ss(line);
                string colName, attr, foreignTable, foreignColumn;
                int type;
                ss >> colName >> type >> attr >> foreignTable >> foreignColumn;
                if (attr == ATTRIBUTE_FOREIGN) {
                    columns->push_back(new DBColumn(colName, type, attr, foreignTable, foreignColumn));
                } else {
                    columns->push_back(new DBColumn(colName, type, attr));
                }
            }
            tables->push_back(new DBTable(tableName, columns));
        } else if (line.find("ROW") == 0) {
            list<DBRowValue *> *rowValues = new list<DBRowValue *>();
            getline(inFile, line);
            if (line != "(") {
                throw runtime_error("Invalid file format");
            }
            while (getline(inFile, line) && line != ")") {
                stringstream ss(line);
                string colName, value;
                ss >> colName >> value;
                rowValues->push_back(new DBRowValue(colName, value));
            }
            tables->back()->rows->push_back(new DBRow(rowValues));
        }
    }
    inFile.close();
}