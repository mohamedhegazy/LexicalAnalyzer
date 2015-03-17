#include "NFA.h"


NFA::NFA() {
    states = new vector<State*>();
    this->start_state = new State(TokenClass::epsilon, false);
    this->accepting_state = new State(TokenClass::epsilon, true);
    this->start_state->add_edge(this->accepting_state, TokenClass::epsilon_char);
    states->push_back(start_state);
    states->push_back(accepting_state);
}


 NFA::NFA(char c) {

    states = new vector<State*>();
    accepting_state = new State(new TokenClass(string(1, c), 0), true);
    start_state = new State(TokenClass::epsilon, false);
    states->push_back(start_state);
    states->push_back(accepting_state);

    start_state->add_edge(accepting_state, c);
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

            for(int i = 0 ; i <(int)e->size(); i++) {
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

    for(int i = 0; i < (int)current->size(); i++) {

        vector<Edge*>* e = current->at(i)->get_adjList();

        for(int j = 0; j < (int)e->size(); j++) {
            if(e->at(j)->get_trans_char() == trans_char &&
                tmp->find(e->at(j)->get_to_State()) == tmp->end()) {
                tmp->insert(e->at(j)->get_to_State());
            }
        }

    }


    set<State*> *result = new set<State*>();

   for(set<State*>::iterator it = tmp->begin(); it != tmp->end(); it++) {
        vector<State*> *t = this->closure(*it);
        for(int i = 0; i < (int)t->size(); i++) {
            result->insert(t->at(i));
        }
   }

    return new vector<State*>(result->begin(), result->end());
}


vector<State*>* NFA::move(string str) {

    vector<State*>* result = this->closure(this->start_state);
    for(int i = 0; i < (int)strlen(&str[0]) && result->size() != 0; i++) {
        result = this->move(result, str[i]);
    }

    return result;
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

    for(int i = 0; i < (int)this->states->size(); i++) {
        result->states->push_back(this->states->at(i));
    }

    for(int i = 0; i < (int)nfa->states->size(); i++) {
        result->states->push_back(nfa->states->at(i));
    }

    result->states->push_back(result->accepting_state);
    return result;

}
NFA* NFA::concatenation(NFA* nfa) {

    NFA* result = new NFA();

    result->states = new vector<State*>();
    result->start_state = this->start_state;
    result->accepting_state = nfa->accepting_state;

    this->accepting_state->set_accepting(false);
    this->accepting_state->add_edge(nfa->start_state, TokenClass::epsilon_char);


    for(int i = 0; i < (int)this->states->size(); i++) {
        result->states->push_back(this->states->at(i));
    }

    for(int i = 0; i < (int)nfa->states->size(); i++) {
       result->states->push_back(nfa->states->at(i));
    }


    return result;

}


NFA* NFA::kleene_closure() {

    State* new_start_state = new State(TokenClass::epsilon, false);
    State* new_acceping_state = new State(TokenClass::epsilon, true);


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
    State* new_acceping_state = new State(TokenClass::epsilon, true);

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



void NFA::compress() {

    for(int i = 0 ;i < (int)states->size(); i++) {
        states->at(i)->compress();
    }

    vector<State*>* s = new vector<State*>();


    for(int i = 0 ;i < (int)states->size(); i++) {
        if(states->at(i)->get_in_degree() != 0) {
            s->push_back(states->at(i));
        }
    }

    this->states = s;

}



NFA* NFA::join_NFAs(vector<NFA*>* nfas) {

    NFA * result = new NFA();
    result->states = new vector<State*>();
    result->start_state = new State(TokenClass::epsilon, false);
    result->accepting_state = NULL;
    result->states->push_back(result->start_state);

    for(int i = 0; i < (int)nfas->size(); i++) {
        NFA* nfa = nfas->at(i);
        result->start_state->add_edge(nfa->start_state, TokenClass::epsilon_char);

        for(int j = 0; j < (int)nfa->states->size(); j++) {
            result->states->push_back(nfa->states->at(j));
        }

    }

    //result->compress();
    return result;

}

void NFA::set_accepting_state(State* accepting_state) {
    this->accepting_state = accepting_state;
}

NFA* NFA::clone() {

    NFA* result = new NFA();
    map<State*, State*> table;

    queue<State*>q;
    q.push(this->start_state);

    while(!q.empty()) {
        State* s = q.front();
        q.pop();
        State* s2 =  s->clone();
        table[s] = s2;

        vector<Edge*> *v = s->get_adjList();
        for(int i = 0; i < (int)v->size(); i++) {
            if(table.find(v->at(i)->get_to_State()) == table.end()) {
                q.push(v->at(i)->get_to_State());
            }
        }

    }

    result->accepting_state = table[this->accepting_state];
    result->start_state = table[this->start_state];

    for(map<State*, State*>::iterator it = table.begin(); it != table.end(); it++) {
        State* s1 = it->first;
        State* s2 = it->second;
        result->states->push_back(s2);
        for(int i = 0; i < (int)s1->get_adjList()->size(); i++) {
            Edge * e1 = s1->get_adjList()->at(i);
            Edge * e2 = new Edge(s2, table[e1->get_to_State()], e1->get_trans_char());
            s2->add_edge(e2);
        }


    }

    return result;
}
 vector<State*>* NFA::get_states(){
    return states;
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
        for(int i = 0; i < (int)states->size(); i++) {
            states->at(i)->state_print();
        }
    }
    else {
        cout<<"states vector is NULL !"<<endl;
    }

    cout<<"dont printing NFA"<<endl;
    cout<<"----------------------------------------"<<endl;
}

State * NFA::get_accepting_state() {
    return accepting_state;
}

 bool NFA::acceptes(string str) {
    vector<State*>*v = move(str);

    for(int i = 0; i < (int)v->size(); i++) {
        if(v->at(i)->get_accepting()) {
            return true;
        }
    }

    return false;
 }


NFA* NFA::get_letter() {

    return get_range('a','z')->oring(get_range('A','Z'));
}

NFA* NFA::get_letters() {
    return get_letter()->positive_closure();
}

NFA* NFA::get_digit() {
    return get_range('0','9');
}

NFA* NFA::get_digits() {
    return get_digit()->positive_closure();
}

NFA* NFA::get_string(string str) {

    NFA* result = new NFA();

    result->states = new vector<State*>();
    result->start_state = new State(TokenClass::epsilon, false);

    result->states->push_back(result->start_state);


    State* current = result->start_state;

    for(int i = 0; i < (int)strlen(&str[0]); i++) {
        State * s = new State(TokenClass::epsilon, false);
        current->add_edge(s, str[i]);
        current = s;
        result->states->push_back(current);
    }

    current->set_accepting(true);
    result->accepting_state = current;



    return result;
}


NFA* NFA::get_range(char a, char b) {
   if(a > b) {
        return NULL;
    }

    NFA* nfa = new NFA();
    nfa->states = new vector<State*>();
    nfa->start_state = new State(TokenClass::epsilon, false);
    nfa->accepting_state = new State(TokenClass::epsilon, true);

    nfa->states->push_back(nfa->start_state);
    nfa->states->push_back(nfa->accepting_state);


    for(char c = a; c <= b; c++) {
        nfa->start_state->add_edge(nfa->accepting_state, c);
    }


    return nfa;
}

NFA* NFA::get_char(char c) {
    return new NFA(c);
}



State* NFA::get_start_state() {
    return start_state;
}
NFA::~NFA() {

}











