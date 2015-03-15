#include "DFA.h"
#include "DFAState.h"




DFA::DFA()
{
     table = new vector<map<char, int>*>();
     map<char, int>* dead_state = new map<char, int>();
     table->push_back(dead_state);
}

DFA::DFA(NFA * nfa) {
    this->nfa=nfa;
    table = new vector<map<char, int>*>();
    map<char, int>* dead_state = new map<char, int>();
    table->push_back(dead_state);
    // e7na el gdid yalaaaaaaaa :D
    this->possibleTrans="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.;_-+*&^%$#!@{}()";
    states=new vector<DFAState*>();
    convertNFAtoDFA();
    minimizeDFA();
}


int DFA::move(int current_state, char trans_char) {
    if(current_state >= (int)table->size()) {
        return 0;
    }
    map<char, int> m = *table->at(current_state);
    return m[trans_char];
}


void DFA::convertNFAtoDFA() {
    DFAState* DFAStart=new DFAState(nfa->closure(nfa->get_start_state()));
    DFAStart->setStart();
    states->push_back(DFAStart);
    //loop over every unmarked DFA State and apply the DFA Algorithm
    for(int j=0;j<this->states->size();j++){
        if(!this->states->at(j)->isMarked()){
                moveDFA(this->states->at(j));
                this->states->at(j)->setMarked();
        }
    }


}

void DFA::moveDFA(DFAState* state_){
    for(int i=0;i<possibleTrans.size();i++){
        moveDFA(state_,possibleTrans.at(i));
    }
}

void DFA::moveDFA(DFAState* state_,char trans_char){
    vector <State*>* moveVector=nfa->move(state_->getNFAStates(),trans_char);

    /*
    vector <State*>* tempDFAstate=new vector<State*>();
    tempDFAstate=nfa->closure(moveVector->at(0));
    for(int i=1;i<moveVector->size();i++){
        Union(tempDFAstate,nfa->closure(moveVector->at(i)));
    }
*/


    if(!exist(moveVector)){
            DFAState* newDfaState=new DFAState(moveVector);
            state_->addEdge(newDfaState,trans_char);
    }
    else{

    }
}

void DFA::minimizeDFA() {

}

void DFA::Union(vector<State*>* st1,vector<State*>* st2){
    for(int i=0;i<st2->size();i++){
        if(!(std::find(st1->begin(),st1->end(),st2->at(i)) != st1->end())){
            st1->push_back(st2->at(i));
        }
    }
}

bool DFA::exist(vector<State*>* dfstate){

    return false;
}



DFA::~DFA()
{
    //dtor
}

