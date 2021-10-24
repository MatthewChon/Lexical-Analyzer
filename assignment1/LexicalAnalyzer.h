#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>
#include <queue>

#include "Token.h"
#include "TokenCodes.h"

class LexicalAnalyzer
{
  private:
    ifstream *sourceCodeFile;
    int current_character_position;
    int capacity;
    queue<char> line;
    char* lexeme;

    TokenCodes tokencode(char);
    TokenCodes lookup(char*);
    TokenCodes furtherlookup(char*);

    char* lower(char*);
    char nextcharacter();
    void nextline();
    void parse();
    void nextnonwhitespace();


  public:
    LexicalAnalyzer(ifstream*);
    int getCurrentCharPositionNumber();
    Token* getNextToken();
};

#endif