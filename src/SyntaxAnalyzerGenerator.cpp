#include "SyntaxAnalyzerGenerator.h"
SyntaxAnalyzerGenerator::SyntaxAnalyzerGenerator()
{

}
SyntaxAnalyzer * SyntaxAnalyzerGenerator:: createSyntaxAnalyzer(LexicalAnalyzer *lex ,string rules){
    cout<<"parse grammar rules and perform left factoring and left recursion elimination";

    LL1 * ll1 = new LL1(rules);

    cout<<"done !"<<endl;

    cout<<"construct Parsing Table! ";
    ParsingTable* table = new ParsingTable (ll1);
    cout<<"done !"<<endl;

    SyntaxAnalyzer * analyzer=new SyntaxAnalyzer(table,lex);
    return analyzer;

}

void SyntaxAnalyzerGenerator ::print_file(string file_name, vector<string>* lines)
{

}

SyntaxAnalyzerGenerator::~SyntaxAnalyzerGenerator()
{
    //dtor
}
