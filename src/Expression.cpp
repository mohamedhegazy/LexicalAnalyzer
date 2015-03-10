#include "Expression.h"

Expression::Expression()
{
    //ctor
}

Expression::~Expression()
{
    //dtor
}

Expression::Expression(string value){
this->type=OPERAND;
this->operand=value;
}
Expression::Expression(char value){
this->type=OPERATOR;
this->operator_=value;
}
