#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return the token of the character under examination
Token *nextToken(Lexer *l) {
  Token *tok = NULL;
  skipWhiteSpace(l);

  switch (l->ch) {
  case '=':
    if (peekChar(l) == '=') {
      unsigned int ch = l->ch;
      readChar(l);
      tok = (Token *)malloc(sizeof(Token));
      tok->literal =
          (char *)malloc(3 * sizeof(char)); // two chars and a null character
      tok->literal[0] = ch;
      tok->literal[1] = l->ch;
      tok->literal[2] = '\0';
      tok->type = EQ;
    } else {
      tok = newToken(ASSIGN, l->ch);
    }
    break;
  case ';':
    tok = newToken(SEMICOLON, l->ch);
    break;
  case '(':
    tok = newToken(LPAREN, l->ch);
    break;
  case ')':
    tok = newToken(RPAREN, l->ch);
    break;
  case ',':
    tok = newToken(COMMA, l->ch);
    break;
  case '+':
    tok = newToken(PLUS, l->ch);
    break;
  case '{':
    tok = newToken(LBRACE, l->ch);
    break;
  case '}':
    tok = newToken(RBRACE, l->ch);
    break;
  case '-':
    tok = newToken(MINUS, l->ch);
    break;
  case '!':
    if (peekChar(l) == '=') {
      unsigned int ch = l->ch;
      tok = (Token *)malloc(sizeof(Token));
      tok->literal =
          (char *)malloc(3 * sizeof(char)); // two chars and a null character
      tok->literal[0] = ch;
      tok->literal[1] = l->ch;
      tok->literal[2] = '\0';
      tok->type = NOT_EQ;
    } else {
      tok = newToken(BANG, l->ch);
    }
    break;
  case '/':
    tok = newToken(SLASH, l->ch);
    break;
  case '*':
    tok = newToken(ASTERISK, l->ch);
    break;
  case '<':
    tok = newToken(LT, l->ch);
    break;
  case '>':
    tok = newToken(GT, l->ch);
    break;
  case '\0':
    tok = (Token *)malloc(sizeof(Token));
    tok->literal = (char *)malloc(1);
    tok->literal[0] = '\0';
    tok->type = EOF_TOKEN;
    break;
  default:
    // whenever one of the character isn't recognized, read for identifiers
    if (isLetter(l->ch)) {
      tok = (Token *)malloc(sizeof(Token));
      tok->literal = readIdentifier(l);
      tok->type = lookupIdentifier(tok->literal);
      return tok;
    } else if (isDigit(l->ch)) {
      tok = (Token *)malloc(sizeof(Token));
      tok->literal = readNumber(l);
      tok->type = INT;
    } else {
      tok = newToken(ILLEGAL, l->ch);
    }
  }

  // advance the pointer into the input, so next nextToken call, the next char
  // is read
  readChar(l);
  return tok;
}

Token *newToken(TokenType token, unsigned int ch) {
  Token *tok = (Token *)malloc(sizeof(Token));

  tok->literal =
      (char *)malloc(2); // allocating an extra byte for the null character
  tok->literal[0] = (char)ch;
  tok->literal[1] = '\0';
  tok->type = token;

  return tok;
}

char *readIdentifier(Lexer *l) {
  // starting position of the identifier
  int position = l->position;
  // keep reading the characters as long the current character is a letter
  while (isLetter(l->ch)) {
    readChar(l);
  }

  // one position past the end of the word - beginning of word position position
  int lengthOfIdentifier = l->position - position;

  char *identifier = (char *)malloc(
      lengthOfIdentifier +
      1); // allocating space for the extra null character for the string

  if (!identifier) {
    printf("memory allocation failed for identifier\n");
  }

  // strncpy copies a portion (lengthOfIdentifier) of a string starting from a
  // specific position (&l->input[position]) to the assigned buffer (identifier)
  strncpy(identifier, &l->input[position], lengthOfIdentifier);

  // because this is a new string (char*), there is not a null character at the
  // end yet
  identifier[lengthOfIdentifier] = '\0';

  return identifier;
}

char *readNumber(Lexer *l) {
  int position = l->position;

  while (isDigit(l->ch)) {
    readChar(l);
  }

  int lengthOfNumber = l->position - position;

  char *number = (char *)malloc(sizeof(lengthOfNumber) + 1);

  if (!number) {
    printf("memory allocation failed for number\n");
  }

  strncpy(number, &l->input[position], lengthOfNumber);

  number[lengthOfNumber] = '\0';

  return number;
}

bool isLetter(unsigned int ch) {
  return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

// LaithScript only supports integers...
bool isDigit(unsigned int ch) { return '0' <= ch && ch <= '9'; }

TokenType lookupIdentifier(char *identifier) {
  if (strcmp(identifier, "fn") == 0) {
    return FUNCTION;
  } else if (strcmp(identifier, "let") == 0) {
    return LET;
  } else if (strcmp(identifier, "true") == 0) {
    return TRUE;
  } else if (strcmp(identifier, "false") == 0) {
    return FALSE;
  } else if (strcmp(identifier, "if") == 0) {
    return IF;
  } else if (strcmp(identifier, "else") == 0) {
    return ELSE;
  } else if (strcmp(identifier, "return") == 0) {
    return RETURN;
  } else {
    return IDENT;
  }
}

void skipWhiteSpace(Lexer *l) {
  while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
    readChar(l);
  }
}

unsigned int peekChar(Lexer *l) {
  if (l->readPosition >= strlen(l->input)) {
    return '\0';
  } else {
    return l->input[l->readPosition];
  }
}

void printToken(Token *tok) {
  const char *typeString;

  switch (tok->type) {
  case ILLEGAL:
    typeString = "ILLEGAL";
    break;
  case EOF_TOKEN:
    typeString = "EOF";
    break;

  // Identifiers + Literals
  case IDENT:
    typeString = "IDENT";
    break;
  case INT:
    typeString = "INT";
    break;

  // Operators
  case ASSIGN:
    typeString = "ASSIGN";
    break;
  case PLUS:
    typeString = "PLUS";
    break;
  case MINUS:
    typeString = "MINUS";
    break;
  case BANG:
    typeString = "BANG";
    break;
  case ASTERISK:
    typeString = "ASTERISK";
    break;
  case SLASH:
    typeString = "SLASH";
    break;
  case EQ:
    typeString = "EQ";
    break;
  case NOT_EQ:
    typeString = "NOT_EQ";
    break;

  // Comparisons
  case LT:
    typeString = "LT";
    break;
  case GT:
    typeString = "GT";
    break;

  // Delimiters
  case COMMA:
    typeString = "COMMA";
    break;
  case SEMICOLON:
    typeString = "SEMICOLON";
    break;
  case LPAREN:
    typeString = "LPAREN";
    break;
  case RPAREN:
    typeString = "RPAREN";
    break;
  case LBRACE:
    typeString = "LBRACE";
    break;
  case RBRACE:
    typeString = "RBRACE";
    break;

  // Keywords
  case FUNCTION:
    typeString = "FUNCTION";
    break;
  case LET:
    typeString = "LET";
    break;
  case TRUE:
    typeString = "TRUE";
    break;
  case FALSE:
    typeString = "FALSE";
    break;
  case IF:
    typeString = "IF";
    break;
  case ELSE:
    typeString = "ELSE";
    break;
  case RETURN:
    typeString = "RETURN";
    break;

  default:
    typeString = "UNKNOWN";
    break;
  }

  printf("Token Type: %s, Literal: %s\n", typeString, tok->literal);
}
