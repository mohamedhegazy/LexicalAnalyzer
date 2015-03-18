#include "RegExParser.h"
#include <stack>          // std::stack
#include <algorithm>
#include <sstream>
const int SYMBOL=0;
const int ALPHA=1;
const int REG_DEF_SEPARATOR=2;
const int REG_EXP_SEPARATOR=3;//we know now the token class name
const int ESCAPE=4;//lookahead one step
const int LEFT_PARENTHESE=5;//concatenate operation
const int RIGHT_PARENTHESE=6;//empty operation stack untill left parenthese
const int LEFT_PARENTHESE_INDEX=7;//punctuation
const int RIGHT_PARENTHESE_INDEX=8;
const int LEFT_CURLY=9;//keyword class
const int RIGHT_CURLY=10;
const int OPERATOR=11;// +,|,(,),*,-
const int SPACE=12;
const int LEFT_PARENTHESE_PRIORITY=15;
const int OR_PRIORITY=16;
const int RANGE_PRIORITY=17;
const int CONCAT_PRIORITY=18;
const int CLOSURE_PRIORITY=19;
const char CONCAT_OP=17;
const char TEMP_OP=18;

RegExParser::RegExParser()
{
    //ctor
}
RegExParser::RegExParser(string regex)
{
    //ctor
    endOfFile=false;
    openInputFile(regex);
    inputFile = new ifstream(&regex[0], ios::in);
    regular_defintions=new vector<RegDef *>();
    regular_expressions=new vector<RegEx *>();
    parse();
}
RegExParser::~RegExParser()
{
    //dtor
}
void RegExParser::parse()
{
    string *line  = new string();
    int priority_by_line_num=0;

    while(getNextLine(line))
    {

        string temp = "";
        int length = (*line).size();
        if(length==0)
            continue;
        stack<Expression *>* operators=new stack<Expression *>();
        vector<Expression *>* output=new vector<Expression *>();
        bool separated=false;
        bool keyword=false;
        bool break_out=false;
        bool punctuation=false;
        bool reg_def=0;
        bool reg_exp=0;
        string temp_lhs_name="";
        for(int i = 0; i < length; i++)
        {
            int type=getCharType((*line)[i]);
            switch(type)
            {
            case SYMBOL:
                temp=temp+(*line)[i];
                break;
            case ALPHA:
                temp=temp+(*line)[i];
                break;
            case REG_DEF_SEPARATOR:
            {

                separated=true;
                reg_def=1;
                RegDef * def=new RegDef();
                def->name=temp;
                temp_lhs_name=temp;
                regular_defintions->push_back(def);
                line=prepareIfConcatenation(*line,0);
                i=-1;
                length=(*line).size();
                temp="";
            }
            break;

            case REG_EXP_SEPARATOR:
            {
                priority_by_line_num++;
                separated=true;
                reg_exp=1;
                RegEx * exp=new RegEx();
                exp->name=temp;
                exp->priority=priority_by_line_num;
                temp_lhs_name=temp;
                regular_expressions->push_back(exp);
                line=prepareIfConcatenation(*line,1);
                i=-1;
                length=(*line).size();
                temp="";
            }
            break;
            case SPACE:
                if(!separated)
                {
                    if(temp.size()>0 && keyword) //case read keyword
                    {
                        RegEx *keyword=new RegEx();
                        keyword->transitions=NFA::get_string(temp);
                        TokenClass* cl=new TokenClass(temp,RegEx::KEYWORD_PRIORITY);
                        keyword->transitions->get_accepting_state()->set_token_class(cl);
                        keyword->priority=RegEx::KEYWORD_PRIORITY;
                        regular_expressions->push_back(keyword);
                        temp="";
                    }
                    else if(temp.size() > 0 && punctuation) //case read punctuation mark
                    {
                        RegEx *punc=new RegEx();
                        punc->transitions=new NFA(temp.at(0));
                        TokenClass* cl=new TokenClass(temp,0);//priority of punctuations ?
                        punc->transitions->get_accepting_state()->set_token_class(cl);
                        punc->priority=0;
                        regular_expressions->push_back(punc);
                        temp="";
                    }
                }
                else
                {
                    if(temp.size()>0)
                    {
                        //like in postfix we put operands in an output vector
                        Expression * exp=new Expression(temp);
                        output->push_back(exp);
                        temp="";
                    }
                }
                break;
            case OPERATOR:
                if(separated)
                {
                    if(temp.size()>0)
                    {
                        Expression * exp=new Expression(temp);
                        output->push_back(exp);
                        temp="";
                    }

                    while(!(operators->empty()) )
                    {
                        Expression *exp=operators->top();
                        if(getOperatorPrecedence((*line)[i]) > getOperatorPrecedence(exp->operator_))
                        {
                            break;
                        }
                        else
                        {
                            operators->pop();
                            output->push_back(exp);
                        }
                    }
                    Expression * exp=new Expression((*line)[i]);
                    operators->push(exp);

                }
                break;
            case RIGHT_PARENTHESE:
                if(separated)
                {
                    if(temp.size()>0)
                    {
                        Expression * exp=new Expression(temp);
                        output->push_back(exp);
                        temp="";
                    }

                    Expression *exp=operators->top();
                    operators->pop();
                    while(exp->operator_!='(')
                    {
                        output->push_back(exp);
                        exp=operators->top();
                        operators->pop();
                    }
                }

                break;
            case LEFT_PARENTHESE:
                if(separated) //parenthese in reg_def or reg_ex
                {
                    if(temp.size()>0)
                    {
                        Expression * exp=new Expression(temp);
                        output->push_back(exp);
                        temp="";
                    }
                    Expression * exp=new Expression('(');
                    operators->push(exp);
                }
                break;

            case ESCAPE:
                if((*line)[i+1]=='L' && separated)
                {
                    Expression * exp=new Expression("epsilon");
                    output->push_back(exp);
                }
                else
                {
                    temp=temp+(*line)[i+1];
                }
                i=i+1;
                break;
            case LEFT_CURLY://keywords or left curly as punctuation
                if(!punctuation)
                    keyword=true;
                else
                    temp=temp+(*line)[i];
                break;
            case RIGHT_CURLY:
                if(keyword)
                    break_out=true;
                else
                    temp=temp+(*line)[i];
                break;
            case RIGHT_PARENTHESE_INDEX:
                if(punctuation)
                    break_out=true;
                break;
            case LEFT_PARENTHESE_INDEX:
                punctuation=true;
                break;
            }
            if(break_out)
                break;
        }
        if(punctuation && temp.size()>0)
        {
            RegEx *punc=new RegEx();
            punc->transitions=new NFA(temp.at(0));
            TokenClass* cl=new TokenClass(temp,0);//priority of punctuations ?
            punc->transitions->get_accepting_state()->set_token_class(cl);
            punc->priority=0;
            regular_expressions->push_back(punc);
            temp="";

        }
        else if(keyword && temp.size() >0)
        {
            RegEx *keyword=new RegEx();
            keyword->transitions=NFA::get_string(temp);
            TokenClass* cl=new TokenClass(temp,RegEx::KEYWORD_PRIORITY);
            keyword->transitions->get_accepting_state()->set_token_class(cl);
            keyword->priority=RegEx::KEYWORD_PRIORITY;
            regular_expressions->push_back(keyword);
            temp="";

        }
        else if(reg_def || reg_exp) //pop operators stacks to evaluate
        {
            if(temp.size()>0)
            {
                Expression *exp=new Expression(temp);
                output->push_back(exp);
            }
            while(!operators->empty())
            {
                Expression *exp=operators->top();
                operators->pop();
                output->push_back(exp);
            }
            //debug purpose
            /*
            for(int i=0; i<output->size(); i++)
            {
                Expression * exp=output->at(i);
                if(exp->type == Expression::OPERAND)
                {
                    cout <<  "operand :" << exp->operand.c_str()<<endl;
                }

                else
                {
                    cout <<  "operator :";
                    cout << string(1,exp->operator_ )<<endl;
                }
            }
            cout<<"--------------------------------------------"<<endl;
            */
            evaluateExpression(temp_lhs_name,output,reg_def==0?1:0);
        }

    }

}
bool RegExParser::openInputFile(string filePath)
{
    inputFile = new ifstream(&filePath[0], ios::in);
    return inputFile->is_open();
}
bool RegExParser::getNextLine(string *line)
{

    if(endOfFile)
        return false;
    //read a line
    std::getline(*inputFile, *line);
    if(inputFile->eof())  //end of file is reached
    {
        endOfFile = true;
        return false;
    }
    return true;
}
int RegExParser::getCharType(char in)
{
    if(((int )in >=65 && (int )in <=90) || ((int )in >=97 && (int )in <=122))
        return ALPHA;
    else if(in==':')
        return REG_EXP_SEPARATOR;
    else if(in=='=')
        return REG_DEF_SEPARATOR;
    else if(in=='\\')
        return ESCAPE;
    else if(in=='(')
        return LEFT_PARENTHESE;
    else if(in==')')
        return RIGHT_PARENTHESE;
    else if(in=='[')
        return LEFT_PARENTHESE_INDEX;
    else if(in==']')
        return RIGHT_PARENTHESE_INDEX;
    else if(in=='{')
        return LEFT_CURLY;
    else if(in=='}')
        return RIGHT_CURLY;
    else if(in=='+' || in=='*' || in=='|' || in=='-'|| in==CONCAT_OP)
        return OPERATOR;
    else  if(in==' ')
        return SPACE;

    return SYMBOL;
}
int RegExParser::getOperatorPrecedence(char operator_)
{
    if(operator_=='|' )
        return OR_PRIORITY;
    else if(operator_=='-')
        return RANGE_PRIORITY;
    else if(operator_=='+' || operator_=='*')
        return CLOSURE_PRIORITY;
    else if(operator_==CONCAT_OP)
        return CONCAT_PRIORITY;
    else if (operator_=='(')
        return LEFT_PARENTHESE_PRIORITY;

}
//this function inserts an operator as concatenation in empty spaces and before/after the left/right
//parentheses
string* RegExParser::prepareIfConcatenation(string line,bool exp_def)
{


    int begin;
    if(exp_def) //regex
    {
        begin=line.find_first_of(":");
    }
    else //regdef
    {
        begin=line.find_first_of("=");
    }
    begin++;
    string temp=line.substr(begin);
    string::iterator end_pos = remove(temp.begin(), temp.end(), ' ');
    temp.erase(end_pos, temp.end());
    string * new_line=new string(addSpaces(temp));
    for(int i=0; i<(*new_line).size(); i++)
    {
        if((*new_line)[i]==' ' && (i>0 && (*new_line)[i-1]!='|' && (*new_line)[i-1]!='(')
                && (i+1<(*new_line).size() && (*new_line)[i+1]!='|' && (*new_line)[i+1]!=')'))
        {
            (*new_line)[i]=CONCAT_OP;
        }
        else if((*new_line)[i]=='('&& (i>0 && (*new_line)[i-1]!='|'&& (*new_line)[i-1]!=CONCAT_OP))
        {
            new_line=new string((*new_line).substr(0,i)+string(1,CONCAT_OP)+(*new_line).substr(i));
        }
        else if((*new_line)[i]==')' && i+1<(*new_line).size()
                &&  ((*new_line)[i+1]=='*' || (*new_line)[i+1]=='+'))
        {
            if(i+2<(*new_line).size() &&  (*new_line)[i+2]!=' ' && (*new_line)[i+2]!='|')
                new_line=new string((*new_line).substr(0,i+2)+string(1,CONCAT_OP)+(*new_line).substr(i+2));
        }
        else if((*new_line)[i]==')' && i+1 <(*new_line).size() && (*new_line)[i+1]!=' ' && (*new_line)[i+1]!='|')
        {
            new_line=new string((*new_line).substr(0,i+1)+string(1,CONCAT_OP)+(*new_line).substr(i+1));
        }
    }
    //cout<<(*new_line)<<endl;
    return new_line;
}
//if(0 it is in regular definition 1 in regex)
void RegExParser::evaluateExpression(string temp_lhs_name,vector<Expression *> * output,bool exp_def)
{
    RegEx *exp;
    RegDef *def;
    stack<NFA *> *value=new stack<NFA *>();
    for(int i=0; i<output->size(); i++)
    {
        Expression * exp=output->at(i);
        if(exp->type==Expression::OPERAND)
        {
            NFA* a=getNFA(exp->operand);
            value->push(a);
        }
        else
        {
            NFA * a;
            NFA * b;
            if(exp->operator_=='+' || exp->operator_=='*') //pop one element
            {
                a=value->top();
                value->pop();
            }
            else
            {
                a=value->top();
                value->pop();
                b=value->top();
                value->pop();
            }
            value->push(evaluate(a,b,exp->operator_));
        }
    }

    if(exp_def)
    {
        for(int i=0; i<regular_expressions->size(); i++)
        {
            exp=regular_expressions->at(i);
            if(strcmp(exp->name.c_str(),temp_lhs_name.c_str())==0)
                break;
        }
        exp->transitions=value->top();
        TokenClass * tok=new TokenClass(temp_lhs_name,exp->priority);
        exp->transitions->get_accepting_state()->set_token_class(tok);
    }
    else
    {
        for(int i=0; i<regular_defintions->size(); i++)
        {
            def=regular_defintions->at(i);
            if(strcmp(def->name.c_str(),temp_lhs_name.c_str())==0)
                break;
        }
        def->transitions=value->top();
        TokenClass * tok=new TokenClass(temp_lhs_name,0);
        def->transitions->get_accepting_state()->set_token_class(tok);
    }
}
NFA* RegExParser::getNFA(string name)
{

    RegDef * def;
    for(int i=0; i<regular_defintions->size(); i++)
    {
        def=regular_defintions->at(i);
        if(strcmp(def->name.c_str(),name.c_str())==0)
        {
            return def->transitions;//case where regex/regdef is defined as function of another regdef
        }
    }
    if(name.size()==1)
    {
        return NFA::get_char(name.at(0));//case one char
    }

    else if(strcmp(name.c_str(),"epsilon")==0)
    {
        return new NFA();//epsilon state

    }
    else if(name.size()>1)
    {
        return NFA ::get_string(name);//case string
    }

}
NFA* RegExParser::evaluate(NFA *a,NFA *b,char operator_)
{
    if(operator_=='+')
        return a->clone()->positive_closure();
    else if(operator_=='*')
        return a->clone()->kleene_closure();
    else if(operator_=='|')
        return a->clone()->oring(b);
    else if(operator_==CONCAT_OP)
        return b->clone()->concatenation(a);
    else if(operator_=='-')
        return NFA::get_range(b->get_accepting_state()->get_token_class()->name.at(0),
                              a->get_accepting_state()->get_token_class()->name.at(0));

}

