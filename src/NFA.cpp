#include "NFA.h"


NFA::NFA() {

    states = new vector<State*>();
    this->start_state = NULL;
    this->accepting_state = NULL;
}


NFA::NFA(TokenClass* start_state_token_class,char trans_char) {

    states = new vector<State*>();
    accepting_state = new State(start_state_token_class, true);
    start_state = new State(TokenClass::epsilon, false);
    states->push_back(start_state);
    states->push_back(accepting_state);

    start_state->add_edge(accepting_state, trans_char);

}




vector <State*>* NFA::closure(State* current) {

        set<State*> *visited = new set<State*>();
        visited->insert(current);
        queue<State*>* q = new queue<State*>();
        q->push(current);

        State *s;
        while(!q->empty()) {
            s = q->front();
            q->pop();

            vector<Edge*>* e = s->get_adjList();

            for(int i = 0 ; i < e->size(); i++) {
                Edge *ed = e->at(i);
                if(ed->get_trans_char() == TokenClass::epsilon_char &&
                    visited->find(ed->get_to_State()) == visited->end()) {
                    visited->insert(ed->get_to_State());
                    q->push(ed->get_to_State());
                }
            }

        }


        return new vector<State*>(visited->begin(), visited->end());
}


vector<State*>* NFA::move(vector<State*>* current, char trans_char) {


    set<State*> *tmp = new set<State*>();

    for(int i = 0; i < current->size(); i++) {

        vector<Edge*>* e = current->at(i)->get_adjList();

        for(int j = 0; j < e->size(); j++) {
            if(e->at(j)->get_trans_char() == trans_char &&
                tmp->find(e->at(j)->get_to_State()) == tmp->end()) {
                tmp->insert(e->at(j)->get_to_State());
            }
        }

    }


    set<State*> *result = new set<State*>();

   for(set<State*>::iterator it = tmp->begin(); it != tmp->end(); it++) {
        vector<State*> *t = this->closure(*it);
        for(int i = 0; i < t->size(); i++) {
            result->insert(t->at(i));
        }
   }

    return new vector<State*>(result->begin(), result->end());
}




NFA* NFA::oring(NFA* nfa) {

    NFA* result = new NFA();

    result->start_state = new State(TokenClass::epsilon, false);

    result->start_state->add_edge(this->start_state,TokenClass::epsilon_char);
    this->start_state->set_accepting(false);

    result->start_state->add_edge(nfa->start_state,TokenClass::epsilon_char);
    nfa->start_state->set_accepting(false);


    result->accepting_state = new State(TokenClass::epsilon, true);
    this->accepting_state->add_edge(result->accepting_state, TokenClass::epsilon_char);
    this->accepting_state->set_accepting(false);
    nfa->accepting_state->add_edge(result->accepting_state, TokenClass::epsilon_char);
    nfa->accepting_state->set_accepting(false);

    result->states->push_back(result->start_state);

    for(int i = 0; i < this->states->size(); i++) {
        result->states->push_back(this->states->at(i));
    }

    for(int i = 0; i < nfa->states->size(); i++) {
        result->states->push_back(nfa->states->at(i));
    }

    result->states->push_back(result->accepting_state);
    return result;

}
NFA* NFA::concatenation(NFA* nfa) {

    NFA* result = new NFA();

    result->start_state = new State(TokenClass::epsilon, false);

    result->start_state->add_edge(this->start_state, TokenClass::epsilon_char);
    this->start_state->set_accepting(false);


    this->accepting_state->set_accepting(false);
    this->accepting_state->add_edge(nfa->start_state, TokenClass::epsilon_char);

    nfa->accepting_state->set_accepting(false);

    result->accepting_state = new State(TokenClass::epsilon, false);

    nfa->accepting_state->add_edge(result->accepting_state, TokenClass::epsilon_char);

    result->states->push_back(result->start_state);


    for(int i = 0; i < this->states->size(); i++) {
        result->states->push_back(this->states->at(i));
    }

     for(int i = 0; i < nfa->states->size(); i++) {
        result->states->push_back(nfa->states->at(i));
    }

    result->states->push_back(result->accepting_state);

    return result;

}


NFA* NFA::kleene_closure() {

    State* new_start_state = new State(TokenClass::epsilon, false);
    State* new_acceping_state = new State(TokenClass::epsilon, false);


    new_start_state->add_edge(this->start_state, TokenClass::epsilon_char);
    this->accepting_state->add_edge(new_acceping_state, TokenClass::epsilon_char);

    new_start_state->add_edge(new_acceping_state, TokenClass::epsilon_char);
    this->accepting_state->add_edge(this->start_state, TokenClass::epsilon_char);

    this->accepting_state->set_accepting(false);

    new_acceping_state->set_accepting(true);

    this->accepting_state = new_acceping_state;
    this->start_state = new_start_state;

    states->push_back(new_acceping_state);
    states->push_back(new_start_state);

    return this;

}

NFA* NFA::positive_closure() {
State* new_start_state = new State(TokenClass::epsilon, false);
    State* new_acceping_state = new State(TokenClass::epsilon, false);

    new_start_state->add_edge(this->start_state, TokenClass::epsilon_char);
    this->accepting_state->add_edge(new_acceping_state, TokenClass::epsilon_char);

    this->accepting_state->add_edge(this->start_state, TokenClass::epsilon_char);

    this->accepting_state->set_accepting(false);

    new_acceping_state->set_accepting(true);

    this->accepting_state = new_acceping_state;
    this->start_state = new_start_state;

    states->push_back(new_acceping_state);
    states->push_back(new_start_state);

    return this;
}

NFA* NFA::join_NFAs(vector<NFA*>* nfas) {
    State * start = new State(TokenClass::epsilon, TokenClass::epsilon_char);
    State * accept = new State(TokenClass::epsilon, TokenClass::epsilon_char);

    this->states->push_back(start);
    this->states->push_back(accept);

    this->start_state = start;
    this->accepting_state = accept;
    for(int i = 0 ;i < nfas->size(); i++) {

        NFA* nfa = nfas->at(i);
        start->add_edge(nfa->start_state, TokenClass::epsilon_char);
        nfa->accepting_state->set_accepting(false);
        nfa->accepting_state->add_edge(accept, TokenClass::epsilon_char);
        for(int j = 0 ;j < nfa->states->size(); i++) {
            this->states->push_back(nfa->states->at(j));
        }
    }


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


State* NFA::get_start_state() {
    return start_state;
}
NFA::~NFA() {

}












