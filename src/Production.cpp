#include "Production.h"


Production*Production::sync = new Production();

Production::Production()
{
    //ctor
    this->RHS=new vector<Symbol *>;

    first = new set<Symbol*>();
}



string Production::toString() {



    string ans = "";
    if(this == sync) {
        ans = "sync";
    }

    else {
        ans = LHS->name+" -> ";
        for(int i = 0; i < (int)RHS->size(); i++) {
            ans += RHS->at(i)->name+" ";
        }
    }

    return ans;
}
Production::~Production()
{
    //dtor
}
