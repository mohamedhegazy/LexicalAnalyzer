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
}

Symbol::~Symbol()
{
    //dtor
}
