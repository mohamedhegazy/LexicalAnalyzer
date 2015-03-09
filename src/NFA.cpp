#include "NFA.h"


NFA::NFA() {

    states = new vector<State*>();
    this->start_state = NULL;
    this->accepting_state = NULL;
}


NFA::NFA(TokenClass* start_state_token_class) {

    states = new vector<State*>();
    start_state = new State(start_state_token_class, true);
    accepting_state = start_state;
    states->push_back(start_state);

}




vector <State*>* NFA::closure(State current) {

}
vector<State*>* NFA::move(vector<State*>* current, char trans_char) {

}
NFA* NFA::oring(NFA* nfa) {

    NFA* result = new NFA();

    result->start_state = new State(TokenClass::epsilon, false);

    result->start_state->add_edge(this->start_state,TokenClass::epsilon_char);
    this->start_state->set_accepting(false);

    result->start_state->add_edge(nfa->start_state,TokenClass::epsilon_char);
    nfa->start_state->set_accepting(false);


    result->accepting_state = new State(TokenClass::epsilon, true);
    this->accepting_state->add_edge(nfa->accepting_state, TokenClass::epsilon_char);
    nfa->accepting_state->add_edge(nfa->accepting_state, TokenClass::epsilon_char);


    result->states->push_back(result->start_state);
    result->states->push_back(result->accepting_state);
    for(int i = 0; i < this->states->size(); i++) {
        result->states->push_back(this->states->at(i));
    }

    for(int i = 0; i < nfa->states->size(); i++) {
        result->states->push_back(nfa->states->at(i));
    }


    return result;

}
NFA* NFA::concatenation(NFA* nfa) {

}
NFA* NFA::kleene_closure() {

}
NFA* NFA::positive_closure() {

}
NFA* NFA::join_start_state() {

}

void NFA::set_accepting_state(State* accepting_state) {
    this->accepting_state = accepting_state;
}


void NFA::NFA_print() {


    cout<<"----------------------------------------"<<endl;
    cout<<"start printing NFA"<<endl;


    TokenClass*g ;
    if(start_state != NULL) {
        g  = start_state->get_token_class();
        cout<<"start state: "<<g->name<<", "<<g->priority<<endl;
    }
    else {
        cout<<"start state is NULL !"<<endl;
    }




    if(accepting_state != NULL) {
        g = accepting_state->get_token_class();
        cout<<"accepting state: "<<g->name<<", "<<g->priority<<endl;
    }
    else {
        cout<<"accepting state is NULL !"<<endl;
    }



    if(states != NULL){
        cout<<"states # : "<<states->size()<<endl;
        for(int i = 0; i < states->size(); i++) {
            states->at(i)->state_print();
        }
    }
    else {
        cout<<"states vector is NULL !"<<endl;
    }

    cout<<"dont printing NFA"<<endl;
    cout<<"----------------------------------------"<<endl;
}

NFA::~NFA() {

}












