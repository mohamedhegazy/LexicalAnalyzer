#include "LexicalAnalyzerGenerator.h"

LexicalAnalyzerGenerator::LexicalAnalyzerGenerator()
{
    //ctor
}

LexicalAnalyzerGenerator::~LexicalAnalyzerGenerator()
{
    //dtor
}
LexicalAnalyzer LexicalAnalyzerGenerator::createLexicalAnalyzer(string regex)
{
    //dtor
    RegExParser *parser=new RegExParser(regex);

}
