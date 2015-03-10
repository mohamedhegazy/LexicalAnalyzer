#include "Expression.h"

Expression::Expression()
{
    //ctor
}

Expression::~Expression()
{
    //dtor
}

Expression::Expression(int type,string value){
this->type=type;
this->operand=value;
}
Expression::Expression(int type,char value){
this->type=type;
this->operator_=value;
}
