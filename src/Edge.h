#ifndef EDGE_H
#define EDGE_H
#include "State.h"
#include "TokenClass.h"
class State;
class Edge
{
    public:
        Edge(State *from, State * to, char trans_char);
        State* get_from_State();
        State* get_to_State();
        char get_trans_char();
        virtual ~Edge();
    protected:
    private:
        char trans_char;
        State *from;
        State *to;
};

#endif // EDGE_H
