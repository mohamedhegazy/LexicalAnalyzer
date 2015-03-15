
#ifndef DFASTATE_H
#define DFASTATE_H

#include "TokenClass.h"
#include <iostream>
#include <string>
#include <string.h>
#include <map>


using namespace std;

class DFAState
{
    public:
        DFAState();
        DFAState*move(char trans_char);
        DFAState*move(string str);
        map<char,DFAState*>* get_adjList();
        TokenClass*get_tokenClass();
        void add_edge(DFAState*state, char trans_char);
        void printer();
        void set_tokenClass(TokenClass* tokenClass);
        bool get_accepting();
        void set_accepting(bool b);
        virtual ~DFAState();



    protected:
    private:
        bool accepting;
        map<char,DFAState*>* adjList;
        TokenClass* token_class;



};


#endif // DFASTATE_H




