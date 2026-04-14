#include "GlobalHeader.hpp"

#include "classes/DBTable.hpp"

extern std::list<DBTable *> *tables;

DBTable *getTableByName(string table) {
    for (DBTable *t : *tables) {
        if (t->name == table) {
            return t;
        }
    }
    return nullptr;
}