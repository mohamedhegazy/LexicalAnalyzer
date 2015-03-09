#include "Phase1.h"
#include "LexicalAnalyzerGenerator.h"
#include <iostream>
using namespace std;
Phase1::Phase1()
{

            LexicalAnalyzerGenerator  *generator = new LexicalAnalyzerGenerator();
            LexicalAnalyzer analyzer  = generator->createLexicalAnalyzer("regxFile.txt");
            analyzer.setSourceCodeFile("test.java");
            while(true) {
                Token t = analyzer.getTokenNextToken();
                cout << t.tokenClass.name << endl;
            }

}

Phase1::~Phase1()
{
    //dtor
}
