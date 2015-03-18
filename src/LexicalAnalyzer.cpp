#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer()
{
    //ctor
}


 LexicalAnalyzer::LexicalAnalyzer(DFA* minimizedDFA) {
    this->dfa = minimizedDFA;
    currentIndex=0;
 }

LexicalAnalyzer::~LexicalAnalyzer()
{
    //dtor
}
Token* LexicalAnalyzer::getTokenNextToken() {

/*
    Token* r = NULL;

    string line = "ll";
    getline(source_file, line);

    if(!source_file.eof()) {

        r = new Token();
        r->tokenClass = TokenClass::epsilon;
        r->attribute_value = "epsilon";

    }

    return r;
*/

    DFAState* start=dfa->get_mini_start_state();
    vector<DFAState*>* DFAVector=new vector<DFAState*>();
    DFAVector->push_back(start);

    string currentString=tokens[currentIndex];

    int i=0;
    DFAState* currentState=start->move_mini(currentString[i]);
    i++;
    while(i<currentString.size() && ( currentState != NULL ) ){
        DFAVector->push_back(currentState);
        currentState=currentState->move_mini(currentString[i]);
        i++;
    }

    DFAState* candidate=new DFAState();
    for(int i=DFAVector->size()-1;i>-1;i--){
        if(DFAVector->at(i)->get_accepting()){
            candidate=DFAVector->at(i);
        }
    }

    if(candidate->get_accepting()){ // longest accepting match
        Token* tokenFound=new Token();
        tokenFound->tokenClass=candidate->get_tokenClass();
        tokenFound->attribute_value=currentString;
        return tokenFound;
    }
    currentIndex++;
    return NULL;
}


void LexicalAnalyzer::setSourceCodeFile(string file){
    this->file_name = file;

    source_file.open(file.c_str());
    if(!source_file.good()){
        cout<<"Bad file error!"<<endl;
    }

    std::string input;

    while(source_file >> input){
        tokens.push_back(input);
    }

}



