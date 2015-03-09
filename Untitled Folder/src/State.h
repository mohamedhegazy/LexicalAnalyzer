#ifndef STATE_H
#define STATE_H
#include <vector>
#include "Edge.h"
#include "TokenClass.h"
class Edge;
class State
{
    public:
        bool accepting;
        std::vector<Edge> out;
        int state_number;
        TokenClass accepted;
        State();
        virtual ~State();
    protected:
    private:
};

#endif // STATE_H
