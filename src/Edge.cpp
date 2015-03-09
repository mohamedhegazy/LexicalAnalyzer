#include "Edge.h"

Edge:: Edge(State *from, State * to, char trans_char)
{
    this->from = from;
    this->to = to;
    this->trans_char = trans_char;
}



State*Edge:: get_from_State() {
    return from;
}
State*Edge::get_to_State(){
    return to;
}

char Edge::get_trans_char() {
    return trans_char;
}

Edge::~Edge()
{
    //dtor
}









