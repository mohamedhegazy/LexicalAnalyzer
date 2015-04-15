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

        Production* get_next_production(Symbol* current, Token * token);//return table[current][token]
        virtual ~ParsingTable();
        string toString();
        string toString(int width);
        bool is_successful();
        vector<Symbol*> *get_symbols();
        Symbol* get_start_symbol();

    protected:
    private:
        ParsingTable();
        void generate_first_follow();
        void update_productions();
        void build_table();
        void set_table_entry(Symbol* s1, Symbol* s2, Production*p);
        bool table_entry_is_set(Symbol* s1, Symbol* s2);
        vector<Symbol*>*symbols;
        map<Symbol*, int> *terminals;
        map<Symbol*, int> *nonterminals;
        map<string, int> *tokens;
        Production * table[50][300];
        bool successful;
        Symbol* start_symbol;
        LL1 * ll1;
};

#endif // PARSINGTABLE_H
