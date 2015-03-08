#ifndef TOKENCLASS_H
#define TOKENCLASS_H
#include <string>
using namespace std;

class TokenClass
{
    public:
        string name;
        int id;//may be deleted later

        TokenClass();
        virtual ~TokenClass();
    protected:
    private:
};

#endif // TOKENCLASS_H
