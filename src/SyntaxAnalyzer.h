#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H
#include "ParsingTable.h"
#include "LexicalAnalyzer.h"
#include <string>
#include <stack>

class SyntaxAnalyzer
{
    public:

        //calls the function getnextToken() from lexicalAnalyzer and makes transitions inside the table based on //the token that returned
        SyntaxAnalyzer(ParsingTable* table, LexicalAnalyzer* lexicalAnalyzer);
        void start_parsing();
        virtual ~SyntaxAnalyzer();

        vector<Production*>* get_parsing_result_productions();
        vector<string>* get_parsing_result_string();
        bool get_successful_parsing();

        vector<Token*>* testing_tokens;
        int testing_index;

        ParsingTable* table;
    protected:
    private:
        SyntaxAnalyzer();

        LexicalAnalyzer * lexicalAnalyzer;
        Token* get_next_token();
        vector<Production*>* parsing_result_productions;
        vector<string>* parsing_result_string;
        bool successful_parsing;
};

#endif // SYNTAXANALYZER_H









