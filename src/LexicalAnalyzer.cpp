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
    if(currentIndex >= tokens.size())
    {
        return NULL;
    }
    int stringIndex=0;
    string tempString="";
    //if(DFAVector->size()==0)
    //if(currentString.size() == 0)
    //{
    DFAVector=new vector<DFAState*>();
    DFAState* start=dfa->get_mini_start_state();
    DFAVector->push_back(start);
    if(currentString.size()==0)
    {
        currentString=tokens[currentIndex];
        currentIndex++;
    }
   // cout<<"Current string tested : " <<currentString <<endl;
    DFAState* tempState=dfa->get_mini_start_state()->move(currentString);
    if(tempState != NULL){
         Token* toke=new Token();
         toke->tokenClass=tempState->get_tokenClass();
         toke->attribute_value=currentString;
         currentString="";
//         currentIndex++;
        //  cout<<"clear input !"<<endl;
         return toke;
    }




    int i=0;
    DFAState* currentState=start->move_mini(currentString[i]);
    i++;
    while(i<currentString.size() && ( currentState != NULL ) )
    {
        DFAVector->push_back(currentState);
        DFAState* tempState=currentState->move_mini(currentString[i]);
        currentState=tempState;
        //currentState=currentState->move_mini(currentString[i]);
        i++;
    }
    stringIndex=i-1;
    if(stringIndex<currentString.size()) //there exists undefined input
    {
        tempString=currentString.substr(stringIndex);

    }
    currentString=currentString.substr(0,i);
    // }



    DFAState* candidate=new DFAState();
    vector<DFAState*>* tempVector=new vector<DFAState*>();
    for(int i=DFAVector->size()-1; i>-1; i--)
    {
        if(DFAVector->at(i)->get_accepting())
        {
            candidate=DFAVector->at(i);


            /*for(int j=i+1; j<DFAVector->size(); j++)
            {
                tempVector->push_back(DFAVector->at(j));
            }
            */
            break;
        }
    }

    //  if(candidate->get_accepting())  // longest accepting match
    // {
    Token* tokenFound=new Token();
    tokenFound->tokenClass=candidate->get_tokenClass();
    tokenFound->attribute_value=currentString;
    DFAVector=tempVector;
    currentString=tempString;
    return tokenFound;
    //}
    //return NULL;
}


void LexicalAnalyzer::setSourceCodeFile(string file)
{
    this->file_name = file;

    //source_file.open(file.c_str(),std::ifstream::in);
    source_file.open(file.c_str());


    /*
    if(!source_file.good())
    {
        cout<<"Bad file error!"<<endl;
    }
    */
    std::string input;

    int i=0;
    source_file >> input;
    while(!source_file.eof())
    {
        tokens.push_back(input);
        cout<<tokens.at(i)<<endl;
        i++;
        source_file >> input;
    }
}



