#ifndef LEXICALANALYZERGENERATOR_H
#define LEXICALANALYZERGENERATOR_H
#include "LexicalAnalyzer.h"
#include <string>
using namespace std;
        // take regExp txt file and creat lexal analyizer
        // get nfa form RegExParser , create dfa , minimize dfa
        // create LexicalAnalyzer by giving it the mimimized dfa

class LexicalAnalyzerGenerator
{
    public:
        LexicalAnalyzerGenerator();
        LexicalAnalyzer createLexicalAnalyzer(string regex);

        virtual ~LexicalAnalyzerGenerator();
    protected:
    private:
};

#endif // LEXICALANALYZERGENERATOR_H
