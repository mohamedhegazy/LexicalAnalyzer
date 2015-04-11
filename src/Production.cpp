#include "Production.h"


Production*Production::sync = new Production();

Production::Production()
{
    //ctor
    this->RHS=new vector<Symbol *>;

    first = new set<Symbol*>();
}



string Production::toString() {

    if(this == sync) {
        return "sync";
    }

    string ans = LHS->name+" -> ";
    for(int i = 0; i < RHS->size(); i++) {
        ans += RHS->at(i)->name+" ";
    }

    return ans;
}
Production::~Production()
{
    //dtor
}
