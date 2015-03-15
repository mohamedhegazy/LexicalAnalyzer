#include "TokenClass.h"



TokenClass* TokenClass::epsilon = new TokenClass("epsilon",10000000);
char TokenClass::epsilon_char = (char)0xde;

 TokenClass* TokenClass:: clone() {
    TokenClass* result= new TokenClass();
    result->priority = this->priority;
    result->name = this->name;
    return result;
 }


TokenClass::TokenClass()
{

}


 string TokenClass::get_token_name() {
    return name;
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
