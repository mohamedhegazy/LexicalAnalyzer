#ifndef DFA_H
#define DFA_H
#include "State.h"
#include <vector>
#include <map>

class DFA
{
    public:
        DFA();
        DFA(*NFA);//transfrom NFA to DFA and minimize it
        int move(int current_state, char trans_char);//get the next state for the transition char
        void print();//prints dfa as table
        virtual ~DFA();
    protected:
    private:
        vector<map<char,int>*> * table;
        void convertNFAtoDFA();
        void minimizeDFA();// using disjoint set will be cool



};

#endif // DFA_H
