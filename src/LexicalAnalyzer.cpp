#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer()
{
    //ctor
}


 LexicalAnalyzer::LexicalAnalyzer(DFA* minimizedDFA) {
    this->dfa = minimizedDFA;

 }

LexicalAnalyzer::~LexicalAnalyzer()
{
    //dtor
}
Token* LexicalAnalyzer::getTokenNextToken() {


    Token* r = NULL;

    string line = "ll";
    getline(source_file, line);

    if(!source_file.eof()) {

        r = new Token();
        r->tokenClass = TokenClass::epsilon;
        r->attribute_value = "epsilon";

    }

    return r;
}


void LexicalAnalyzer::setSourceCodeFile(string file){
    this->file_name = file;
   // source_file.open(file);

}



