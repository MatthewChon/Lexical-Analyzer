#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCodes.h"

class LexicalAnalyzer
{
  private:
    ifstream *sourceCodeFile;

    /* implemented variables and functions */
    char* lexeme;
    int lexeme_size;
    int current_character_position;
    string line;

    /* TokenCodes function */
    TokenCodes parse();

    /* void function */
    void nextnonwhitespace();
    void loadnextline();

  public:
    LexicalAnalyzer(ifstream*);
    int getCurrentCharPositionNumber();
    Token* getNextToken();
};

#endif