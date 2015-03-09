#include "RegExParser.h"

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
    string *line  = new string();
    while(getNextLine(line))
    {

    }


}

RegExParser::~RegExParser()
{
    //dtor
}
bool RegExParser::openInputFile(string filePath) {
	inputFile = new ifstream(&filePath[0], ios::in);
	return inputFile->is_open();
}
bool RegExParser::getNextLine(string *line) {

    if(endOfFile)
        return false;
	//read a line
	std::getline(*inputFile, *line);
	if(inputFile->eof()) {//end of file is reached
        endOfFile = true;
		return false;
    }
	return true;
}

