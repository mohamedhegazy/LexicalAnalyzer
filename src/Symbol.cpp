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
    this->is_originaly_nullable=false;
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




 string Symbol::toString() {

    string ans = name+" .. ";
    ans += "first :( ";
    for(set<Symbol*>::iterator it = first->begin(); it != first->end(); it++) {
        ans += (*it)->name + " ";
    }

    ans += ") ... ";
    ans += "follow :( ";
    for(set<Symbol*>::iterator it = follow->begin(); it != follow->end(); it++) {
        ans += (*it)->name + " ";
    }
    ans += ")";

    return ans;
 }







string Symbol::toString(int width) {


    std::ostringstream ans;

    ans.width(width);

    ans<<left<<name;
    string tt = "first :( ";
    for(set<Symbol*>::iterator it = first->begin(); it != first->end(); it++) {
        tt += (*it)->name + " ";
    }
    tt += ")";

    ans.width(width);
    ans<<left<<tt;


    tt = "follow :( ";
    for(set<Symbol*>::iterator it = follow->begin(); it != follow->end(); it++) {
        tt += (*it)->name + " ";
    }
    tt += ")";

    ans.width(width);
    ans<<left<<tt;

    ans << " nullable : ";
    ans << (is_nullable ? "true": "false");
    ans << " terminal : ";
    ans << (is_terminal? "true": "false");






    return ans.str();
}













