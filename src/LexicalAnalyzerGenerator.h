#ifndef LEXICALANALYZERGENERATOR_H
#define LEXICALANALYZERGENERATOR_H
#include "LexicalAnalyzer.h"
#include "RegExParser.h"
#include <string>
using namespace std;
        // take regExp txt file and creat lexal analyizer
        // get nfa form RegExParser , create dfa , minimize dfa
        // create LexicalAnalyzer by giving it the mimimized dfa

class LexicalAnalyzerGenerator
{
    public:

        //leave the constructer empty
        LexicalAnalyzerGenerator();

        //create lexical analyzer
        LexicalAnalyzer* createLexicalAnalyzer(string regxFile);

        virtual ~LexicalAnalyzerGenerator();
    protected:
    private:
};

#endif // LEXICALANALYZERGENERATOR_H
