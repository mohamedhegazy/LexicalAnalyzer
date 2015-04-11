#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <vector>
#include "Production.h"
#include "TokenClass.h"
#include <set>

using namespace std;
class Production;
class Symbol
{
    public:
        static Symbol*$;
        static Symbol*espilon;

        Symbol();
        Symbol(bool terminal,string name);
        bool is_nullable;
        bool is_originaly_nullable;
        Production* null_production;
        bool is_terminal;
        bool just_added;
        string name;
        vector<Production *>* productions;
        set<Symbol *>* first;
        set<Symbol *>* follow;
        virtual ~Symbol();
        void set_nullabel();
    protected:
    private:
};

#endif // SYMBOL_H
