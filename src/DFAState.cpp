#include "DFAState.h"

DFAState::DFAState()
{
    accepting = false;
    adjList = new map<char,DFAState*>();
    token_class = TokenClass::epsilon;
}





DFAState*DFAState::move(char trans_char)
{

    DFAState*result = NULL;


    if(adjList->find(trans_char) != adjList->end())
    {
        result = adjList->at(trans_char);
    }

    return result;

}


DFAState*DFAState::move(string str)
{

    DFAState* current = this;
    int i = 0;
    int n = strlen(&str[0]);
    while(current != NULL && i < n)
    {
        current = current->move(str[i]);
        i++;
    }

    return current;
}

bool DFAState::get_accepting()
{
    return accepting;
}

void DFAState::set_accepting(bool b)
{
    accepting = b;
}

void DFAState::set_tokenClass(TokenClass* tokenClass)
{
    token_class = tokenClass;
}

void DFAState::add_edge(DFAState*state, char trans_char)
{
    (*adjList)[trans_char] = state;
}


void DFAState::printer()
{

    cout<<"accepting : "<<accepting<<", "<<get_tokenClass()->get_token_name()<<" .. ";
    for(map<char,DFAState*>::iterator it = adjList->begin(); it != adjList->end(); it++)
    {
        cout<<"("<<(it->second)->get_tokenClass()->get_token_name()<<", "<<it->first<<")";
    }

}



map<char,DFAState*>* DFAState::get_adjList()
{
    return adjList;
}

TokenClass*DFAState::get_tokenClass()
{
    return token_class;
}


DFAState::~DFAState()
{
    //dtor
}




DFAState* DFAState::move_mini(char trans_char)
{
    DFAState*result = NULL;


    if(adjList_mini->find(trans_char) != adjList_mini->end())
    {
        result = adjList_mini->at(trans_char);
    }

    return result;


}
DFAState*DFAState::move_mini(string str)
{
    DFAState* current = this;
    int i = 0;
    int n = strlen(&str[0]);
    while(current != NULL && i < n)
    {
        current = current->move_mini(str[i]);
        i++;
    }

    return current;
}
map<char,DFAState*>* DFAState::get_adjList_mini()
{
    return adjList_mini;

}
void DFAState::add_edge_mini(DFAState*state, char trans_char)
{
    (*adjList_mini)[trans_char] = state;
}
bool DFAState::get_representative()
{
    return this->representative;
}
void DFAState::set_representative(bool b)
{
    adjList_mini = new map<char,DFAState*>();
    this->representative=b;
}
