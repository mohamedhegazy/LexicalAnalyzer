#ifndef REGEX_H
#define REGEX_H
#include <string>
using namespace std;
#include "NFA.h"

        //when regexParser reads a regex it will create its nfa and store it in
        //the vector of regular expressions
class RegEx
{
    public:
        static const int KEYWORD_PRIORITY=0;//highest
        string name;
        NFA *transitions;
        int priority;//if keyword then highest priority

        RegEx();
        virtual ~RegEx();
    protected:
    private:
};

#endif // REGEX_H
