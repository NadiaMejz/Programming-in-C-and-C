#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBRow.hpp"
#include "classes/DBRowValue.hpp"
#include "classes/DBTable.hpp"

extern std::list<DBTable *> *tables;

void save() {
    string tag;
    cin >> tag;
    if (tag != "TO") {
        throw runtime_error("Missing 'TO' tag!");
    }
    string file;
    cin >> file;
    if (file.substr(file.find_last_of(".") + 1) != "nadia") {
        throw runtime_error("Invalid file extension, use .nadia");
    }
    ofstream outFile(file);
    if (!outFile) {
        throw runtime_error("Cannot open file for writing");
    }
    for (DBTable *table : *tables) {
        outFile << "TABLE " << table->name << endl << "(" << endl;
        for (DBColumn *col : *table->columns) {
            outFile << col->name << " " << col->type << " " << col->attribute << " " << col->foreignTableName << " " << col->foreignTableColumn << endl;
        }
        outFile << ")" << endl;
        for (DBRow *row : *table->rows) {
            outFile << "ROW" << endl << "(" << endl;
            for (DBRowValue *value : *row->rowValues) {
                outFile << value->columnName << " " << value->value << endl;
            }
            outFile << ")" << endl;
        }
    }
    outFile.close();
}