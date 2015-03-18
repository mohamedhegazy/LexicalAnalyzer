#include <fstream>
#include "DFA.h"
#include "SubGroup.h"
#include <algorithm>
#include <sstream>
#include <math.h>       /* ceil */
#include <time.h>

DFA::DFA()
{

}

DFA::DFA(NFA * nfa)
{
    states = new vector<DFAState*>();
    states_minimized =new vector<DFAState*>();
    convertNFAtoDFA(nfa);
    clock_t tStart = clock();
    minimizeDFA();
    //printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    print();
}


void DFA::convertNFAtoDFA(NFA * nfa)
{


    vector<State*>*origing = nfa->get_states();

    map<string,DFAState*>* mapper = new map<string,DFAState*>();

    start_state = new DFAState();
    string sssss = *set_to_string(nfa->closure(nfa->get_start_state()), origing);

    (*mapper)[sssss] = start_state;

    queue<vector<State*>*>* q = new queue<vector<State*>*>();
    q->push(nfa->closure(nfa->get_start_state()));


    while(!q->empty())
    {

        vector<State*> *v = q->front();
        q->pop();
        string str = *set_to_string(v, origing);

        DFAState* current_state = mapper->at(str);

        TokenClass* t = TokenClass::epsilon;
        for(int i = 0; i < (int)v->size(); i++)
        {
            if(v->at(i)->get_accepting() && t->priority >= v->at(i)->get_token_class()->priority)
            {
                t = v->at(i)->get_token_class();
                current_state->set_accepting(true);
            }
        }
        current_state->set_tokenClass(t);
        states->push_back(current_state);

        for(int i = 0; i < 265; i++)
        {
            char trans_char = (char)i;
            if(trans_char == TokenClass::epsilon_char)
                continue;

            vector<State*>*r = nfa->move(v, trans_char);

            if(r->size() != 0)
            {
                string str2 = *set_to_string(r, origing);
                DFAState *st = NULL;

                if(mapper->find(str2) != mapper->end())
                {
                    st = mapper->at(str2);
                }
                else
                {
                    st = new DFAState();
                    (*mapper)[str2] = st;
                    q->push(r);
                }

                current_state->add_edge(st, trans_char);

            }

        }


    }

    for(int i = 0; i < (int)states->size(); i++)
    {
        states->at(i)->id = i;
    }
}


bool DFA::accepts(string str)
{
    DFAState * state = start_state->move(str);
    if(state == NULL)
        return false;

    return state->get_accepting();
}

vector<DFAState*>* DFA::get_states()
{
    return states;
}


string* DFA::set_to_string(vector<State*>*r, vector<State*>*origin)
{

    map<State*,int>m;
    for(int i = 0; i < (int)r->size(); i++)
    {
        m[r->at(i)] = 0;
    }

    int n = origin->size();

    char *c = new char [n+1];

    for(int i = 0; i < n; i++)
    {
        if(m.find(origin->at(i)) == m.end())
        {
            c[i] = '0';
        }
        else
        {
            c[i] = '1';
        }
    }

    c[n] = '\0';
    string *s = new string(c);

    return s;
}

DFAState* DFA::get_start_state()
{
    return start_state;
}


void DFA::minimizeDFA()
{
    /*
    for(int i=0; i<states->size(); i++)
    {
        DFAState * st=states->at(i);
        cout<<st->get_accepting()<<","<<st->get_tokenClass()->name<<endl;
    }
    */
    vector <SubGroup *>* groups=new vector<SubGroup *>();
    vector <SubGroup *>* new_groups=new vector<SubGroup *>();
//split by accepting and rejecting
    SubGroup* rejecting=new SubGroup();
    map<TokenClass*,SubGroup*> tok_sub;
    for(int i=0; i<states->size(); i++)
    {
        DFAState* st=states->at(i);
        if(st->get_accepting())
        {
            //accepting states are differentiated by the pattern they accept
            SubGroup* accepting=tok_sub[st->get_tokenClass()];
            if(accepting==NULL)
            {
                accepting=new SubGroup();
                accepting->put(st);
                groups->push_back(accepting);
                tok_sub[st->get_tokenClass()]=accepting;
            }
            else
            {
                accepting->put(st);
            }
        }
        else
        {
            rejecting->put(st);
        }
    }
    groups->push_back(rejecting);
    while(true)
    {
        //loop each subgroup
        for(int i=0; i<groups->size(); i++)
        {
            SubGroup *sub=groups->at(i);
            map< DFAState*, map<char,int> >m;//map each state to groups it can go to for every symbol
            //loop states of each subgroup
            for(int j=0; j<sub->group->size(); j++)
            {
                DFAState * st=sub->group->at(j);
                map<char,int> s;
                m[st]=s;
                for(int i = -127; i < 128; i++)
                {
                    char trans_char = (char)i;
                    DFAState *trans=st->move(trans_char);
                    if(trans!=NULL)
                    {
                        int index=getGroup(trans,groups);//keep track of groups
                        m[st][trans_char]=index;
                    }
                }
            }
            vector<SubGroup *>* temp=findGrouping(m);
            for(int k=0; k<temp->size(); k++)
            {
                new_groups->push_back(temp->at(k));
            }
        }
        if(equivalent(groups,new_groups))
        {
            break;
        }//terminating condition
        groups->clear();
        for(int i=0; i<new_groups->size(); i++)
        {
            groups->push_back(new_groups->at(i));
        }
        new_groups->clear();
    }
    map<DFAState *,DFAState *> map;//used to map states to its representatives
    // assumption to take first state in group as representative
    for(int i=0; i<groups->size(); i++)
    {
        SubGroup * gr=groups->at(i);
        DFAState * rep=gr->group->at(0);
        rep->set_representative(true);
        states_minimized->push_back(rep);
        for(int j=0; j<gr->group->size(); j++)
        {
            map[gr->group->at(j)]=rep;
        }
    }
    start_state_minimized=map[start_state];
    //constructing minimized graph
    for(int i=0; i<groups->size(); i++)
    {
        SubGroup * gr=groups->at(i);
        DFAState * rep=gr->group->at(0);
        //take representative and see where it goes
        for(int i = -127; i < 128; i++)
        {
            char trans_char = (char)i;
            DFAState *trans=rep->move(trans_char);
            if(trans!=NULL)
            {
                rep->add_edge_mini(map[trans],trans_char);
            }
        }
    }
}



