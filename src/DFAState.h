
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


        DFAState*move_mini(char trans_char);
        DFAState*move_mini(string str);
        map<char,DFAState*>* get_adjList_mini();
        void add_edge_mini(DFAState*state, char trans_char);
        bool get_representative();
        void set_representative(bool b);

        virtual ~DFAState();
                int id;


    protected:
    private:
        bool accepting;
        map<char,DFAState*>* adjList;
        TokenClass* token_class;
        bool representative;//if this is true the state was chosen to be representative
        map<char,DFAState*>* adjList_mini;//this contains edges to other representative states


};


#endif // DFASTATE_H




