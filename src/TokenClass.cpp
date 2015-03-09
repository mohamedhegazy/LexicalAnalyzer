#include "TokenClass.h"



TokenClass* TokenClass::epsilon = new TokenClass("epsilon",-1);
char TokenClass::epsilon_char = (char)0xde;




TokenClass::TokenClass()
{

}

TokenClass::TokenClass(string name, int priority)
{
    this->name = name;
    this->priority = priority;
}



TokenClass::~TokenClass()
{
    //dtor
}
