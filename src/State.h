#ifndef STATE_H
#define STATE_H
#include <vector>
#include "Edge.h"
#include "TokenClass.h"
#include <set>
#include <queue>
#include <iostream>
class Edge;
class State
{
    public:

        State(TokenClass *tokenClass, bool accepting_state);
        void set_dead_state(bool dead_state);
        void add_edge(Edge* edge);
        void add_edge(State* to, char trans_char);
        vector <Edge*>* get_adjList();
        vector <State*>* closure();
        void set_accepting(bool accepting);
        TokenClass* get_token_class();
        void set_token_class(TokenClass *cl);
        bool get_accepting();
        void compress();
        State* clone();
        void state_print();
        int get_in_degree();
        virtual ~State();
    protected:
    private:
        State();
        bool accepting;
        bool dead_state;
        int state_priority;
        TokenClass *token_class;
        std::vector<Edge*> *adjList;
        int in_degree;
};

#endif // STATE_H





