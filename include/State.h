#ifndef STATE_H
#define STATE_H


class State
{
    public:
        bool accepting;
        vector<Edge> out;
        int state_number;
        TokenClass accepted;

        State();
        virtual ~State();
    protected:
    private:
};

#endif // STATE_H
