#ifndef DFA_H
#define DFA_H
#include "State.h"
#include "NFA.h"
#include <vector>
#include <map>
#include "DFAState.h"
#include "string.h"
#include "NFA.h"
#include <algorithm>

class DFA
{
    public:
        DFA();
        DFA(NFA * nfa);//transfrom NFA to DFA and minimize it
        int move(int current_state, char trans_char);//get the next state for the transition char
        void moveDFA(DFAState* state_);
        void moveDFA(DFAState* state_,char trans_char);
        void print();//prints dfa as table
        void addDFAState(DFAState* dFAState_);//add a new dfa state and makes sure it doesn't already exist
        void Union(vector<State*>* st1,vector<State*>* st2);
        bool exist(vector<State*>* state_);
        virtual ~DFA();
    protected:
    private:
        std::string possibleTrans;
        NFA * nfa;
        std::vector<DFAState*> * states;
        std::vector<map<char,int>*> * table;
        void convertNFAtoDFA();
        void minimizeDFA();// using disjoint set will be cool



};

#endif // DFA_H
