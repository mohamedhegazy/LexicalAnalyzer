#ifndef REGEXPARSER_H
#define REGEXPARSER_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "RegDef.h"
#include "RegEx.h"
#include <string>
#include "Expression.h"

class RegExParser
{

    public:
        ifstream *inputFile;
        vector<RegDef *> *regular_defintions;
        vector<RegEx *> *regular_expressions;
        vector<TokenClass> tokenClasses;
        RegExParser(string name);
        NFA* constructNFA();
        string* prepareIfConcatenation(string line,bool exp_def);
         string addSpaces(string line);
         void sortRegExp();
         void sortRegDef();

        RegExParser();
        virtual ~RegExParser();
    protected:
    private:
    bool openInputFile(string filePath);//filePath: the absolute file path
	bool getNextLine(string *line);//return false if end of file is reached
    bool endOfFile;
    int getCharType(char in);
    int getOperatorPrecedence(char operator_);
    void parse();
    void evaluateExpression(string temp_lhs_name,vector<Expression *> *output,bool exp_def);
    NFA* getNFA(string name);
    NFA* evaluate(NFA *a,NFA *b,char operator_);
};

#endif // REGEXPARSER_H
