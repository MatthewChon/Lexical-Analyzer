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
      token_class = tokencode(nextcharacter());
      while(token_class == IDENT || token_class == NUMLIT) {
        parse();
        token_class = tokencode(nextcharacter());
      }
      t->setLexemeNumber(0);
      t->setLexemeString(lexeme);
      t->setTokenCode(lookup(lexeme));
      break;
    case NUMLIT:
      token_class = tokencode(nextcharacter());
      while(token_class == NUMLIT) {
        parse();
        token_class = tokencode(nextcharacter());
      }
      t->setLexemeNumber(atoi(lexeme));
      t->setLexemeString(lexeme);
      t->setTokenCode(NUMLIT);
      break;
    case NEWLINE:
      t->setLexemeNumber(0);
      t->setLexemeString("\\n");
      t->setTokenCode(NEWLINE);
      nextline();
      break;
    case EOI:
      t->setLexemeNumber(0);
      t->setLexemeString("EOI");
      t->setTokenCode(token_class);
      break;
    case NAL:
      token_class = tokencode(nextcharacter());
      while (token_class == NAL) {
        parse();
        token_class = tokencode(nextcharacter());
      }
      t->setLexemeNumber(0);
      t->setLexemeString(lexeme);
      t->setTokenCode(NAL);
      break;
    default:
      t->setLexemeNumber(0);
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
        case '\n':
          return NEWLINE;
        default:
          return NAL;
      }
    }
  }
  else {
    if (sourceCodeFile->eof()) {
      return EOI;
    }
    return NEWLINE;
  }
}
TokenCodes LexicalAnalyzer::lookup(char* token) {
  char* case_insensitive = lower(token);
  if (strcmp(case_insensitive, "begin") == 0)
    return BEGINSYM;
  else if (strcmp(case_insensitive, "boolean") == 0)
    return BOOLSYM;
  else if (strcmp(case_insensitive, "else") == 0)
    return ELSESYM;
  else if (strcmp(case_insensitive, "end") == 0)
    return ENDSYM;
  else if (strcmp(case_insensitive, "false") == 0)
    return FALSESYM;
  else if (strcmp(case_insensitive, "get") == 0)
    return GETSYM;
  else if (strcmp(case_insensitive, "if") == 0)
    return IFSYM;
  else if (strcmp(case_insensitive, "is") == 0)
    return ISSYM;
  else if (strcmp(case_insensitive, "integer") == 0)
    return INTSYM;
  else if (strcmp(case_insensitive, "loop") == 0)
    return LOOPSYM;
  else if (strcmp(case_insensitive, "newline") == 0)
    return NEWLINE;
  else if (strcmp(case_insensitive, "not") == 0)
    return NOTSYM;
  else if (strcmp(case_insensitive, "null") == 0)
    return NULLSYM;
  else if (strcmp(case_insensitive, "procedure") == 0)
    return PROCSYM;
  else if (strcmp(case_insensitive, "put") == 0)
    return PUTSYM;
  else if (strcmp(case_insensitive, "rem") == 0)
    return REMSYM;
  else if (strcmp(case_insensitive, "then") == 0)
    return THENSYM;
  else if (strcmp(case_insensitive, "true") == 0)
    return TRUESYM;
  else if (strcmp(case_insensitive, "while") == 0)
    return WHILESYM;
  else
    return furtherlookup(token);
  
}
TokenCodes LexicalAnalyzer::furtherlookup(char* token) {
  switch(token[0]) {
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
      if (nextcharacter() == '=') {
        parse();
        return NEQ;
      }
      return SLASH;
    case ':':
      if (nextcharacter() == '=') {
        parse();
        return BECOMES;
      }
      return COLON;
    case '<':
      if (nextcharacter() == '=') {
        parse();
        return LEQ;
      }
      return LSS;
    case '>':
      if (nextcharacter() == '=') {
        parse();
        return GEQ;
      }
      return GTR;
    default:
      return IDENT;
  }
}
char* LexicalAnalyzer::lower(char* token) {

  int size = sizeof(token)/sizeof(token[0]);
  char *lowercase = new char[size];
  
  for (int i = 0; i < size; ++i) {
    lowercase[i] = tolower(token[i]);
  }
  return lowercase;
}

char LexicalAnalyzer::nextcharacter() {
  return line.front();
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