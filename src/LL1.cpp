#include "LL1.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

LL1::LL1()
{
   symbols=new vector<Symbol *>;
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

        if(!contains(LHS))
        {
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
                if(strcmp(components->at(k).c_str(),"NULL")==0)
                {
                    non_terminal->is_nullable=true;
                    continue;
                }
                if(contains(components->at(k)))
                {
                    Symbol * sym=getSymbol(components->at(k));
                    pr->RHS->push_back(sym);
                }
                else
                {
                    string s=getTerminal(components->at(k));
                    if(s.size()==0)
                    {
                        Symbol *non=new Symbol(false,components->at(k));
                        symbols->push_back(non);
                        pr->RHS->push_back(non);
                    }
                    else
                    {
                        Symbol *term;
                        if(contains(s))
                            term=getSymbol(s);
                        else
                        {
                            term=new Symbol(true,s);
                            symbols->push_back(term);
                        }
                        pr->RHS->push_back(term);
                    }
                }
            }
            if(pr->RHS->size()>0)
            non_terminal->productions->push_back(pr);
        }
    }
    if(symbols->size()>0)
        start_symbol=symbols->at(0);
    for(int i=0; i<productions->size(); i++)
    {
        string prod=productions->at(i);
        int index=prod.find("=");
        string LHS=trim(prod.substr(1,index-1));
        for(int j=0; j<symbols->size(); j++)
        {
            if(strcmp(symbols->at(j)->name.c_str(),LHS.c_str())==0)
            {
                Symbol * temp=symbols->at(j);
                symbols->erase(symbols->begin()+j);
                symbols->insert(symbols->begin()+i,temp);
            }
        }
    }
    performLeftRecursionElimination();
    performLeftFactoring();
    printSymbols();
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
        if((*line).size()>0)
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
    if(temp.size()>0)
        res->push_back(trim(temp));
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
    if(str.size()>2 && str.at(0)=='\'' && str.at(str.size()-1)=='\'')
        return str.substr(1,str.size()-2);
    else
        return "";
}
void LL1::performLeftFactoring()
{
    while(true)
    {
        bool change=false;
        for(int i=0; i<symbols->size(); i++)
        {
            if(symbols->at(i)->is_terminal)
                continue;
            int s=1;
            for(int j=0; j<symbols->at(i)->productions->size(); j++)
            {
                int min_cnt=100000;
                vector<Production* > *temp=new vector<Production*>;
                for(int k=0; k<symbols->at(i)->productions->size(); k++)
                {
                    if(j!=k)
                    {
                        int cnt=match(symbols->at(i)->productions->at(j),symbols->at(i)->productions->at(k));
                        if(cnt>0)
                        {
                            temp->push_back(symbols->at(i)->productions->at(k));
                            if(cnt<min_cnt)
                                min_cnt=cnt;
                        }
                    }
                }

                if(temp->size()>0)
                {
                    temp->push_back(symbols->at(i)->productions->at(j));
                    for(int h=0; h<temp->size(); h++)
                    {
                        for(int d=0; d<symbols->at(i)->productions->size(); d++)
                        {
                            if(symbols->at(i)->productions->at(d)==temp->at(h))
                            {
                                symbols->at(i)->productions->erase(symbols->at(i)->productions->begin()+d);
                                d--;
                            }
                        }
                    }
                    Production * common=getCommon(symbols->at(i),min_cnt,temp);
                    string dash="";
                    int c=s;
                    while(c-->0)
                        dash=dash+"'";

                    s++;
                    Symbol * s=new Symbol(false,symbols->at(i)->name+dash);
                    for(int m=0; m<temp->size(); m++)
                    {
                        Production * l=new Production();
                        l->LHS=s;
                        if(temp->at(m)->RHS->size()==0){
                            s->is_nullable=true;
                            temp->erase(temp->begin()+m);
                            m--;
                            continue;
                        }

                        for(int z=0; z<temp->at(m)->RHS->size(); z++)
                        {
                            l->RHS->push_back(temp->at(m)->RHS->at(z));
                        }
                        s->productions->push_back(l);
                    }
                    common->RHS->push_back(s);
                    symbols->at(i)->productions->push_back(common);
                    symbols->push_back(s);
                    change=true;
                }
            }
        }
        if(!change)
            break;
    }

}
void LL1::performLeftRecursionElimination()
{
    for(int i=0; i<symbols->size(); i++)
    {
        if(symbols->at(i)->is_terminal || symbols->at(i)->just_added)
            continue;
        Symbol * s=symbols->at(i);
        for(int j=0; j<i; j++)
        {
            if(symbols->at(j)->is_terminal)
                continue;
            for(int k=0; k<s->productions->size(); k++)
                //replace Ai->Aj Y with Ai->a1 Y|a2 Y|..
                //where Aj->a1|a2|...
            {
                Production* p=s->productions->at(k);
                if(p->RHS->size()>0 && p->RHS->at(0)==symbols->at(j))
                {
                    p->RHS->erase(p->RHS->begin());
                    s->productions->erase(s->productions->begin()+k);
                    concatenateProductions(s,symbols->at(j)->productions,p);
                    k--;
                }
            }
        }
        removeImmediateLeftRecursion(i);
    }
}
void LL1:: concatenateProductions(Symbol * s,vector<Production *>* productions,Production *p2)
{
    for(int i=0; i<productions->size(); i++)
    {
        Production * pr=new Production();
        pr->LHS=s;
        for(int k=0; k<productions->at(i)->RHS->size(); k++)
        {
            pr->RHS->push_back(productions->at(i)->RHS->at(k));
        }
        for(int j=0; j<p2->RHS->size(); j++)
        {
            pr->RHS->push_back(p2->RHS->at(j));
        }
        s->productions->push_back(pr);
    }
}
//remove immediate left recursion among Apos productions
void LL1:: removeImmediateLeftRecursion(int pos)
{
    for(int i=0; i<=pos; i++)
    {
        if(symbols->at(i)->is_terminal)
            continue;
        vector<Production *>*pro=new vector<Production *>;
        for(int j=0; j<symbols->at(i)->productions->size(); j++)
        {
            if(symbols->at(i)->productions->at(j)->LHS==
                    symbols->at(i)->productions->at(j)->RHS->at(0))
            {
                Production* p=symbols->at(i)->productions->at(j);
                p->RHS->erase(p->RHS->begin());
                pro->push_back(p);
                symbols->at(i)->productions->erase(symbols->at(i)->productions->begin()+j);
                j--;
            }
        }
        if(pro->size()>0)
        {
            Symbol *s=new Symbol(false,symbols->at(i)->name+"'");
            s->is_nullable=true;
            s->just_added=true;
            for(int k=0; k<pro->size(); k++)
            {
                pro->at(k)->LHS=s;
                pro->at(k)->RHS->push_back(s);
                s->productions->push_back(pro->at(k));
            }
            for(int t=0; t<symbols->at(i)->productions->size(); t++)
            {
                symbols->at(i)->productions->at(t)->RHS->push_back(s);
            }
            symbols->insert(symbols->begin()+i+1,s);
        }
    }
}
int LL1:: match(Production *p1,Production *p2)
{
    int i=0;
    while(i<p1->RHS->size() && i < p2->RHS->size() && p1->RHS->at(i) == p2->RHS->at(i))
    {
        i++;
    }
    return i;
}

