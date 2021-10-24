#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
  sourceCodeFile = scf;

  lexeme = new char[10];
  lexeme_size = 0;

  loadnextline();
}

int LexicalAnalyzer::getCurrentCharPositionNumber()
{
  return current_character_position;
}

Token* LexicalAnalyzer::getNextToken()
{
  Token *t;
  t = new Token();
  lexeme_size = 0;

  TokenCodes code = parse();

  switch(code) {
    case IDENT:
      t->setLexemeNumber(getCurrentCharPositionNumber());
      while(code == IDENT || code == NUMLIT) {
        code = parse();
      }
      t->setLexemeString(lexeme);
      t->setTokenCode(IDENT);
      break;
    case NUMLIT:
      t->setLexemeNumber(getCurrentCharPositionNumber());
      while (code == NUMLIT) {
        code = parse();
      }
      t->setLexemeString(lexeme);
      t->setTokenCode(NUMLIT);
      break;
    case NEWLINE:
      t->setLexemeNumber(getCurrentCharPositionNumber());
      t->setLexemeString("\\n");
      t->setTokenCode(NEWLINE);
      loadnextline();
      break;
    case EOI:
      t->setLexemeNumber(getCurrentCharPositionNumber());
      t->setLexemeString("EOI");
      t->setTokenCode(EOI);
      break;
  }
  return t;
}
TokenCodes LexicalAnalyzer::parse() {
  if (getCurrentCharPositionNumber() < line.length()) {
    char symbol = line.at(current_character_position++);
    if (lexeme_size < 10) {
      lexeme[lexeme_size] = symbol;
      lexeme[++lexeme_size] = 0;
    }
    if (isalpha(symbol)) {
      return IDENT;
    }
    else if (isdigit(symbol)){
      return NUMLIT;
    }
    else {
    }
  }
  else {
    if (sourceCodeFile->eof()) {
      return EOI;
    }
    else {
      return NEWLINE;
    }
  }
}
void LexicalAnalyzer::nextnonwhitespace() {
  char symbol = line.at(getCurrentCharPositionNumber());
  while(isspace(symbol)) {
    current_character_position++;
  }
}
void LexicalAnalyzer::loadnextline() {
  current_character_position = 0;
  getline(*sourceCodeFile, line);
}