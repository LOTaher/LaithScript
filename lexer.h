#ifndef LEXER_H

typedef struct {
  char *input;  // string input into the lexer
  int position; // current position in the input (points to a single character
                // in the input)
  int readPosition; // current reading position in the input (after the current
                    // character)
  unsigned char ch; // current character under examination (1 byte)
} Lexer;

Lexer *newLexer(char *input);
void readChar(Lexer *l);

#endif
