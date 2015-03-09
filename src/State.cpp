#include "State.h"

State::State(TokenClass *tokenClass, bool accepting_state) {
    this->token_class = tokenClass;
    this->accepting = accepting_state;
    this->dead_state = false;
    this->adjList = new vector<Edge*>();
}
void State:: set_dead_state(bool dead_state) {
    this->dead_state = dead_state;
}
void State::add_edge(Edge* edge) {
    adjList->push_back(edge);

}
void State:: add_edge(State* to, char trans_char) {
    adjList->push_back(new Edge(this, to, trans_char));
}


vector<Edge*>* State:: get_adjList() {
    return adjList;
}


void State::set_accepting(bool accepting) {
    this->accepting = accepting;
}


 TokenClass* State::get_token_class() {
    return token_class;

 }

 void State:: state_print() {
    cout<<token_class->name<<", "<<token_class->priority<<" ... ";
    for(int i = 0; i < adjList->size(); i++) {
        Edge*e = adjList->at(i);
        cout<<"("<<e->get_to_State()->get_token_class()->name<<", "<<e->get_trans_char()<<") ";
    }
    cout<<endl;
 }

State::~State()
{
    //dtor
}





