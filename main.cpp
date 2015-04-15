#include <iostream>
#include <map>
#include "src/NFA.h"
#include "src/DFA.h"
#include "src/LL1.h"
#include "src/ParsingTable.h"

#include "src/RegExParser.h"
#include "src/Phase1.h"
#include "src/Phase2.h"
#include "src/SyntaxAnalyzer.h"


using namespace std;

void DFA_test();
void RegExParser_test();
void phase1_test();
void phase2_test();
void     LL1_test();

void parsing_table_test();
ParsingTable* parsing_table_test1();
ParsingTable* parsing_table_test2();
ParsingTable* parsing_table_test3();

void SyntaxAnalyzer_test();


int main(int argc, char* argv[])
{
    cout << "Hello Parser!" << endl;


    //RegExParser_test();
    //DFA_test();
    //phase1_test();
    //phase2_test();
    //LL1_test();
    //parsing_table_test();
    SyntaxAnalyzer_test();



    cout<<"done !"<<endl;

    return 0;
}

void LL1_test(){
LL1* ll1=new LL1("GRAMMAR_RULES.txt");

}


void SyntaxAnalyzer_test() {


    ParsingTable * table = parsing_table_test1();
    LexicalAnalyzer* lexcal = NULL;
    SyntaxAnalyzer* analyze = new SyntaxAnalyzer(table, lexcal);

    analyze->testing_index = 0;
    analyze->testing_tokens = new vector<Token*>();

    TokenClass* a = new TokenClass("a",0);
    TokenClass* b = new TokenClass("b",0);
    TokenClass* c = new TokenClass("c",0);
    TokenClass* d = new TokenClass("d",0);
    TokenClass* e = new TokenClass("e",0);
    TokenClass* $ = new TokenClass("$",0);

    /*
    Token* t1 = new Token();
    t1->tokenClass = a;
    t1->attribute_value = "a";

    Token* t2 = new Token();
    t2->tokenClass = a;
    t2->attribute_value = "a";


    Token* t3 = new Token();
    t3->tokenClass = b;
    t3->attribute_value = "b";

    Token* t4 = new Token();
    t4->tokenClass = $;
    t4->attribute_value = "$";


    analyze->testing_tokens->push_back(t1);
    analyze->testing_tokens->push_back(t2);
    analyze->testing_tokens->push_back(t3);
    analyze->testing_tokens->push_back(t4);
    */

    Token* t1 = new Token();
    t1->tokenClass = c;
    t1->attribute_value = "c";

    Token* t2 = new Token();
    t2->tokenClass = e;
    t2->attribute_value = "e";


    Token* t3 = new Token();
    t3->tokenClass = a;
    t3->attribute_value = "a";

    Token* t4 = new Token();
    t4->tokenClass = d;
    t4->attribute_value = "d";

    Token* t5 = new Token();
    t5->tokenClass = b;
    t5->attribute_value = "b";

    Token* t6 = new Token();
    t6->tokenClass = $;
    t6->attribute_value = "$";


    analyze->testing_tokens->push_back(t1);
    analyze->testing_tokens->push_back(t2);
    analyze->testing_tokens->push_back(t3);
    analyze->testing_tokens->push_back(t4);
    analyze->testing_tokens->push_back(t5);
    analyze->testing_tokens->push_back(t6);

    cout<<table->toString()<<endl;



    analyze->start_parsing();


    vector<string> * ans = analyze->get_parsing_result_string();
    cout<<"parsing : "<<analyze->get_successful_parsing()<<endl;
    for(int i = 0; i < ans->size(); i++) {
        cout<<ans->at(i)<<endl;
    }
    /*
    for(int i = 0; i < p->size(); i++) {
        cout<<p->at(i)->toString()<<endl;
    }
    */


}




void parsing_table_test() {

    cout<<"hello tables\n";

   // cout<<"here"<<endl;
    //ParsingTable* table = parsing_table_test1();
    ParsingTable* table = parsing_table_test2();
    //ParsingTable* table = parsing_table_test3();


    /*
    vector<Symbol*> *ss = table->get_symbols();
    for(int i = 0; i < (int)ss->size(); i++) {
        Symbol*s = ss->at(i);

        cout<<s->toString()<<endl;
    }

    cout<<"successfull : "<<table->is_successful()<<endl;
    */
    cout<<table->toString(15);

}


ParsingTable* parsing_table_test1() {
    /*
        S -> AbS | e | epsilon
        A -> a | cAd
    */

    Symbol* S = new Symbol(false, "S");
    Symbol* A = new Symbol(false, "A");
    Symbol* a = new Symbol(true, "a");
    Symbol* b = new Symbol(true, "b");
    Symbol* c = new Symbol(true, "c");
    Symbol* d = new Symbol(true, "d");
    Symbol* e = new Symbol(true, "e");

    S->is_nullable = true;




    Production * s1 = new Production();
    s1->LHS = S;
    s1->RHS->push_back(A);
    s1->RHS->push_back(b);
    s1->RHS->push_back(S);

    Production * s2 = new Production();
    s2->LHS = S;
    s2->RHS->push_back(e);

    S->productions->push_back(s1);
    S->productions->push_back(s2);


    Production * a1 = new Production();
    a1->LHS = A;
    a1->RHS->push_back(a);



    Production * a2 = new Production();
    a2->LHS = A;
    a2->RHS->push_back(c);
    a2->RHS->push_back(A);
    a2->RHS->push_back(d);


    A->productions->push_back(a1);
    A->productions->push_back(a2);




    LL1 * ll1 = new LL1();

    ll1->start_symbol  = S;

    ll1->symbols->push_back(A);
    ll1->symbols->push_back(S);
    ll1->symbols->push_back(a);
    ll1->symbols->push_back(b);
    ll1->symbols->push_back(c);
    ll1->symbols->push_back(d);
    ll1->symbols->push_back(e);

    ParsingTable * table = new ParsingTable(ll1);

    TokenClass * aa = new TokenClass("a",0);
    TokenClass * bb = new TokenClass("b",0);
    TokenClass * cc = new TokenClass("c",0);
    TokenClass * dd = new TokenClass("d",0);
    TokenClass * ee = new TokenClass("e",0);

    Token * ta = new Token();
    ta->attribute_value = "a";
    ta->tokenClass = aa;

    Token * tb = new Token();
    tb->attribute_value = "b";
    tb->tokenClass = bb;

    Token * tc = new Token();
    tc->attribute_value = "c";
    tc->tokenClass = cc;

    Token * td = new Token();
    td->attribute_value = "d";
    td->tokenClass = dd;

    Token * te = new Token();
    te->attribute_value = "e";
    te->tokenClass = ee;

    vector<Token*>*tokens = new vector<Token*>();
    tokens->push_back(ta);
    tokens->push_back(tb);
    tokens->push_back(tc);
    tokens->push_back(td);
    tokens->push_back(te);


    return table;

}


