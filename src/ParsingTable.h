#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H
#include "Token.h"
#include "Symbol.h"
#include "LL1.h"
#include "Production.h"
#include <map>

using namespace std;
class ParsingTable
{
    public:
    //takes LL1 grammar and gets the first and follow sets of each production

        ParsingTable(LL1* ll1);
        map< Symbol*, map<Token*,Production*> > table;
        Symbol* start_symbol;
        Production* get_next_production(Symbol* current, Token * token);//return table[current][token]
        ParsingTable();
        virtual ~ParsingTable();
    protected:
    private:
};

#endif // PARSINGTABLE_H
