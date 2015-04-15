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
            cout<<"enter regular expresions file : ";
            cin>>regxFile;
            //regxFile="regex.txt";

            //create  LexicalAnalyzer which will anaulize a source file according to the
            //given rules in regxFile.
            LexicalAnalyzer* analyzer  = generator->createLexicalAnalyzer(regxFile);
                        //set the source code for the LexicalAnalyze

            string source_file;

            cout<<"enter source code  file : ";
            cin>>source_file;
            //source_file="test.java";

            string out_file;
            cout<<"enter output file : ";
            cin>>out_file;
            //out_file="expected_output.txt";
            analyzer->setSourceCodeFile(source_file);

            string CFG_rules;
            cout<<"enter grammar rules file : ";
            cin>>CFG_rules;

            SyntaxAnalyzerGenerator * syntax_generator=new SyntaxAnalyzerGenerator();
            SyntaxAnalyzer * syntax_analyzer=syntax_generator->createSyntaxAnalyzer(analyzer,CFG_rules);

            cout<<"regular expresions file : "<<regxFile<<endl;
            cout<<"source file : "<<source_file<<endl;
            cout<<"grammar file : "<<CFG_rules<<endl;
            cout<<"output file : "<<out_file<<endl;
            cout<<"start syntax analysis, ";
            //return sequence of productions as strings


 }
Phase2::~Phase2()
{
    //dtor

}
