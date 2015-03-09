#include <iostream>
#include "src/NFA.h"


using namespace std;

int main()
{
    cout << "Hello world!" << endl;


    NFA * nfa1 = new NFA(new TokenClass("a", 1),'a');
    NFA * nfa2 = new NFA(new TokenClass("b", 1),'b');
    NFA * nfa3 = new NFA(new TokenClass("c", 1),'c');
    NFA * nfa4 = new NFA(new TokenClass("e", 1),'e');
    NFA * nfa5 = new NFA(new TokenClass("f", 1),'f');
    NFA * nfa6 = new NFA(new TokenClass("i", 1),'i');
    NFA * nfa7 = new NFA(new TokenClass("m", 1),'m');
    NFA * nfa8 = new NFA(new TokenClass("o", 1),'o');
    NFA * nfa9 = new NFA(new TokenClass("u", 1),'u');
    NFA * nfa10 = new NFA(new TokenClass("w", 1),'w');
    NFA * nfa11 = new NFA(new TokenClass("y", 1),'y');
    NFA * nfa12 = new NFA(new TokenClass("y", 1),'y');

    NFA* nfa13 = nfa12->oring(nfa7);
    vector<State*>* t = nfa13->closure(nfa13->get_start_state());
    vector<State*>* v = nfa13->move(t,'m');

    cout<<v->size()<<endl;
    for(int i = 0; i < v->size(); i++) {
        v->at(i)->state_print();
    }


    cout << "done!" << endl;
    return 0;
}





