#include "Phase2.h"
#include "SyntaxAnalyzerGenerator.h"
#include "LexicalAnalyzerGenerator.h"

#include <iostream>
#include <stdio.h>

using namespace std;

Phase2::Phase2()
{
    //ctor
}
void Phase2::start_phase2() {



            cout<<"\n\n===============================================\n";

            // create  LexicalAnalyzerGenerator which will take reuglar expresions file
            // and create the  LexicalAnalyzer itself.
            LexicalAnalyzerGenerator* generator = new LexicalAnalyzerGenerator();

            string regxFile;
            //cout<<"enter regular expresions file : ";
            regxFile = "regex.txt";
            //regxFile="regex.txt";

            //create  LexicalAnalyzer which will anaulize a source file according to the
            //given rules in regxFile.
            LexicalAnalyzer* analyzer  = generator->createLexicalAnalyzer(regxFile);
                        //set the source code for the LexicalAnalyze

            string source_file;

            //cout<<"enter source code  file : ";
            source_file = "test.java";
            //source_file="test.java";

            string out_file;
           // cout<<"enter output file : ";
            out_file = "result.txt";
            //out_file="expected_output.txt";
            analyzer->setSourceCodeFile(source_file);

            string CFG_rules;
            //cout<<"enter grammar rules file : ";
            CFG_rules = "GRAMMAR_RULES.txt";

            SyntaxAnalyzerGenerator * syntax_generator=new SyntaxAnalyzerGenerator();
            SyntaxAnalyzer * syntax_analyzer=syntax_generator->createSyntaxAnalyzer(analyzer,CFG_rules);
            cout<<"regular expresions file : "<<regxFile<<endl;
            cout<<"source file : "<<source_file<<endl;
            cout<<"grammar file : "<<CFG_rules<<endl;
            cout<<"output file : "<<out_file<<endl;
            cout<<"start syntax analysis, "<<endl;
            //return sequence of productions as strings


            syntax_analyzer->table->print_to_file("parsing_table.txt");





            syntax_analyzer->start_parsing();
            syntax_analyzer->table->print_symbols_to_file("symbols_first_follow.txt");
            vector<string> * ans = syntax_analyzer->get_parsing_result_string();
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout<<"parsing status : "<<syntax_analyzer->get_successful_parsing()<<endl;
            for(int i = 0; i < ans->size(); i++) {
                cout<<ans->at(i)<<endl;
            }


 }


Phase2::~Phase2()
{
    //dtor

}