Production* LL1::getCommon(Symbol *s ,int min_cnt,vector<Production *>*prod)
{
    Production * new_pr=new Production();
    new_pr->LHS=s;
    int i=0;
    while(i<min_cnt)
    {
        for(int j=0; j<prod->size(); j++)
        {
            if(j==0)
                new_pr->RHS->push_back(prod->at(j)->RHS->at(0));
            prod->at(j)->RHS->erase(prod->at(j)->RHS->begin());
        }
        i++;
    }
    return new_pr;
}
void LL1:: printSymbols()
{
    FILE * test=fopen("GrammarTest.txt","w+");
    for(int i=0; i<symbols->size(); i++)
    {
        if(symbols->at(i)->is_terminal)
            continue;
        string temp=symbols->at(i)->name+" -> ";
        for(int j=0; j<symbols->at(i)->productions->size(); j++)
        {

            for(int k=0; k<symbols->at(i)->productions->at(j)->RHS->size(); k++)
            {
                temp=temp+symbols->at(i)->productions->at(j)->RHS->at(k)->name+" ";
            }
            if(j+1<symbols->at(i)->productions->size())
                temp=temp+" |";
        }
        if(symbols->at(i)->is_nullable)
        {
            temp=temp+" | epsilon";
        }
        fprintf(test,"%s\n",temp.c_str());
    }
    for(int i=0; i<symbols->size(); i++)
    {
        if(symbols->at(i)->is_terminal)
            fprintf(test,"Non terminal : %s \n",symbols->at(i)->name.c_str());
    }
    fclose(test);
}
