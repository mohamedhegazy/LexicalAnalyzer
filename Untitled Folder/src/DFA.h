#ifndef DFA_H
#define DFA_H
#include "State.h"

class DFA
{
    public:
        DFA();
        DFA(*NFA);//transfrom NFA to DFA and minimize it
        State move(State current,char input);
        void print();//prints dfa as table
        virtual ~DFA();
    protected:
    private:
           State start;
           void convertNFAtoDFA();
           void minimizeDFA();// using disjoint set will be cool



};

#endif // DFA_H
