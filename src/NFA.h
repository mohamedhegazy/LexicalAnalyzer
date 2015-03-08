#ifndef NFA_H
#define NFA_H
#include "State.h"
#include <vector>
class NFA
{
    public:
        State start;
        vector <State> closure(State current);
        State move(vector<State> current,char input);
        NFA();
        virtual ~NFA();
    protected:
    private:
};

#endif // NFA_H
