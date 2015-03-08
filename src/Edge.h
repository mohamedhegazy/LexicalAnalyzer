#ifndef EDGE_H
#define EDGE_H
#include "State.h"
#include "TokenClass.h"
class State;
class Edge
{
    public:
        char transition_character;
        State *from;
        State *to;
        Edge();
        virtual ~Edge();
    protected:
    private:
};

#endif // EDGE_H
