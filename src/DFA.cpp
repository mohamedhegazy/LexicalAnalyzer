
#include "DFA.h"

DFA::DFA()
{

}

DFA::DFA(NFA * nfa) {
    states = new vector<DFAState*>();
    convertNFAtoDFA(nfa);
}


void DFA::convertNFAtoDFA(NFA * nfa) {

    vector<State*>*origing = nfa->get_states();

    map<string,DFAState*>* mapper = new map<string,DFAState*>();

    start_state = new DFAState();
    string sssss = *set_to_string(nfa->closure(nfa->get_start_state()), origing);

    (*mapper)[sssss] = start_state;

    queue<vector<State*>*>* q = new queue<vector<State*>*>();
    q->push(nfa->closure(nfa->get_start_state()));


    while(!q->empty()) {

        vector<State*> *v = q->front();
        q->pop();
        string str = *set_to_string(v, origing);

        DFAState* current_state = mapper->at(str);

        TokenClass* t = TokenClass::epsilon;
        for(int i = 0; i < (int)v->size(); i++) {
            if(v->at(i)->get_accepting() && t->priority > v->at(i)->get_token_class()->priority) {
                t = v->at(i)->get_token_class();
                current_state->set_accepting(true);
            }
        }
        current_state->set_tokenClass(t);
        states->push_back(current_state);

        for(int i = -127; i < 128; i++) {
            char trans_char = (char)i;

            vector<State*>*r = nfa->move(v, trans_char);

            if(r->size() != 0) {
                string str2 = *set_to_string(r, origing);
                DFAState *st = NULL;

                if(mapper->find(str2) != mapper->end()) {
                   st = mapper->at(str2);
                }
                else {
                    st = new DFAState();
                    (*mapper)[str2] = st;
                    q->push(r);
                }

                current_state->add_edge(st, trans_char);

            }

        }


    }


}


 bool DFA::accepts(string str) {
    DFAState * state = start_state->move(str);
    if(state == NULL)
        return false;

    return state->get_accepting();
 }

 vector<DFAState*>* DFA::get_states() {
    return states;
 }


string* DFA::set_to_string(vector<State*>*r, vector<State*>*origin) {

    map<State*,int>m;
    for(int i = 0; i < (int)r->size(); i++) {
        m[r->at(i)] = 0;
    }

    int n = origin->size();

    char *c = new char [n+1];

    for(int i = 0; i < n; i++) {
        if(m.find(origin->at(i)) == m.end()) {
            c[i] = '0';
        }
        else {
            c[i] = '1';
        }
    }

    c[n] = '\0';
    string *s = new string(c);

    return s;
}

void DFA::minimizeDFA() {

}

 DFAState* DFA::get_start_state() {
    return start_state;
 }


DFA::~DFA()
{
    //dtor
}

