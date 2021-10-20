#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
  sourceCodeFile = scf;


}

int LexicalAnalyzer::getCurrentCharPositionNumber()
{

}

Token* LexicalAnalyzer::getNextToken()
{
  Token *t;



  return t;
}
