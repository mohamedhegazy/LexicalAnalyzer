#include "Symbol.h"


Symbol*Symbol::$ = new Symbol(true,"$");
Symbol*Symbol::espilon = new Symbol(true,"epsilon");


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

    first = new set<Symbol*>();
    follow = new set<Symbol*>();

}

void Symbol::set_nullabel() {
    is_originaly_nullable = true;
    null_production = new Production();
    null_production->LHS = this;
    null_production->RHS->push_back(Symbol::espilon);
}
Symbol::~Symbol()
{
    //dtor
}
