#include <iostream>
#include <map>
#include "src/NFA.h"
#include "src/DFA.h"
#include "src/RegExParser.h"
#include "src/Phase1.h"

using namespace std;

void DFA_test();
void RegExParser_test();
void phase1_test();

int main(int argc, char* argv[])
{
    cout << "Hello Parser!" << endl;



    //RegExParser_test();
    //DFA_test();
    phase1_test();





    cout<<"done !"<<endl;

    return 0;
}



void phase1_test() {
    cout<<"Phase1 test"<<endl;
    Phase1::start_phase1();
    cout<<"Phase1 test done !"<<endl;
}



void DFA_test() {

   cout<<"DFA test"<<endl;

    //letter = a-z | A-Z
    TokenClass * tLetters = new TokenClass("letters", 0);
    NFA*letter = NFA::get_letters();
    letter->get_accepting_state()->set_token_class(tLetters);

    //digit = 0-9
    TokenClass * tDigit = new TokenClass("digit", 1);
    NFA*digit = NFA::get_digit();
    digit->get_accepting_state()->set_token_class(tDigit);


    //digits = digit+
    TokenClass * tDigits = new TokenClass("digits", 3);
    NFA*digits = NFA::get_digits();
    digits->get_accepting_state()->set_token_class(tDigits);

    //{boolean int float}
    TokenClass * tBoolean = new TokenClass("boolean", 4);
    NFA*boolean = NFA::get_string("boolean");
    boolean->get_accepting_state()->set_token_class(tBoolean);

    //{boolean int float}
    TokenClass * tInt = new TokenClass("int", 5);
    NFA*integer = NFA::get_string("int");
    integer->get_accepting_state()->set_token_class(tInt);

    TokenClass * tFloat = new TokenClass("float", 6);
    NFA*floatt = NFA::get_string("float");
    floatt->get_accepting_state()->set_token_class(tFloat);


    //id: letter (letter|digit)*
    TokenClass * tId = new TokenClass("id", 1000);
    NFA*id = letter->clone()->concatenation(
        letter->clone()->oring(digit->clone())->kleene_closure()
    );
    id->get_accepting_state()->set_token_class(tId);


/**


    num: digit+ | digit+ . digits ( \L | E digits)
    relop: \=\= | !\= | > | >\= | < | <\=
    assign: =
    { if else while }
    [; , \( \) { }]
    addop: \+ | -
    mulop: \* | /
*/
   vector<NFA*>*v = new vector<NFA*>();
   v->push_back(id);
   v->push_back(digits);
   v->push_back(integer);
   v->push_back(floatt);
   v->push_back(boolean);

   NFA*nfa = NFA::join_NFAs(v);


   DFA* dfa = new DFA(nfa);
   cout<<"dfa states count : "<<dfa->get_states()->size()<<endl;
   cout<<"nfa states count : "<<nfa->get_states()->size()<<endl;


   while(true) {
        string str;
        cin>>str;
        DFAState * ss = dfa->get_start_state()->move(str);
        if(ss == NULL) {
             cout<<"anser is : NULL"<<endl;
        }
        else
            cout<<"anser is : "<<ss->get_accepting()<<" class : "<<ss->get_tokenClass()->name<<endl;
        //cout<<"the anser is : "<<nfa->acceptes(str)<<endl;
   }

   cout<<"DFA test done !"<<endl;
}




//hegazy test

void RegExParser_test() {

    cout<<"testing RegExParser"<<endl;

    //hegazy test

    RegExParser *parser=new RegExParser("regex.txt");
    NFA *a=parser->constructNFA();


    DFA *hussein=new DFA(a);
    cout<<"dfa states count : "<<hussein->get_states()->size()<<endl;
    cout<<"dfa states mini count : "<<hussein->get_mini_states()->size()<<endl;
    cout<<"nfa states count : "<<a->get_states()->size()<<endl;

    NFA * boolean=NFA::get_string("boolean");
    cout<<boolean->get_states()->size()<<"       lol";
       while(true) {
    cout<<"\n\n\n\n\n\n\nenter data\n";

    while(true) {
        string str;
        cin>>str;
        DFAState * ss = hussein->get_mini_start_state()->move_mini(str);
        if(ss == NULL) {
             cout<<"anser is : NULL"<<endl;
        }
        else
            cout<<"anser is : "<<ss->get_accepting()<<" class : "<<ss->get_tokenClass()->name<<endl;
        //cout<<"the anser is : "<<nfa->acceptes(str)<<endl;
    }

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

//    NFA *id =letter->concatenation(closure);
    //cout<<a->get_accepting_state()->get_token_class()->name;
    while(true)
    {
        cin>>lol;
        //cout<<id->acceptes(lol)<<endl;
        cout<<a->acceptes(lol)<<endl;
    }
//    string temp=*(RegExParser::prepareIfConcatenation("id: letter (letter|digit)*",1));
//    cout << temp<<endl;
    //end hegazy test
       }

}










