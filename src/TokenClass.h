#ifndef TOKENCLASS_H
#define TOKENCLASS_H
#include <string>
#include <iostream>

using namespace std;

class TokenClass
{
    public:

        static TokenClass* epsilon;
        static char epsilon_char;
        string get_token_name();
        string name;
        int priority;//may be deleted later


        TokenClass(string name, int priority);
        TokenClass();
        TokenClass* clone();
        virtual ~TokenClass();
    protected:
    private:

};

#endif // TOKENCLASS_H
