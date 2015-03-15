#include "State.h"

State::State(TokenClass *tokenClass, bool accepting_state) {
    this->token_class = tokenClass;
    this->accepting = accepting_state;
    this->dead_state = false;
    this->adjList = new vector<Edge*>();
    this->in_degree = 0;
}

State::State() {

}

void State:: set_dead_state(bool dead_state) {
    this->dead_state = dead_state;
}
void State::add_edge(Edge* edge) {
    adjList->push_back(edge);
    edge->get_from_State()->in_degree++;
}
void State:: add_edge(State* to, char trans_char) {
    adjList->push_back(new Edge(this, to, trans_char));
    to->in_degree++;
}


vector<Edge*>* State:: get_adjList() {
    return adjList;
}


void State::set_accepting(bool accepting) {

    this->accepting = accepting;
}

State* State::clone() {
   State * result = new State();
   result->accepting = this->accepting;
   result->dead_state = this->dead_state;
   result->state_priority = this->state_priority;
   result->token_class = this->token_class->clone();
   result->adjList = new vector<Edge*>;

   return result;
}

bool State::get_accepting() {
    return accepting;
}


 TokenClass* State::get_token_class() {
    return token_class;

 }

 void State:: state_print() {
    cout<<"("<<token_class->name<<", "<<token_class->priority<<", "<<accepting<<" ) ... ";
    for(int i = 0; i < (int)adjList->size(); i++) {
        Edge*e = adjList->at(i);
        cout<<"("<<e->get_to_State()->get_token_class()->name<<", "<<e->get_trans_char()<<") ";
    }
    cout<<endl;
 }

void State::set_token_class(TokenClass *cl){
this->token_class=cl;
}


vector <State*>* State::closure() {


        set<State*> *visited = new set<State*>();
        visited->insert(this);
        queue<State*>* q = new queue<State*>();
        q->push(this);

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


void State::compress() {

    vector<Edge*> *adj = new vector<Edge*>;
    vector<State*>* c = this->closure();

    for(int i = 0; i < (int)adjList->size(); i++) {
        Edge* e = adjList->at(i);
        if(e->get_trans_char() != TokenClass::epsilon_char) {
            adj->push_back(e);
        }
    }

    for(int i = 0; i < (int)c->size(); i++) {

        State * s = c->at(i);

        if(s == this)
          continue;

        vector<Edge*>* e = s->adjList;

        for(int j = 0; j < (int)e->size(); j++) {
            Edge* ed = e->at(j);
            if(ed->get_trans_char() != TokenClass::epsilon_char) {
                adj->push_back(new Edge(this, ed->get_to_State(), ed->get_trans_char()));

            }
        }

        s->in_degree--;
        if(s->accepting) {
            this->accepting = true;
            if(s->token_class->priority < this->token_class->priority) {
                 this->token_class = s->token_class;
            }

        }

    }

    //remember to remove duplicates please
    this->adjList = adj;

}


int State::get_in_degree() {
    return in_degree;
 }


State::~State()
{
    //dtor
}





