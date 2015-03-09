#ifndef NFA_H
#define NFA_H
#include "State.h"
#include <stdio.h>
#include <iostream>
#include <vector>
class NFA
{
    public:
        NFA();
        NFA(TokenClass *start_state_token_class);
        vector <State*>* closure(State current);
        vector<State*>* move(vector<State*>* current, char trans_char);
        NFA* oring(NFA* nfa);
        NFA* concatenation(NFA* nfa);
        NFA* kleene_closure();
        NFA* positive_closure();
        NFA* join_start_state();
        void set_accepting_state(State* accepting_state);
        void NFA_print();
        virtual ~NFA();
    protected:
    private:

        vector<State*>*states;
        State *start_state;
        State *accepting_state;//null if there is multiple accepting states
};

#endif // NFA_H