vector<SubGroup *>* DFA::findGrouping(map< DFAState *,map<char,int> > m)
{
    map < DFAState *,bool> in;
    vector<SubGroup *>* new_grouping=new vector<SubGroup*>();
    typedef std::map< DFAState *,map<char,int> >::iterator it_type;
    for(it_type iterator = m.begin(); iterator != m.end(); iterator++)
    {
        in[iterator->first]=false;
    }
    for(it_type iterator = m.begin(); iterator != m.end(); iterator++)
    {
        SubGroup* new_sub=new SubGroup();
        if(!in[iterator->first])
        {
            new_sub->put(iterator->first);
            in[iterator->first]=true;
        }

        for(it_type iterator_2 = m.begin(); iterator_2 != m.end(); iterator_2++)
        {
            if(map_compare(iterator->second,iterator_2->second) && iterator->first!=iterator_2->first)
            {
                if(!in[iterator_2->first] )
                {
                    new_sub->put(iterator_2->first);
                    in[iterator_2->first]=true;
                }
            }
        }
        if(new_sub->group->size()>0)
            new_grouping->push_back(new_sub);
    }
    return new_grouping;
}
bool DFA::equivalent(vector<SubGroup *>* a,vector<SubGroup *>* b)
{
    if(a->size()!=b->size())
    {
        return false;
    }
    for(int i=0; i<a->size(); i++)
    {
        SubGroup *aa=a->at(i);
        bool match=false;
        for(int j=0; j<b->size(); j++)
        {
            SubGroup *bb=b->at(j);
            if(aa->group->size()==bb->group->size() && sameStates(aa,bb))
            {
                match=true;
            }
        }
        if(!match)
        return false;
    }
    return true;
}
bool DFA::sameStates(SubGroup *aa,SubGroup *bb)
{
    for(int i=0; i<aa->group->size(); i++)
    {
        DFAState * staa=aa->group->at(i);
        bool match =false;
        for(int j=0; j<bb->group->size(); j++)
        {
            DFAState *stbb=bb->group->at(j);
            if(staa==stbb)
            {
                match=true;
            }
        }
        if(!match)
        return false;
    }
    return true;
}
bool DFA::map_compare (map<char,int> lhs, map<char,int> rhs)
{
    return lhs.size() == rhs.size()
           && std::equal(lhs.begin(), lhs.end(),
                         rhs.begin());
}
int DFA::getGroup(DFAState * state,vector <SubGroup *> * groups)
{
    for(int i=0; i<groups->size(); i++)
    {
        SubGroup *gr=groups->at(i);
        if(std::find(gr->group->begin(), gr->group->end(), state)!=gr->group->end())
        {
            return i;
        }
    }
    return -1;
}
bool DFA::accepts_mini(string str)
{
    DFAState * state = start_state_minimized->move_mini(str);
    if(state == NULL)
        return false;
    return state->get_accepting();
}
vector<DFAState*>* DFA::get_mini_states()
{

    return states_minimized;
}
DFAState* DFA::get_mini_start_state()
{
    return start_state_minimized;
}
DFA::~DFA()
{
    //dtor
}
void DFA::print()
{
    string delim="";
    bool open=openOutputFile("table.txt");
    for(int i=32 ; i<127; i++)
    {
        delim=delim+"--------";
    }
    delim=delim+"--------";
    writeToFile(delim);
    string chars="|state  |";
    for(int i=32 ; i<127; i++)
    {
        char s=(char)i;
        chars=chars+"    "+string(1,s)+"  |";
    }
    chars=chars+"accepts|";
    writeToFile(chars);
    writeToFile(delim);

    for(int i=0; i<states_minimized->size(); i++)
    {
        string line="";
        string Result;
        ostringstream convert;
        convert << i;
        Result = convert.str();
        while(Result.size()<=6)
        {
            Result=Result+" ";
            if(Result.size()==7)
                break;
            Result=" "+Result;
        }
        line=line+"|"+Result+"|";
        DFAState * st=states_minimized->at(i);
        for(int j=32; j<127; j++)
        {
            char trans_char=(char)j;
            DFAState *trans=st->move(trans_char);
            if(trans==NULL)
            {
                line=line+"    -1 |";
            }
            else
            {
                int index=std::find(states->begin(), states->end(), trans)-states->begin();
                string Result;
                ostringstream convert;
                convert << index;
                Result = convert.str();
                while(Result.size()<=6)
                {
                    Result=Result+" ";
                    if(Result.size()==7)
                        break;
                    Result=" "+Result;
                }
                line=line+Result+"|";
            }

        }
        if(st->get_accepting())
        {
            string Result;
            ostringstream convert;
            convert << st->get_tokenClass()->priority;
            Result = convert.str();

            line=line+st->get_tokenClass()->name+","+Result;
        }
        else
        {
            line=line+"NULL";
        }
        writeToFile(line);
        writeToFile(delim);
    }

}
bool DFA::openOutputFile(string filePath)
{
    outputFile = new ofstream(&filePath[0], ios::out);
    return outputFile->is_open() && !outputFile->fail();
}
void DFA::writeToFile(string line)
{
    outputFile->write("\n",1);
    outputFile->write(&line[0],strlen(&line[0]));
}