ParsingTable* parsing_table_test2() {
    /*
        E  -> TE’
        E’ -> +TE’ | espsilon
        T  -> FT’
        T’ -> *FT’ | epsilon
        F  -> (E) | id
    */

    Symbol* E = new Symbol(false, "E");
    Symbol* E2 = new Symbol(false, "E`");
    Symbol* T = new Symbol(false, "T");
    Symbol* T2 = new Symbol(false, "T`");
    Symbol* F = new Symbol(false, "F");

    Symbol* addition = new Symbol(true, "+");
    Symbol* multiplication = new Symbol(true, "*");
    Symbol* open = new Symbol(true, "(");
    Symbol* close = new Symbol(true, ")");
    Symbol* id = new Symbol(true, "id");

    E2->is_nullable = true;
    T2->is_nullable = true;




    Production * e1 = new Production();
    e1->LHS = E;
    e1->RHS->push_back(T);
    e1->RHS->push_back(E2);
    E->productions->push_back(e1);

    Production * e21 = new Production();
    e21->LHS = E2;
    e21->RHS->push_back(addition);
    e21->RHS->push_back(T);
    e21->RHS->push_back(E2);
    E2->productions->push_back(e21);





    Production * t1 = new Production();
    t1->LHS = T;
    t1->RHS->push_back(F);
    t1->RHS->push_back(T2);
    T->productions->push_back(t1);



    Production * t21 = new Production();
    t21->LHS = T2;
    t21->RHS->push_back(multiplication);
    t21->RHS->push_back(F);
    t21->RHS->push_back(T2);
    T2->productions->push_back(t21);




    Production * f1 = new Production();
    f1->LHS = F;
    f1->RHS->push_back(open);
    f1->RHS->push_back(E);
    f1->RHS->push_back(close);
    F->productions->push_back(f1);


    Production * f2 = new Production();
    f2->LHS = F;
    f2->RHS->push_back(id);
    F->productions->push_back(f2);



    LL1 * ll1 = new LL1();

    ll1->start_symbol  = E;

    ll1->symbols->push_back(E);
    ll1->symbols->push_back(E2);
    ll1->symbols->push_back(T);
    ll1->symbols->push_back(T2);
    ll1->symbols->push_back(F);
    ll1->symbols->push_back(open);
    ll1->symbols->push_back(close);
    ll1->symbols->push_back(id);
    ll1->symbols->push_back(addition);
    ll1->symbols->push_back(multiplication);

    ParsingTable * table = new ParsingTable(ll1);
    return table;

}


ParsingTable* parsing_table_test3() {
    /*
        S -> i C t S E | a
        E -> e S | epsilon
        C -> b
    */

    Symbol* S = new Symbol(false, "S");
    Symbol* E = new Symbol(false, "E");
    Symbol* C = new Symbol(false, "C");

    Symbol* i = new Symbol(true, "i");
    Symbol* t = new Symbol(true, "t");
    Symbol* a = new Symbol(true, "a");
    Symbol* e = new Symbol(true, "e");
    Symbol* b = new Symbol(true, "b");

    E->is_nullable = true;




    Production * s1 = new Production();
    s1->LHS = S;
    s1->RHS->push_back(i);
    s1->RHS->push_back(C);
    s1->RHS->push_back(t);
    s1->RHS->push_back(S);
    s1->RHS->push_back(E);
    S->productions->push_back(s1);


    Production * s2 = new Production();
    s2->LHS = S;
    s2->RHS->push_back(a);
    S->productions->push_back(s2);

    Production * e1 = new Production();
    e1->LHS = E;
    e1->RHS->push_back(e);
    e1->RHS->push_back(S);
    E->productions->push_back(e1);





    Production * c1 = new Production();
    c1->LHS = C;
    c1->RHS->push_back(b);
    C->productions->push_back(c1);



    LL1 * ll1 = new LL1();

    ll1->start_symbol  = S;

    ll1->symbols->push_back(S);
    ll1->symbols->push_back(E);
    ll1->symbols->push_back(C);
    ll1->symbols->push_back(i);
    ll1->symbols->push_back(t);
    ll1->symbols->push_back(a);
    ll1->symbols->push_back(e);
    ll1->symbols->push_back(b);


    ParsingTable * table = new ParsingTable(ll1);
    return table;

}






void phase1_test() {
    cout<<"Phase1 test"<<endl;
    Phase1::start_phase1();
    cout<<"Phase1 test done !"<<endl;
}
void phase2_test(){
    cout<<"Phase2 test"<<endl;
    Phase2::start_phase2();
    cout<<"Phase2 test done !"<<endl;

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










