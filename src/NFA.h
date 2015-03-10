#ifndef NFA_H
#define NFA_H
#include "State.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <string.h>
#include <map>

class NFA
{
    public:

        static NFA* get_letter();
        static NFA* get_letters();
        static NFA* get_digit();
        static NFA* get_digits();
        static NFA* get_string(string str);


        NFA();
        NFA(TokenClass *start_state_token_class, char trans_char);
        NFA(char c);
        vector <State*>* closure(State* current);
        vector<State*>* move(vector<State*>* current, char trans_char);
        vector<State*>* move(string str);
        NFA* oring(NFA* nfa);
        NFA* concatenation(NFA* nfa);
        NFA* kleene_closure();
        NFA* positive_closure();
        NFA* join_NFAs(vector<NFA*>* nfas);
        NFA* clone();
        void set_accepting_state(State* accepting_state);
        void NFA_print();
        State * get_start_state();
        bool acceptes(string str);
        virtual ~NFA();
    protected:
    private:

        vector<State*>*states;
        State *start_state;
        State *accepting_state;//null if there is multiple accepting states
};

#endif // NFA_H
