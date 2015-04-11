#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H
#include "Token.h"
#include "Symbol.h"
#include "LL1.h"
#include "Production.h"
#include <map>
#include <sstream>
#include <iomanip>
#include "TokenClass.h"

using namespace std;
class ParsingTable
{
    public:
    //takes LL1 grammar and gets the first and follow sets of each production

        ParsingTable(LL1* ll1);
        Symbol* start_symbol;
        Production* get_next_production(Symbol* current, Token * token);//return table[current][token]
        ParsingTable();
        virtual ~ParsingTable();
        string toString();
        string toString(int width);
    protected:
    private:
        void generate_first_follow();
        void update_productions();
        void build_table();
        vector<Symbol*>*symbols;
        map<Symbol*, int> *terminals;
        map<Symbol*, int> *nonterminals;
        Production * table[50][300];
        LL1 * ll1;
};

#endif // PARSINGTABLE_H