NFA * RegExParser::constructNFA()
{
    vector <NFA *> *nfas=new vector<NFA *>();
    for(int i=0; i<regular_expressions->size(); i++)
    {
        RegEx * reg=regular_expressions->at(i);
        nfas->push_back(reg->transitions);
    }
    return NFA::join_NFAs(nfas);

}


string  RegExParser::addSpaces(string line)
{
    string temp=line;
    sortRegDef();
    for(int i=0; i<regular_defintions->size(); i++)
    {
        string Result;
        ostringstream convert;
        convert << i;
        Result = convert.str();
        RegDef* def=regular_defintions->at(i);
        int found=temp.find(def->name);
        while(found!=std::string::npos)
        {

            if(found+def->name.size() <temp.size() &&
                    (temp[found+def->name.size()]=='*' || temp[found+def->name.size()]=='+' ))
            {
                temp=temp.substr(0,found)+" "+string(1,TEMP_OP)+Result+string(1,TEMP_OP)+temp.substr(found+def->name.size(),1)+" "+temp.substr(found+def->name.size()+1);
            }
            else
            {
                temp=temp.substr(0,found)+" "+string(1,TEMP_OP)+Result+string(1,TEMP_OP)+" "+temp.substr(found+def->name.size());
            }

            found=temp.find(def->name,found+def->name.size());
        }
    }
    for(int i=0; i<temp.size(); i++)
    {
        if(temp[i]==TEMP_OP)
        {
            string index="";
            int k=i+1;
            while(temp[k]!=TEMP_OP)
            {
                index=index+temp[k];
                k++;
            }
            int value = atoi(index.c_str());
            RegDef *def=regular_defintions->at(value);
            temp=temp.substr(0,i)+def->name+temp.substr(k+1);
        }

    }
    //cout<<temp<<endl;
    return temp;

}
//sorts regdef by descending order of the length of their names
void RegExParser::sortRegDef()
{
    for(int i=1; i<regular_defintions->size(); i++)
    {
        for(int j=0; j<regular_defintions->size()-i; j++)
        {
            RegDef *first=regular_defintions->at(j);
            RegDef *second=regular_defintions->at(j+1);
            if(first->name.size()<second->name.size())
            {
                iter_swap(regular_defintions->begin()+j,regular_defintions->begin()+j+1);
            }
        }
    }
}



