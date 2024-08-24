#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // REPL
    printf("not handling repl yet\n");
  }

  else if (argc == 2) {
    if (!strcmp(strrchr(argv[1], '\0') - 3, ".lt")) {
      // the filename ends with .lt

      // open the file in read only mode
      FILE *file_ptr = fopen(argv[1], "r");

      if (file_ptr == NULL) {
        printf("file cannot be read\n");
        return EXIT_FAILURE;
      }

      // move the file pointer to the end of the file
      fseek(file_ptr, 0, SEEK_END);
      // gets the current position of the file pointer (because it is at the end
      // of the file, this would be the total byte count)
      long file_size = ftell(file_ptr);
      // move the file pointer back to the start so the file can be properly
      // read
      rewind(file_ptr);

      // create the buffer for the content of the file
      // take the amount of bytes the file is, add 1 for the null character,
      // then multiply it by the size of chars since there is a char in each
      // byte counted
      char *file_content = (char *)malloc((file_size + 1) * sizeof(char));

      if (file_content == NULL) {
        printf("failed to properly allocate memory\n");
        fclose(file_ptr);
        return EXIT_FAILURE;
      }

      // read the file content into the buffer
      fread(file_content, sizeof(char), file_size, file_ptr);
      file_content[file_size] = '\0'; // null terminate the string

      // initialize the lexer
      Lexer *lexer = newLexer(file_content);

      // tokenization loop
      Token *token;
      while ((token = nextToken(lexer)) != NULL && token->type != EOF_TOKEN) {
        printToken(token);
        free(token->literal); // free the literal string inside the token
        free(token); // free token memory after processing and printing it
      }

      // cleanup open buffers and active memory
      free(file_content);
      free(lexer);
      fclose(file_ptr);

    } else {
      printf("invalid file provided\n");
      return EXIT_FAILURE;
    }

  }
  else {
    printf("invalid arguments\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
