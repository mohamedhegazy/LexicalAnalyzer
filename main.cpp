#include <iostream>
#include <map>
#include "src/NFA.h"


using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    NFA* what = NFA::get_string("what");
    NFA* where = NFA::get_string("where");
    NFA* how = NFA::get_string("how")->kleene_closure();

    NFA* nfa = new NFA();
    nfa = nfa->oring(what)->oring(where)->oring(how);
    cout<<nfa->acceptes("howu")<<endl;


    cout << "done!" << endl;
    return 0;
}





