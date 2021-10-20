#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

class LexicalAnalyzer
{
  private:
    ifstream *sourceCodeFile;


  public:
    LexicalAnalyzer(ifstream*);
    int getCurrentCharPositionNumber();
    Token* getNextToken();
};

#endif