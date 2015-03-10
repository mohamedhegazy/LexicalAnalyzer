#include "RegExParser.h"
#include <stack>          // std::stack
const int RIGHT_PARENTHESE_PRIORITY=-1;
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
const int PUNCTUATION=13;
const int ORING_RANGE_PRIORITY=14;
const int CONCAT_PRIORITY=15;
const int CLOSURE_PRIORITY=16;
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
        priority_by_line_num++;
        string temp = "";
        int length = (*line).size();
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
                i=0;
                length=(*line).size();
            }
            break;

            case REG_EXP_SEPARATOR:
            {
                separated=true;
                reg_exp=1;
                RegEx * exp=new RegEx();
                exp->name=temp;
                exp->priority=priority_by_line_num;
                temp_lhs_name=temp;
                regular_expressions->push_back(exp);
                line=prepareIfConcatenation(*line,1);
                i=0;
                length=(*line).size();

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
                        RegEx *keyword=new RegEx();
                        keyword->transitions=new NFA(temp.at(0));
                        TokenClass* cl=new TokenClass(temp,0);//priority of punctuations ?
                        keyword->transitions->get_accepting_state()->set_token_class(cl);
                        keyword->priority=0;
                        regular_expressions->push_back(keyword);
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
                    Expression * exp=new Expression('(');
                    operators->push(exp);
                }
                break;

            case ESCAPE:
                if((*line)[i+1]=='L')
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
            else if(reg_def || reg_exp) //pop operators stacks to evaluate
            {
                while(!operators->empty())
                {
                    Expression *exp=operators->top();
                    operators->pop();
                    output->push_back(exp);
                }
                evaluateExpression(temp_lhs_name,output,reg_def==0?0:1);
            }
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
        return REG_DEF_SEPARATOR;
    else if(in=='=')
        return REG_EXP_SEPARATOR;
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
    else if(in=='+' || in=='*' || in=='|' || in=='-'|| in=='~')
        return OPERATOR;
    else  if(in==' ')
        return SPACE;
    else if(in==';' || in==',' || in=='(' || in == ')' || in=='{' || in =='}')
        return PUNCTUATION;

    return 0;
}
int RegExParser::getOperatorPrecedence(char operator_)
{
    if(operator_=='|' || operator_=='-')
        return ORING_RANGE_PRIORITY;

    else if(operator_=='+' || operator_=='*')
        return CLOSURE_PRIORITY;
    else if(operator_=='~')
        return CONCAT_PRIORITY;
    else if (operator_=='(')
        return RIGHT_PARENTHESE_PRIORITY;

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
    while(line.at(begin)==' ')
        begin++;
    string* temp=new string(line.substr(begin));
    for(int i=0; (*temp).size(); i++)
    {
        if((*temp)[i]==' ')
        {
            (*temp)[i]='~';
        }
        else if((*temp)[i]=='(' && i>0 && (*temp)[i-1]!='~' )
        {
            temp=new string((*temp).substr(0,i)+"~"+(*temp).substr(i));
        }
        else if( (*temp)[i]==')' && i+1<(*temp).size() && (*temp)[i+1]!='+' && (*temp)[i+1]!='*')
        {
            temp=new string((*temp).substr(0,i+1)+"~"+(*temp).substr(i+1));
        }
        else if( (*temp)[i]==')' && i+2<(*temp).size() && (*temp)[i+2]!='+' && (*temp)[i+2]!='*')
        {
            temp=new string((*temp).substr(0,i+2)+"~"+(*temp).substr(i+2));
        }

    }
    for(int i=0; (*temp).size(); i++)//eliminate ~ around the OR(ranged or normal)
    {
        if((*temp)[i]=='|' || ((*temp)[i]=='-' && i>0 && (*temp)[i-1]!='\\' ))
        {
            int j=i-1;
            int k=j+1;
            while(j>0 && ((*temp)[j] =='~'||(*temp)[j] ==' '))
                temp[j--]=' ';
            while(k<(*temp).size() && ( (*temp)[k] =='~'||(*temp)[k] ==' ')  )
                temp[k++]=' ';
        }
        return temp;
    }
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
            return def->transitions;
        }
    }
    if(name.size()==1)
    {
        return NFA::get_char(name.at(0));
    }
    if(strcmp(name.c_str(),"epsilon"))
    {
        return new NFA();

    }
}
NFA* RegExParser::evaluate(NFA *a,NFA *b,char operator_)
{
    if(operator_=='+')
        return a->positive_closure();
    else if(operator_=='*')
        return a->kleene_closure();
    else if(operator_=='|')
        return a->oring(b);
    else if(operator_=='~')
        return a->concatenation(b);
    else if(operator_=='-')
        return NFA::get_range(a->get_accepting_state()->get_token_class()->name.at(0),
                              b->get_accepting_state()->get_token_class()->name.at(0));

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










