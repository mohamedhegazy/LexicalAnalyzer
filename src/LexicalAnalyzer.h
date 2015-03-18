#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H
#include "Token.h"
#include "DFA.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";



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
            //get the tokens of the source file in sequence
            Token* getTokenNextToken();

            //constructor that sets the DFA which will be used by the
            //lexical analyzer
            LexicalAnalyzer(DFA* minimizedDFA);

            //set the source code file which will be parsed
            //for example test.java
            void setSourceCodeFile(string file_name);


        virtual ~LexicalAnalyzer();
    protected:
    private:
        int currentIndex;
        vector<DFAState*>* DFAVector;
        string currentString;
        std::vector<string> tokens;
        LexicalAnalyzer();
        string file_name;
        DFA* dfa;
        std::ifstream source_file;

};

#endif // LEXICALANALYZER_H
