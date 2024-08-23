#ifndef TOKEN_C
#include "lexer.h"
#include <stdbool.h>

// here we define the different type of tokens are lexer will parse the source
// code to.
typedef enum {
  ILLEGAL,   // Illegal Character
  EOF_TOKEN, // EOF

  // identifiers + literals
  IDENT, // Identifier (add, foobar, x, y, ...)
  INT,   // Integer (12345)

  // operators
  ASSIGN,   // =
  PLUS,     // +
  MINUS,    // -
  BANG,     // !
  ASTERISK, // *
  SLASH,    // /

  LT, // <
  GT, // >

  // delimeters
  COMMA,     // ,
  SEMICOLON, // ;
  LPAREN,    // (
  RPAREN,    // )
  LBRACE,    // {
  RBRACE,    // }

  FUNCTION, // fn
  LET       // let
} TokenType;

// here is the actual token data structure
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

#endif
