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

            cout<<"regular expresions file : "<<regxFile<<endl;
            cout<<"source file : "<<source_file<<endl;
            cout<<"output file : "<<out_file<<endl;

            cout<<"start lexical analysis, ";
            //get tokens from the  LexicalAnalyzer
             FILE * pFile = fopen (out_file.c_str(),"w+");


            vector<string> identifiers;
            string ident="id";
            Token* t = analyzer->getTokenNextToken();
            while(t != NULL) {
                fprintf(pFile,"%s\n",t->tokenClass->name.c_str());
                if((ident.compare(t->tokenClass->name) == 0)  &&
                   (std::find(identifiers.begin(),identifiers.end(),t->attribute_value)==identifiers.end())) {
                    identifiers.push_back(t->attribute_value);
                }
                t = analyzer->getTokenNextToken();
            }

            FILE * symbolTable=fopen("SymboleTable.txt","w+");
            for(int i=0;i<identifiers.size();i++){
                fprintf(symbolTable,"%s\n",identifiers.at(i).c_str());
            }


            cout<<"done !"<<endl;


            cout<<"===============================================\n\n\n\n\n";

 }


Phase1::~Phase1()
{
    //dtor
}










