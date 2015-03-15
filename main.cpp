#include <iostream>
#include <map>
#include "src/NFA.h"
#include "src/DFA.h"
#include "src/RegExParser.h"

using namespace std;

void DFA_test();
void RegExParser_test();
int main(int argc, char* argv[])
{
    cout << "Hello Parser!" << endl;


    DFA_test();
    cout<<"done !"<<endl;
    return 0;
}


void DFA_test() {

   cout<<"DFA test"<<endl;


   TokenClass* t = new TokenClass("if",0);
   NFA * digits = NFA::get_string("if");
   digits->get_accepting_state()->set_token_class(t);

   TokenClass* t2 = new TokenClass("letters",10);
   NFA * letters = NFA::get_letters();
   letters->get_accepting_state()->set_token_class(t2);


   TokenClass* t3 = new TokenClass("while",5);
   NFA * whi = NFA::get_string("while");
   whi->get_accepting_state()->set_token_class(t3);


   TokenClass* t4 = new TokenClass("ident",8);
   NFA * ident = NFA::get_letters()->concatenation(
        (NFA::get_letter()->oring(NFA::get_digit()))->kleene_closure()
   );
   ident->get_accepting_state()->set_token_class(t4);


   vector<NFA*>*v = new vector<NFA*>();
   v->push_back(digits);
   v->push_back(letters);
   v->push_back(whi);
   v->push_back(ident);

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
//    string temp=*(RegExParser::prepareIfConcatenation("id: letter (letter|digit)*",1));
//    cout << temp<<endl;
    //end hegazy test


}










