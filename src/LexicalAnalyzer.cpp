#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer()
{
    //ctor
}


LexicalAnalyzer::LexicalAnalyzer(DFA* minimizedDFA)
{
    this->dfa = minimizedDFA;
    currentIndex=0;
    DFAVector=new vector<DFAState*>();
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    //dtor
}
Token* LexicalAnalyzer::getTokenNextToken()
{

    if((currentIndex >= tokens.size() ) && (currentString.size()==0))
    {
        return NULL;
    }
    int stringIndex=0;
    string tempString="";
    DFAVector=new vector<DFAState*>();
    DFAState* start=dfa->get_mini_start_state();
    DFAVector->push_back(start);
    if(currentString.size()==0)
    {

        currentString=tokens[currentIndex];
        currentIndex++;
    }

    //~~~~~~~~~Check if this is a clear valid input ~~~~~~~~~~~~
    DFAState* tempState=dfa->get_mini_start_state()->move(currentString);
    if(tempState != NULL)
    {
        Token* toke=new Token();
        toke->tokenClass=tempState->get_tokenClass();
        toke->attribute_value=currentString;
        currentString="";
        if(toke->tokenClass->name == "epsilon")
        {
            toke->tokenClass->name ="Error : Invalid input";

        }
        return toke;
    }

    int i=0;
    DFAState* currentState=start->move_mini(currentString[i]);
    DFAVector->push_back(currentState);
    // if(currentState != NULL){
    i++;
    //}
    bool atend=false;
    while(i<currentString.size() && ( currentState != NULL ) && (currentState->move_mini(currentString[i]) != NULL))
    {
        atend=true;
        DFAState* tempState=currentState->move_mini(currentString[i]);
        currentState=tempState;
        if(currentState != NULL)
        {
            DFAVector->push_back(currentState);
        }
        i++;
    }
    //if(atend){
    /*if(currentState == NULL && i<currentString.size())
        stringIndex=i-1;
    }
    else{
        stringIndex=i;
    }
    */

    stringIndex=i;
    if(stringIndex<currentString.size()) //there exists undefined input
    {
        tempString=currentString.substr(stringIndex);

    }
    //if(i>0){
    int size_=currentString.size()-tempString.size();
    currentString=currentString.substr(0,size_);
    //}

    //if(stringIndex==0 ){ // if an invalid input occured , print an error message in the file
    if(currentState==NULL && i==1)
    {
        Token* error_= new Token();
        error_->tokenClass=new TokenClass("error : invalid input",-1000);
        error_->attribute_value=currentString;
        currentString=tempString;
        return error_;
    }
    DFAState* candidate=new DFAState();
    vector<DFAState*>* tempVector=new vector<DFAState*>();
    for(int i=DFAVector->size()-1; i>-1; i--)
    {
        if(DFAVector->at(i)->get_accepting())
        {
            candidate=DFAVector->at(i);
            break;
        }
    }

    Token* tokenFound=new Token();
    tokenFound->tokenClass=candidate->get_tokenClass();
    tokenFound->attribute_value=currentString;
    DFAVector=tempVector;
    currentString=tempString;
    return tokenFound;
}


void LexicalAnalyzer::setSourceCodeFile(string file)
{
    this->file_name = file;
    source_file.open(file.c_str());
    std::string input;

    int i=0;

    while(source_file.peek()!=EOF)
    {
        char c;
        source_file.get(c);
        if(c!='\n' && c!='\t' && c!='\b')
            temp_char[i++]=c;
    }
    size=i;
    /*
    for(int i=0; i<size; i++)
    {
        cout<<string(1,temp_char[i])<<endl;
    }
    */

    /*
    source_file >> input;
    tokens.push_back(input);
    while(!source_file.eof())
    {
        if(input.compare("\n") != 0  || input.compare(" ")){
        //tokens.push_back(input);
        }
        cout<<tokens.at(i)<<endl;
        i++;
        source_file >> input;
        tokens.push_back(input);
    }
    if(input.compare("\n") != 0 || input.compare(" ") ){
      //  tokens.push_back(input);
        }
        cout<<tokens.size()<<endl;
    //tokens.push_back(input);
       // cout<<"ll : "<<tokens.size()<<endl;
       */
}

Token* LexicalAnalyzer::getNextToken()
{
    if(index>=size)
        return NULL;
    DFAState * st=dfa->get_mini_start_state();
    vector <DFAState*> * temp=new vector<DFAState *>();
    string attr_val="";
    while(st!=NULL)
    {
        st=st->move_mini(temp_char[index++]);
        if(temp_char[index-1]!=' '&&temp_char[index-1]!='\n')//ignore blanks,newline
        {
            temp->push_back(st);
            attr_val=attr_val+string(1,temp_char[index-1]);
        }

    }
    if(temp->size()==1 && temp->at(0)==NULL)
        temp->clear();
    DFAState * latest_accepted=NULL;
    int i;
    for(i=temp->size()-1; i>=0 && index>0; i--,index--)
    {
        DFAState *cur=temp->at(i);
        if(cur !=NULL && cur->get_accepting())
        {
            latest_accepted=cur;
            break;
        }
    }
    attr_val=attr_val.substr(0,i+1);
    Token * tok=new Token();
    TokenClass * cl=new TokenClass();
    tok->tokenClass=cl;
    if(latest_accepted==NULL)
    {

        tok->tokenClass->name="ERROR!";
    }
    else
    {
        tok->tokenClass=latest_accepted->get_tokenClass();
        tok->attribute_value=attr_val;
    }
    return tok;

}





















