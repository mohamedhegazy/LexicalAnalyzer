
#include "DFA.h"

DFA::DFA()
{
     table = new vector<map<char, int>*>();
     map<char, int>* dead_state = new map<char, int>();
     table->push_back(dead_state);
}

DFA::DFA(*NFA) {

    table = new vector<map<char, int>*>();
    map<char, int>* dead_state = new map<char, int>();
    table->push_back(dead_state);

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

}
void DFA::minimizeDFA() {

}


DFA::~DFA()
{
    //dtor
}

