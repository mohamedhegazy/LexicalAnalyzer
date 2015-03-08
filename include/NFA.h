#ifndef NFA_H
#define NFA_H


class NFA
{
    public:
        State start;
        vector <State> closure(State current);
        State move(Vector<State> current,char input);
        NFA();
        virtual ~NFA();
    protected:
    private:
};

#endif // NFA_H
