#ifndef PRODUCTION_H
#define PRODUCTION_H
#include "Symbol.h"
#include <vector>
#include <set>
#include <iostream>
using namespace std;

class Symbol;
class Production
{
    public:

        static Production * sync;
        Production();
        vector<Symbol*>* RHS;
        Symbol* LHS;
        string toString();
        virtual ~Production();

        bool is_nullable;
        set<Symbol*>*first;
    protected:
    private:
};

#endif // PRODUCTION_H
