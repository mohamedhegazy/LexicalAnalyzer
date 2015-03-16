#include "Phase1.h"
#include "LexicalAnalyzerGenerator.h"
#include <iostream>
#include <stdio.h>

using namespace std;
Phase1::Phase1()
{

}

 void Phase1::start_phase1() {
            cout<<"\n\n===============================================\n";

            // create  LexicalAnalyzerGenerator which will take reuglar expresions file
            // and create the  LexicalAnalyzer itself.
            LexicalAnalyzerGenerator*generator = new LexicalAnalyzerGenerator();

            string regxFile;
            cout<<"enter regular expresions file : ";
            cin>>regxFile;

            //create  LexicalAnalyzer which will anaulize a source file according to the
            //given rules in regxFile.
            LexicalAnalyzer* analyzer  = generator->createLexicalAnalyzer(regxFile);

            //set the source code for the LexicalAnalyze

            string source_file;
            cout<<"enter source code  file : ";
            cin>>source_file;

            string out_file;
            cout<<"enter output file : ";
            cin>>out_file;

            analyzer->setSourceCodeFile(source_file);

            cout<<"regular expresions file : "<<regxFile<<endl;
            cout<<"source file : "<<source_file<<endl;
            cout<<"output file : "<<out_file<<endl;

            cout<<"start lexical analysis, ";
            //get tokens from the  LexicalAnalyzer
             FILE * pFile = fopen (out_file.c_str(),"w+");



            Token* t = analyzer->getTokenNextToken();
            while(t != NULL) {
                fprintf(pFile,"%s\n",t->tokenClass->name.c_str());
                t = analyzer->getTokenNextToken();
            }

            cout<<"done !"<<endl;


            cout<<"===============================================\n\n\n\n\n";

 }


Phase1::~Phase1()
{
    //dtor
}










