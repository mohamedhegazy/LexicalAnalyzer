#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <vector>
#include "Production.h"
using namespace std;
class Production;
class Symbol
{
    public:
        Symbol();
        Symbol(bool terminal,string name);
        bool is_nullable;
        bool is_terminal;
        bool just_added;
        string name;
        vector<Production *>* productions;
        vector<Symbol *>* first;
        vector<Symbol *>* follow;
        virtual ~Symbol();
    protected:
    private:
};

#endif // SYMBOL_H
