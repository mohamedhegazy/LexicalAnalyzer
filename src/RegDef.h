#ifndef REGDEF_H
#define REGDEF_H
#include <string>
using namespace std;
#include "NFA.h"
        //when regexParser reads a regular definition it will create its nfa and store it in the vector of regular definitions

class RegDef
{
    public:
        string name;
        NFA* transitions;

        RegDef();
        virtual ~RegDef();
    protected:
    private:
};

#endif // REGDEF_H
