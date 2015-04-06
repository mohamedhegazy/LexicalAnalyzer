#ifndef PRODUCTION_H
#define PRODUCTION_H
#include "Symbol.h"
#include <vector>
using namespace std;

class Symbol;
class Production
{
    public:
        Production();
        vector<Symbol*>* RHS;
        Symbol* LHS;

        virtual ~Production();
    protected:
    private:
};

#endif // PRODUCTION_H
