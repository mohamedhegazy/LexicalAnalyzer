#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
using namespace std;

class Expression
{
    public:
        static const int OPERAND=0;
        static const int OPERATOR=1;
        int type;
        string operand;
        char operator_;
        Expression();
        Expression(int type,string value);
        Expression(int type,char value);
        virtual ~Expression();
    protected:
    private:
};

#endif // EXPRESSION_H
