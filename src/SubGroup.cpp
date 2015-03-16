#include "SubGroup.h"

SubGroup::SubGroup()
{
    //ctor
    group=new vector<DFAState *>();
}

SubGroup::~SubGroup()
{
    //dtor
}
void SubGroup::put(DFAState * st){
group->push_back(st);
}
