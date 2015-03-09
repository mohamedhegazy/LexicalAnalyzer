#include "RegExParser.h"
const int ALPHA=1;
const int REG_DEF_SEPARATOR=2;
const int REG_EXP_SEPARATOR=3;//we know now the token class name
const int ESCAPE=4;//lookahead one step
const int LEFT_PARENTHESE=5;//concatenate operation
const int RIGHT_PARENTHESE=6;//empty operation stack untill left parenthese
const int LEFT_PARENTHESE_INDEX=7;//punctuation
const int RIGHT_PARENTHESE_INDEX=8;
const int LEFT_CURLY=9;//keyword class
const int RIGHT_CURLY=10;
const int OPERATOR=11;// +,|,(,),*,-

RegExParser::RegExParser()
{
    //ctor
}
RegExParser::RegExParser(string regex)
{
    //ctor
    endOfFile=false;
    openInputFile(regex);
    inputFile = new ifstream(&regex[0], ios::in);
    string *line  = new string();
    while(getNextLine(line))
    {
        string temp = "";
        int length = strlen(&line[0]);
        for(int i = 0; i < length; i++)
        {
            int type=getCharType(line[i]);
            switch(type){



            }

        }


    }

    RegExParser::~RegExParser()
    {
        //dtor
    }
    bool RegExParser::openInputFile(string filePath)
    {
        inputFile = new ifstream(&filePath[0], ios::in);
        return inputFile->is_open();
    }
    bool RegExParser::getNextLine(string *line)
    {

        if(endOfFile)
            return false;
        //read a line
        std::getline(*inputFile, *line);
        if(inputFile->eof())  //end of file is reached
        {
            endOfFile = true;
            return false;
        }
        return true;
    }
    int RegExParser::getCharType(char in){
        if(((int )in >=65 && (int )in <=90) || ((int )in >=97 && (int )in <=122))
        return ALPHA;
        else if(in==':')
        return REG_DEF_SEPARATOR;
        else if(in=='=')
        return REG_EXP_SEPARATOR;
        else if(in=='\\')
        return ESCAPE;
        else if(in=='(')
        return LEFT_PARENTHESE;
        else if(in==')')
        return RIGHT_PARENTHESE;
        else if(in=='[')
        return LEFT_PARENTHESE_INDEX;
        else if(in==']')
        return RIGHT_PARENTHESE_INDEX;
        else if(in=='{')
        return LEFT_CURLY;
        else if(in=='}')
        return RIGHT_CURLY;
        else if(in=='+' || in=='*' || in=='|' || in=='-')
        return OPERATOR;
    }
