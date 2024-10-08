#ifndef TOKEN_C
#include "lexer.h"
#include <stdbool.h>

// define the different type of tokens are lexer will parse the source
// code to.
typedef enum {
  ILLEGAL,   // illegal character
  EOF_TOKEN, // EOF

  // identifiers + literals
  IDENT, // identifier (add, foobar, x, y, ...)
  INT,   // integer (12345)

  // operators
  ASSIGN,   // =
  PLUS,     // +
  MINUS,    // -
  BANG,     // !
  ASTERISK, // *
  SLASH,    // /
  EQ,       // ==
  NOT_EQ,   // !=

  LT, // <
  GT, // >

  // delimeters
  COMMA,     // ,
  SEMICOLON, // ;
  LPAREN,    // (
  RPAREN,    // )
  LBRACE,    // {
  RBRACE,    // }

  // keywords
  FUNCTION, // fn
  LET,      // let
  TRUE,     // true
  FALSE,    // false
  IF,       // if
  ELSE,     // else
  RETURN,   // return
} TokenType;

// the actual token data structure
typedef struct {
  TokenType type;
  char *literal;
} Token;

Token *nextToken(Lexer *l);
Token *newToken(TokenType tokenType, unsigned int byte);
char *readIdentifier(Lexer *l);
char *readNumber(Lexer *l);
bool isLetter(unsigned int ch);
bool isDigit(unsigned int ch);
TokenType lookupIdentifier(char *identifier);
void skipWhiteSpace(Lexer *l);
unsigned int peekChar(Lexer *l);
void printToken(Token *tok);

#endif
