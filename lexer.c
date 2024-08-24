#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// creates a new Lexer
Lexer *newLexer(char *input) {
  // first, memory must be allocated to the heap so this lexer can persist
  // across multiple functions.
  Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));

  if (lexer == NULL) {
    printf("memory allocation failed.");
    return NULL;
  }

  // memory is not allocated to input, because it is passed into the function,
  // meaning it should be handled already
  lexer->input = input;
  lexer->position = 0;
  lexer->readPosition = 0;
  lexer->ch = '\0';

  readChar(lexer);

  return lexer;
}

void readChar(Lexer *l) {
  // if we have reached the end of the string input, set the current character
  // to 0 (null character)
  if (l->readPosition > strlen(l->input)) {
    l->ch = '\0';
  } else {
    // set the current character to the character at the readPosition
    l->ch = l->input[l->readPosition];
  }

  l->position = l->readPosition;
  l->readPosition += 1;
}
