#ifndef SUBGROUP_H
#define SUBGROUP_H
#include <vector>
#include "DFAState.h"

class SubGroup
{
    public:
        SubGroup();
        vector <DFAState*>*group;
        virtual ~SubGroup();
        void put(DFAState * st);
    protected:
    private:
};

#endif // SUBGROUP_H