//hussein method
void DFA::minimizeDFA2()
{
    int n = states->size();
    bool marked[n][n];
    DFAState *s1, *s2;


    for(int i = 0; i < n; i++)
    {
        s1 = states->at(i);
        for(int j = 0; j < n; j++)
        {
            s2 = states->at(j);

            if(s1->get_tokenClass()->name != s2->get_tokenClass()->name||
                    s1->get_accepting() != s2->get_accepting())
            {
                marked[i][j] = true;
            }
            else
            {
                marked[i][j] = false;
            }
        }
    }






    int count_marked;
    do
    {

        count_marked = 0;

        for(int i = 0; i < n; i++)
        {
            s1 = states->at(i);
            for(int j = 0; j < n; j++)
            {
                s2 = states->at(j);

                for(int k = 0; k < 256 && !marked[i][j]; k++)
                {
                    char c = (char)k;
                    DFAState * m1 = s1->move(c);
                    DFAState * m2 = s2->move(c);

                    if((m1 == NULL && m2 != NULL)||(m1 != NULL and m2 == NULL)||
                            ( m1 != NULL && m2 != NULL && marked[m1->id][m2->id]))
                    {
                        marked[i][j] = true;
                        count_marked++;
                    }

                }


            }
        }

    }
    while(count_marked != 0);

    /**
        for(int i =0 ; i < n; i++) {
            for(int j = 0; j < n; j++){
                if(!marked[i][j]) {
                    count_marked++;
                }
                cout<<marked[i][j]<<" ";
            }
            cout<<" , "<<states->at(i)->get_tokenClass()->name<<", "<<states->at(i)->get_accepting()<<" .. ";
            map<char,DFAState*>*m = states->at(i)->get_adjList();
            for(map<char,DFAState*>::iterator it = m->begin(); it != m->end(); it++) {
                cout<<"("<<it->first<<", "<<it->second->id<<") ";
            }
            cout<<endl;
        }
    */

    bool unused[n];
    for(int i = 0; i < n; i++)
    {
        unused[i] = true;
    }

    vector<DFAState*>* nState = new vector<DFAState*>();
    vector<DFAState*> *r = new vector<DFAState*>();
    map<DFAState*,DFAState*>mapper;

    for(int i = 0; i < n; i++)
    {
        if(unused[i])
        {

            DFAState* s = new DFAState();
            s->set_accepting(states->at(i)->get_accepting());
            s->set_tokenClass(states->at(i)->get_tokenClass());
            nState->push_back(s);
            r->push_back(states->at(i));

            for(int j = 0; j < n; j++)
            {
                if(!marked[i][j])
                {
                    unused[j] = false;
                    mapper[states->at(j)] = s;
                }
            }
        }

    }

    for(int i = 0; i <(int)r->size(); i++)
    {
        DFAState*s = r->at(i);
        DFAState*ns = mapper[s];

        map<char,DFAState*>*m = s->get_adjList();
        for(map<char,DFAState*>::iterator it = m->begin(); it != m->end(); it++)
        {
            ns->add_edge(mapper[it->second], it->first);
        }

    }

    cout<<states->size()<<" minimized to "<<nState->size()<<endl;
    this->states = nState;
    this->start_state = mapper[this->start_state];

}
