#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer()
{
    //ctor
}

SyntaxAnalyzer::SyntaxAnalyzer(ParsingTable* table, LexicalAnalyzer* lexicalAnalyzer)
{
    this->table = table;
    this->lexicalAnalyzer = lexicalAnalyzer;
}


SyntaxAnalyzer::~SyntaxAnalyzer()
{
    //dtor
}
void SyntaxAnalyzer:: start_parsing() {


    parsing_result_productions  = new  vector<Production*>();
    parsing_result_string = new  vector<string>();
    successful_parsing = true;



    stack<Symbol*> * s = new stack<Symbol*>();

    Token* token = get_next_token();
    s->push(Symbol::$);
    s->push(table->get_start_symbol());

    while(token != NULL && s->size() != 0) {

        Symbol* curretn_symbol = s->top();
        s->pop();

        if(!curretn_symbol->is_terminal) {
                Production*p = table->get_next_production(curretn_symbol, token);
                if(p != NULL && p != Production::sync) {// every thing is awsome

                    parsing_result_productions->push_back(p);
                    parsing_result_string->push_back(p->toString());

                    if(p->LHS->null_production == p)
                        continue;

                    vector<Symbol*> *ss = p->RHS;
                    for(int i = ss->size() - 1; i >= 0; i--) {
                        s->push(ss->at(i));
                    }

                }
                else if(p == NULL) {
                    string sss = "--- dicarted token : "+token->tokenClass->name+"  current symbol : "+curretn_symbol->name;
                    parsing_result_string->push_back(sss);
                    s->push(curretn_symbol);
                    token = get_next_token();
                    successful_parsing = false;
                }
                else if(p == Production::sync) {
                    // nothing to do here
                    cout<<"sync"<<endl;
                    parsing_result_string->push_back("sync");
                    successful_parsing = false;
                }
        }
        else {
               if(curretn_symbol->name != token->tokenClass->name) {
                    // we need to handel error here
                   string sss = "*** expecting : "+curretn_symbol->name+"  got : "+token->tokenClass->name;
                   parsing_result_string->push_back(sss);
                   successful_parsing = false;
               }
               else {
                    string sss = "+++ acceted : "+curretn_symbol->name+" ("+token->attribute_value+" )";
                    parsing_result_string->push_back(sss);
                    token = get_next_token();
               }
        }



    }






}


Token* SyntaxAnalyzer::get_next_token() {

    return lexicalAnalyzer->getNextToken();

    /*
    if(testing_index == (int)testing_tokens->size()) {
        return NULL;
    }

    return testing_tokens->at(testing_index++);
    */
}


vector<Production*>* SyntaxAnalyzer::get_parsing_result_productions() {
    return parsing_result_productions;
}
vector<string>* SyntaxAnalyzer::get_parsing_result_string() {
    return parsing_result_string;
};
bool SyntaxAnalyzer::get_successful_parsing() {
    return successful_parsing;
}











