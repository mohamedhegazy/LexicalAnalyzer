#include "DFAEdge.h"

DFAEdge::DFAEdge(DFAState * form , DFAState * to , char trans_char)
{
    this->from=form;
    this->to=to;
    this->trans_char=trans_char;
}

DFAEdge::~DFAEdge()
{
    //dtor
}
