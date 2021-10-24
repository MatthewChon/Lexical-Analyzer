#include <iostream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

LexicalAnalyzer::LexicalAnalyzer(ifstream *scf)
{
  sourceCodeFile = scf;

  lexeme = new char[10];

  nextline();
}

int LexicalAnalyzer::getCurrentCharPositionNumber()
{
  return current_character_position;
}

Token* LexicalAnalyzer::getNextToken()
{
  Token *t;
  capacity = 0;

  nextnonwhitespace();
  parse();

  t = new Token();

  TokenCodes token_class = tokencode(lexeme[0]);
  switch(token_class) {
    case IDENT:
      token_class = tokencode(line.front());
      while(token_class == IDENT ||
            token_class == NUMLIT) {
        parse();
        token_class = tokencode(line.front());
      }
      t->setLexemeNumber(getCurrentCharPositionNumber());
      t->setLexemeString(lexeme);
      t->setTokenCode(lookup(lexeme));
      break;
    case NUMLIT:
      token_class = tokencode(line.front());
      while(token_class == NUMLIT) {
        parse();
        token_class = tokencode(line.front());
      }
      t->setLexemeNumber(getCurrentCharPositionNumber());
      t->setLexemeString(lexeme);
      t->setTokenCode(NUMLIT);
      break;
    case NEWLINE:
      t->setLexemeNumber(getCurrentCharPositionNumber());
      t->setLexemeString("\\n");
      t->setTokenCode(NEWLINE);
      nextline();
      break;
    case EOI:
      t->setLexemeNumber(getCurrentCharPositionNumber());
      t->setLexemeString("EOI");
      t->setTokenCode(token_class);
      break;
    default:
      t->setLexemeNumber(getCurrentCharPositionNumber());
      token_class = lookup(lexeme);
      t->setLexemeString(lexeme);
      t->setTokenCode(token_class);
  }

  return t;
}
void LexicalAnalyzer::parse() {
  if (!line.empty()) {
    if (capacity < 10) {
      lexeme[capacity++] = line.front();
      lexeme[capacity] = 0;
      line.pop();
    }
    current_character_position++;
  }
}
TokenCodes LexicalAnalyzer::tokencode(char c) {
  if (!line.empty()) {
    if(isalpha(c)) {
      return IDENT;
    }
    else if (isdigit(c)) {
      return NUMLIT;
    }
    else {
      switch(c) {
        case '+':
          return PLUS;
        case '-':
          return MINUS;
        case '*':
          return TIMES;
        case '=':
          return EQL;
        case '(':
          return LPAREN;
        case ')':
          return RPAREN;
        case ',':
          return COMMA;
        case ';':
          return SEMICOLON;
        case '/':
          return SLASH;
        case ':':
          return COLON;
        case '<':
          return LSS;
        case '>':
          return GTR;
        default:
          return NAL;
      }
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
TokenCodes LexicalAnalyzer::lookup(char* token) {
  char* case_insensitive = lower(token);

  return IDENT;
}
char* LexicalAnalyzer::lower(char* token) {

  int size = sizeof(token)/sizeof(token[0]);
  char *lowercase = new char[size];
  
  for (int i = 0; i < size; ++i) {
    lowercase[i] = tolower(token[i]);
  }
  return lowercase;
}

void LexicalAnalyzer::nextnonwhitespace() {

  while (!line.empty() && isspace(line.front())) {
    line.pop();
    current_character_position++;
  }
}
void LexicalAnalyzer::nextline() {

  string new_statement;
  current_character_position = 0;

  getline(*sourceCodeFile, new_statement);

  for (int i = 0; i < new_statement.length(); ++i) {
    line.push(new_statement.at(i));
  }
  if (!sourceCodeFile->eof()) {
    line.push('\n');
  }
}