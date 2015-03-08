#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;
#include "TokenClass.h"
class Token
{
    public:
        string attribute_value;
        TokenClass tokenClass;

        Token();
        virtual ~Token();
    protected:
    private:
};

#endif // TOKEN_H
