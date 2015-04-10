#include "Symbol.h"

Symbol::Symbol()
{
    //ctor
}
Symbol::Symbol(bool terminal,string name)
{
    //ctor
    this->is_terminal=terminal;
    this->name=name;
    this->productions=new vector<Production *>;
    this->is_nullable=false;
    this->just_added=false;
}

Symbol::~Symbol()
{
    //dtor
}
