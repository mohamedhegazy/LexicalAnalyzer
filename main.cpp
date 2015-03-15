#include <iostream>
#include <map>
#include "src/NFA.h"
#include "src/DFA.h"
#include "src/RegExParser.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Hello world!" << endl;


    //hegazy test
    RegExParser *parser=new RegExParser("regex.txt");
    NFA *a=parser->constructNFA();
    string t="a";
    char s=41;
    cout<<string(1,(char)s);
    cout<< a->acceptes("a") <<endl;
    string lol;
    //a->NFA_print();
    NFA * small=NFA::get_range('a','z');
    NFA * capital=NFA::get_range('A','Z');
    NFA * digits=NFA::get_range('0','9');
    NFA * letter=small->oring(capital);
    NFA * letterORDigit=letter->oring(digits);
    NFA * closure=letterORDigit->kleene_closure();
    NFA *id =letter->concatenation(closure);
    //cout<<a->get_accepting_state()->get_token_class()->name;
    while(true)
    {
        cin>>lol;
        //cout<<id->acceptes(lol)<<endl;
        cout<<a->acceptes(lol)<<endl;
    }
    //end hegazy test


    DFA * dfa = new DFA();

    cout<<dfa->move(0,0)<<endl;
    cout << "done!" << endl;
    return 0;
}





