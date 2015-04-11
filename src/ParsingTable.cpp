#include "ParsingTable.h"


ParsingTable::ParsingTable()
{
    //ctor
}
ParsingTable::ParsingTable(LL1 * ll1)
{
    this->ll1 = ll1;
    this->start_symbol= ll1->start_symbol;

    terminals = new  map<Symbol*, int>();
    nonterminals = new  map<Symbol*, int>();

    int j = 0;
    int k = 0;
    for(int i = 0; i < (int)ll1->symbols->size(); i++) {
        if(ll1->symbols->at(i)->is_terminal) {
            (*terminals)[ll1->symbols->at(i)] = j++;
        }
        else {
            (*nonterminals)[ll1->symbols->at(i)] = k++;
        }
    }
    (*terminals)[Symbol::$] = j;

    this->symbols = ll1->symbols;
    generate_first_follow();
    update_productions();
    build_table();

}

ParsingTable::~ParsingTable()
{
    //dtor
}



void ParsingTable::build_table() {

    for(int ii = 0 ;ii < (int)symbols->size(); ii++) {
        Symbol*s = symbols->at(ii);
        if(s->is_terminal)
            continue;

        int i = nonterminals->at(s);

        for(int jj = 0 ;jj < (int)s->productions->size(); jj++) {
            Production* p = s->productions->at(jj);

            for(set<Symbol*>::iterator it = p->first->begin(); it != p->first->end(); it++) {
                int j = terminals->at(*it);
                table[i][j] = p;
            }

            if(p->is_nullable) {// handel errors here please
                for(set<Symbol*>::iterator it = s->follow->begin(); it != s->follow->end(); it++) {
                    int j = terminals->at(*it);
                    table[i][j] = p;
                }
            }



        }// end of jj


        if(s->is_originaly_nullable && !s->is_terminal) {
            for(set<Symbol*>::iterator it = s->follow->begin(); it != s->follow->end(); it++) {
                int j = terminals->at(*it);
                table[i][j] = s->null_production;
            }
        }

        for(set<Symbol*>::iterator it = s->follow->begin(); it != s->follow->end(); it++) {
            int j = terminals->at(*it);
            if(table[i][j] == NULL)
                table[i][j] = Production::sync;
        }

    }// end of ii

}

string ParsingTable::toString() {
    return toString(20);
}

 string ParsingTable::toString(int width) {

    std::ostringstream ans;

    ans.width(width);
    ans<<left<<" ";
    for(map<Symbol*,int>::iterator it = terminals->begin(); it !=  terminals->end(); it++) {
        ans.width(width);
        ans<<left<<it->first->name;
    }
    ans<<endl;

    for(map<Symbol*,int>::iterator it = nonterminals->begin(); it !=  nonterminals->end(); it++) {
        int i = it->second;
        ans.width(width);
        ans<<left<<it->first->name;
        for(map<Symbol*,int>::iterator it2 = terminals->begin(); it2 !=  terminals->end(); it2++) {
            int j = it2->second;

            ans.width(width);
            if(table[i][j] == NULL)
                ans<<left<<" ";
            else
                ans<<left<<table[i][j]->toString();
        }
        ans<<endl;
    }


    return ans.str();

 }

void ParsingTable::update_productions() {
    for(int ii = 0 ;ii < (int)symbols->size(); ii++) {
            Symbol*s = symbols->at(ii);
            for(int jj = 0 ;jj < (int)s->productions->size(); jj++) {
                Production* p = s->productions->at(jj);
                int i = 0;
                Symbol* ss = p->RHS->at(i);
                p->first->insert(ss->first->begin(), ss->first->end());

                while(i < (int)p->RHS->size() - 1 && ss->is_nullable) {
                    i++;
                    ss = p->RHS->at(i);
                    p->first->insert(ss->first->begin(), ss->first->end());
                }

                if(i == (int)p->RHS->size() - 1 && ss->is_nullable) {
                    p->is_nullable = true;
                }

                /*
                cout<<p->toString()<<endl;
                for(set<Symbol*>::iterator it = p->first->begin(); it != p->first->end(); it++) {
                    cout<<(*it)->name<<" ";
                }
                cout<<endl;
                */

            }// end of jj

        }// end of ii
}

void ParsingTable::generate_first_follow() {
  // algorithm :  http://homepages.ius.edu/RWISMAN/C431/html/Chapter3.htm


    vector<Symbol*> symbols = *(ll1->symbols);
    int n = symbols.size();

    for(int i = 0; i < n; i++) {
        if(symbols[i]->is_terminal) {
            symbols[i]->first->insert(symbols[i]);
        }
        if(symbols[i]->is_nullable) {
            symbols[i]->set_nullabel();
        }
    }

    this->start_symbol->follow->insert(Symbol::$);


    bool updated = true;
    while(updated) {
        updated = false;

        for(int ii = 0; ii < n; ii++) {

            Symbol*symbol = symbols[ii];
            vector<Production*> productions = *(symbol->productions);
            int m = productions.size();

            for(int jj = 0; jj < m; jj++) {


                Production *p = productions[jj];

                if(p->RHS->size() == 0)
                    continue;

                int k = 0;
                for(k = 0; k < (int)p->RHS->size() && p->RHS->at(k)->is_nullable; k++);
                if(k == (int)p->RHS->size()) {
                    symbol->is_nullable = true;
                }

                k = p->RHS->size();

               // cout<<p->toString()<<endl;

                for(int i = 0; i < k; i++) {

                  bool all_nullable = true;
                    for(int t = 0; t < i && all_nullable; t++) {
                        all_nullable = p->RHS->at(t)->is_nullable ;
                    }


                    if(all_nullable) {
                        int pre = symbol->first->size();
                        Symbol* ss = p->RHS->at(i);
                        for(set<Symbol*>::iterator t = ss->first->begin(); t != ss->first->end(); t++) {
                                symbol->first->insert(*t);
                        }
                        if(pre != (int)symbol->first->size()) {
                            updated = true;
                        }
                    }


                    for(int j = i + 1; j < k; j++) {

                        all_nullable = true;
                         for(int t = i + 1; t < k && all_nullable; t++) {
                            all_nullable = p->RHS->at(t)->is_nullable ;
                        }

                        if(all_nullable) {
                            Symbol* ss = p->RHS->at(i);
                            int pre = ss->follow->size();
                            for(set<Symbol*>::iterator t = symbol->follow->begin(); t != symbol->follow->end(); t++) {
                                    ss->follow->insert(*t);
                            }
                            if(pre != (int)ss->follow->size()) {
                                updated = true;
                            }
                        }



                        all_nullable = true;
                         for(int t = i + 1; t < j && all_nullable; t++) {
                            all_nullable = p->RHS->at(t)->is_nullable ;
                        }

                        if(all_nullable) {
                            Symbol* ss = p->RHS->at(i);
                            Symbol* ss2 = p->RHS->at(j);
                            int pre = ss->follow->size();
                            for(set<Symbol*>::iterator t = ss2->first->begin(); t != ss2->first->end(); t++) {
                                    ss->follow->insert(*t);
                            }
                            if(pre != (int)ss->follow->size()) {
                                updated = true;
                            }
                        }


                    }// end of j
                }// end of i


            }// end of jj

        }// end of ii

    }// end of while

}






















