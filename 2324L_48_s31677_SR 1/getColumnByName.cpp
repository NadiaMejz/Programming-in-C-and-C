#include "GlobalHeader.hpp"

#include "classes/DBColumn.hpp"
#include "classes/DBTable.hpp"

extern std::list<DBTable *> *tables;

DBColumn *getColumnByName(string table, string column) {
    for (DBTable *t : *tables) {
        if (t->name == table) {
            for (DBColumn *c : *t->columns) {
                if (c->name == column) {
                    return c;
                }
            }
        }
    }
    return nullptr;
}