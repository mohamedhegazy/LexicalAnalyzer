#include <iostream>
#include <map>
#include "src/NFA.h"
#include "src/DFA.h"


using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    DFA * dfa = new DFA();

    cout<<dfa->move(0,0)<<endl;
    cout << "done!" << endl;
    return 0;
}





