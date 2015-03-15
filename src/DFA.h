#ifndef DFA_H
#define DFA_H
#include "State.h"
#include "NFA.h"
#include "DFAState.h"
#include "State.h"
#include <vector>
#include <map>
#include <queue>
#include <string>

using namespace std;

class DFA
{
    public:
        DFA();
        DFA(NFA * nfa);//transfrom NFA to DFA and minimize it
        int move(int current_state, char trans_char);//get the next state for the transition char
        void print();//prints dfa as table
        DFAState* get_start_state();
        vector<DFAState*>*get_states();
        bool accepts(string str);
        virtual ~DFA();
    protected:
    private:
        void convertNFAtoDFA(NFA* nfa);
        string* set_to_string(vector<State*>*r, vector<State*> * origin);
        void minimizeDFA();// using disjoint set will be cool
        DFAState*start_state;
        vector<DFAState*>*states;


};

#endif // DFA_H
