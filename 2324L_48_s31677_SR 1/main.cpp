#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBRowValue.hpp"
#include "classes/DBRow.hpp"
#include "classes/DBTable.hpp"
#include "classes/Join.hpp"

list<DBTable *> *tables = new list<DBTable *>();

extern DBTable *getTableByName(string table);
extern DBColumn *getColumnByName(string table, string column);

extern void generateNewTable();
extern void putData();
extern void getData();
extern void save();
extern void read();
extern void deleteRecord();

int main() {
    while (true) {
        try {
            string tag;
            cout << "> ";
            cin >> tag;
            if (tag == TAG_QUIT) {
                break;
            } else if (tag == TAG_NEW_TABLE) {
                generateNewTable();
            } else if (tag == TAG_PUT) {
                putData();
            } else if (tag == TAG_GET) {
                getData();
            } else if (tag == TAG_SAVE) {
                save();
            } else if (tag == TAG_READ) {
                read();
            } else if (tag == TAG_DELETE) {
                deleteRecord();
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
}