#include <iostream>
#include "src/NFA.h"


using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    TokenClass* c = new TokenClass("state 1", 1);
    NFA* nfa = new NFA(c);
    nfa->NFA_print();


    TokenClass* c2 = new TokenClass("state 2", 1);
    NFA* nfa2 = new NFA(c2);
    nfa2->NFA_print();


    NFA * r = nfa->oring(nfa2);
    r->NFA_print();

    cout << "done!" << endl;
    return 0;
}
