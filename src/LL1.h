#ifndef LL1_H
#define LL1_H
#include <string>
#include "Symbol.h"
#include <vector>
using namespace std;
//reads CFG and eliminates left-recusrion and performs left-factoring
class LL1
{
    public:
        LL1();
        LL1(string input_rules);//reads CFG and eliminates left-recusrion and performs left-factoring
        vector<Symbol*> *symbols;
        Symbol* start_symbol;

        virtual ~LL1();
    protected:
    private:
};

#endif // LL1_H
