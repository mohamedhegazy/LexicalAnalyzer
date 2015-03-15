#include "DFAState.h"

DFAState::DFAState(vector <State*>* NFAStates )
{
    this->Marked=false;
    this->NFAStates=NFAStates;
    for(int j=0;j<NFAStates->size();j++){
        if(NFAStates->at(j)->get_accepting()){
            this->isAccepting=true;
            break;
        }

    }
}

void DFAState::addEdge( DFAEdge* DFAEdge){
    //TODO
}

void DFAState::addEdge(DFAState* to,char trans_char){
    //TODO
}

void DFAState::setMarked(){
    Marked=true;
}

bool DFAState::isMarked(){
    return Marked;
}

void DFAState::setStart(){
    this->isStart=true;
}

vector<State*>* DFAState::getNFAStates(){
    return this->NFAStates;
}
DFAState::~DFAState()
{
    //dtor
}
