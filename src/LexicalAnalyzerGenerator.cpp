#include "LexicalAnalyzerGenerator.h"

LexicalAnalyzerGenerator::LexicalAnalyzerGenerator()
{
    //ctor
}

LexicalAnalyzerGenerator::~LexicalAnalyzerGenerator()
{
    //dtor
}
LexicalAnalyzer* LexicalAnalyzerGenerator::createLexicalAnalyzer(string regex)
{


    cout<<"parse regular expressions, ";
    RegExParser *parser=new RegExParser(regex);
    cout<<"done !"<<endl;

    cout<<"construct NFA, ";
    NFA* nfa = parser->constructNFA();
   // NFA * nfa = NFA::get_letters()->oring(NFA::get_digits());
    cout<<"done !"<<endl;

    cout<<"convert NFA to DFA and minimize it, ";
    DFA* dfa = new DFA(nfa);
    cout<<"done !"<<endl;

    cout<<"create lexical analyzer, ";
    LexicalAnalyzer * result = new LexicalAnalyzer(dfa);
    cout<<"done !"<<endl;

    return result;
}





