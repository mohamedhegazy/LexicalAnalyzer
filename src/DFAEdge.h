#ifndef DFAEDGE_H
#define DFAEDGE_H
#include "DFAState.h"

class DFAState;
class DFAEdge
{
    public:
        DFAEdge(DFAState * form , DFAState * to , char trans_char);
        virtual ~DFAEdge();
    protected:
    private:
        DFAState *from;
        DFAState *to;
        char trans_char;
};

#endif // DFAEDGE_H
