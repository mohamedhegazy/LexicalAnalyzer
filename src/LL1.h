#ifndef LL1_H
#define LL1_H
#include <fstream>

#include <string>
#include "Symbol.h"
#include <vector>
using namespace std;
//reads CFG and eliminates left-recusrion and performs left-factoring
class LL1
{
    public:
        LL1();
        LL1(string input_rules);//reads CFG and eliminates left-recusrion and performs left-factoring
        vector<Symbol*> *symbols;

        ifstream *inputFile;
        bool openInputFile(string filePath);//filePath: the absolute file path
        bool getNextLine(string *line);//return false if end of file is reached
        bool endOfFile;
        vector<string > *getProductions(vector<string> * lines);
        vector<string>* readFile(string lines);
        string trim_right_inplace(string s);
        string trim_left_inplace(string s);
        string trim(string s);
        vector<string> * trim(string str,char delim);
        Symbol * getSymbol(string name);
        bool contains(string symbol);
        string getTerminal(string str);
        vector<string> * split(string str,char delim);
        Symbol* start_symbol;
        void performLeftFactoring();
        void performLeftRecursionElimination();
        virtual ~LL1();
    protected:
    private:
};

#endif // LL1_H
