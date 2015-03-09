#ifndef REGEXPARSER_H
#define REGEXPARSER_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "RegDef.h"
#include "RegEx.h"
#include <string>

class RegExParser
{

    public:
        ifstream *inputFile;
        vector<RegDef> regular_defintions;
        vector<RegEx> regular_expressions;
        vector<TokenClass> tokenClasses;
        RegExParser(string name);
        NFA constructNFA();

        RegExParser();
        virtual ~RegExParser();
    protected:
    private:
    bool openInputFile(string filePath);//filePath: the absolute file path
	bool getNextLine(string *line);//return false if end of file is reached
    bool endOfFile;
    int getCharType(char in);
};

#endif // REGEXPARSER_H
