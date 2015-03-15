#ifndef DFASTATE_H
#define DFASTATE_H
#include <vector>
#include "TokenClass.h"
#include "State.h"
#include "DFAEdge.h"
#include <iostream>

class DFAEdge;
class DFAState
{
    public:
        DFAState(vector <State*>* NFAStates );
        void setStart();
        void addEdge(DFAEdge* DFAEdge);
        void addEdge(DFAState* to,char trans_char);
        virtual ~DFAState();
        void setMarked();
        bool isMarked();
        vector<State*>* getNFAStates();
    protected:
    private:
        std::vector <State*> * NFAStates;
        std::vector <DFAEdge*> * DFAEdges;
        bool isStart;
        bool isAccepting;
        bool Marked;

};

#endif // DFASTATE_H
