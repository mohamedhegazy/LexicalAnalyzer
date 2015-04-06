#ifndef SYNTAXANALYZERGENERATOR_H
#define SYNTAXANALYZERGENERATOR_H
#include <string>
#include "SyntaxAnalyzer.h"
#include "LexicalAnalyzer.h"
#include <vector>
#include <string>
#include "LL1.h"
#include "ParsingTable.h"

using namespace std;
class SyntaxAnalyzerGenerator
{
    public:
        SyntaxAnalyzerGenerator();
        void print_file(string file_name, vector<string> * lines);
        SyntaxAnalyzer * createSyntaxAnalyzer(LexicalAnalyzer *lex,string rules);
        virtual ~SyntaxAnalyzerGenerator();
    protected:
    private:
};

#endif // SYNTAXANALYZERGENERATOR_H
