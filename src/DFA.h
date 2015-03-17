#ifndef DFA_H
#define DFA_H
#include "State.h"
#include "NFA.h"
#include "DFAState.h"
#include "State.h"
#include <vector>
#include <map>
#include <queue>
#include <string>
#include "SubGroup.h"
using namespace std;

class DFA
{
    public:
        DFA();
        DFA(NFA * nfa);//transfrom NFA to DFA and minimize it
        int move(int current_state, char trans_char);//get the next state for the transition char
        void print();//prints dfa as table
        DFAState* get_start_state();
        vector<DFAState*>*get_states();
        bool accepts(string str);

        vector<SubGroup *>*  findGrouping(map< DFAState *,map<char,int> > map);
        bool equivalent(vector<SubGroup *>* a,vector<SubGroup *>* b);
        bool sameStates(SubGroup *aa,SubGroup *bb);
        bool map_compare (map<char,int> lhs, map<char,int> rhs);
        int getGroup(DFAState * state,vector <SubGroup *> * groups);
        bool accepts_mini(string str);
        vector<DFAState*>*get_mini_states();
        DFAState* get_mini_start_state();
        void minimizeDFA2();

        virtual ~DFA();
    protected:
    private:
        void convertNFAtoDFA(NFA* nfa);
        string* set_to_string(vector<State*>*r, vector<State*> * origin);
        void minimizeDFA();// using disjoint set will be cool
        DFAState*start_state;
        vector<DFAState*>*states;
        void writeToFile(string line);
        bool openOutputFile(string filePath);
        ofstream *outputFile;
        DFAState*start_state_minimized;
        vector<DFAState*>*states_minimized;

};

#endif // DFA_H
