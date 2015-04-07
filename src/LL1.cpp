#include "LL1.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

LL1::LL1()
{
    //ctor
}
LL1::LL1(string input)
{
    //ctor
    endOfFile=false;
    openInputFile(input);
    symbols=new vector<Symbol *>;
    vector<string >* productions=getProductions(readFile(input));
    for(int i=0; i<productions->size(); i++)
    {
        Symbol * non_terminal;
        string prod=productions->at(i);
        int index=prod.find("=");
        string LHS=trim(prod.substr(1,index-1));

        if(!contains(LHS)){
        non_terminal=new Symbol(false,LHS);
        symbols->push_back(non_terminal);
        }
        else
        non_terminal=getSymbol(LHS);
        string RHS=trim(prod.substr(index+1));
        vector<string >* prods=split(RHS,'|');
        for(int j=0; j<prods->size(); j++)
        {
            Production * pr=new Production();
            pr->LHS=non_terminal;
            vector<string> * components=split(prods->at(j),' ');
            for(int k=0; k<components->size(); k++)
            {
                if(contains(components->at(i)))
                {
                    Symbol * sym=getSymbol(components->at(i));
                    pr->RHS->push_back(sym);
                }
                else
                {
                    string s=getTerminal(components->at(i));
                    if(s.size()==0){
                    Symbol *non=new Symbol(false,components->at(i));
                    symbols->push_back(non);
                    pr->RHS->push_back(non);
                    }
                    else{
                    Symbol *term=new Symbol(true,s);
                    symbols->push_back(term);
                    pr->RHS->push_back(term);
                    }
                }
            }
            non_terminal->productions->push_back(pr);
        }
    }
    if(symbols->size()>0)
        start_symbol=symbols->at(0);
    performLeftRecursionElimination();
    performLeftFactoring();
}

LL1::~LL1()
{
    //dtor
}

vector<string>* LL1::getProductions(vector<string> * lines)
{
    for(int i=0; i<lines->size(); i++)
    {
        string temp=lines->at(i);
        if(temp.size()>0 && temp.at(0)!='#')
        {
            lines->erase(lines->begin()+i);
            if(i>0)
                lines->at(i-1)=lines->at(i-1)+temp;
            i--;
        }
    }
    return lines;
}
vector<string>* LL1::readFile(string lines)
{
    vector<string>* file=new vector<string>;
    string *line  = new string();
    while(getNextLine(line))
    {
        file->push_back((*line));
    }
    return file;
}
bool LL1::openInputFile(string filePath)
{
    inputFile = new ifstream(&filePath[0], ios::in);
    return inputFile->is_open();
}
bool LL1::getNextLine(string *line)
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

string LL1::trim_right_inplace(
    string      s
)
{
        const string delimiters = " \f\n\r\t\v";
    return s.erase( s.find_last_not_of( delimiters ) + 1 );
}

string LL1::trim_left_inplace(
    string       s    )
{
    const string delimiters = " \f\n\r\t\v" ;
    return s.erase( 0, s.find_first_not_of( delimiters ) );
}

string LL1::trim(
    string       s
    )
{
    const string delimiters = " \f\n\r\t\v" ;
    return trim_left_inplace( trim_right_inplace( s ) );
}
vector<string> * LL1::split(string str,char delim)
{
    vector<string >*res=new vector<string>;
    string temp="";
    for(int i=0; i<str.size() ; i++)
    {
        if(str.at(i)==delim)
        {
            temp=trim(temp);
            res->push_back(temp);
            temp="";
        }
        else
        {
            temp=temp+str.at(i);
        }
    }
    return res;
}
bool LL1::contains(string symbol)
{
    for(int i=0; i<symbols->size(); i++)
    {
        Symbol * s=symbols->at(i);
        if(strcmp(s->name.c_str(),symbol.c_str())==0)
            return true;
    }
    return false;
}
Symbol * LL1::getSymbol(string name)
{
    for(int i=0; i<symbols->size(); i++)
    {
        Symbol * s=symbols->at(i);
        if(strcmp(s->name.c_str(),name.c_str())==0)
            return s;
    }
    return NULL;


}
string LL1::getTerminal(string str)
{
    if(str.size()>2 && str.at(0)=='‘' && str.at(str.size()-1)=='’')
        return str.substr(1,str.size()-2);
    else
    return "";
}
void LL1::performLeftFactoring(){

}
void LL1::performLeftRecursionElimination(){


}
