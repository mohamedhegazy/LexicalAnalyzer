#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H
#include "ParsingTable.h"
#include "LexicalAnalyzer.h"
#include <string>

class SyntaxAnalyzer
{
    public:
        SyntaxAnalyzer();
        //calls the function getnextToken() from lexicalAnalyzer and makes transitions inside the table based on //the token that returned
        SyntaxAnalyzer(ParsingTable* table, LexicalAnalyzer* lexicalAnalyzer);
        vector<string>* start_parsing(string source_code);
        virtual ~SyntaxAnalyzer();
    protected:
    private:
};

#endif // SYNTAXANALYZER_H
