#include "ast.h"

char *ProgramTokenLiteral(Node *p) {
  ProgramNode *program = (ProgramNode *)p; // type cast
  if (program->statementSize > 0) {
    return program->statements[0]->TokenLiteral(
        program->statements[0]); // retrieves the literal of the first statement
                                 // in the program
  } else {
    return "";
  }
}

char *IdentifierTokenLiteral(Node *i) {
  Identifier *identifier = (Identifier *)i; // type cast
  return identifier->node.token.literal;
}

char *LetStatementTokenLiteral(Node *ls) {
  LetStatement *letStatement = (LetStatement *)ls; // type cast
  return letStatement->node.token.literal;
}
