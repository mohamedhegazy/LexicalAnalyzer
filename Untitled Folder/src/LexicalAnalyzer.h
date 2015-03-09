#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include "Token.h"
#include "DFA.h"
// given the minimized dfa and the source code file
        // read the input file and provid tokens through
        // the next token method applying the max munch rule
        // the given dfa checks if there is more than one accepting state
        // and if so it will break the tie by applying the priority rule
        // be carful of end of file as it's not handled in the dfa, it's your jop
        // at EOF return a Token that represents end of file
class LexicalAnalyzer
{
    public:
            Token getTokenNextToken();
            LexicalAnalyzer(DFA minimizedDFA);
            void setSourceCodeFile(string file_name);

        LexicalAnalyzer();
        virtual ~LexicalAnalyzer();
    protected:
    private:
};

#endif // LEXICALANALYZER_H
