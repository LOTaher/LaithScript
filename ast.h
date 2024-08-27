#ifndef AST_H
#define AST_H

#include "token.h"

// the AST constructed only contains nodes that are connected to each other

typedef enum { STATEMENT, EXPRESSION } NodeType;

typedef struct Node {
  NodeType type;
  Token token;
  char *(*TokenLiteral)(struct Node *); // returns the literal value of the
                                        // token it’s associated with
} Node;

// the root of every AST our parser produces
typedef struct {
  Node **statements;
  int statementSize;
} ProgramNode;

typedef struct {
  Node node;   // node->token.literal = IDENT
  char *value; // the name of the identifier (e.g "x")
} Identifier;

typedef struct {
  Node node;        // node->token.literal = LET
  Identifier *name; // points to the value field of the identifier
  Node *value;      // is a node because it can be an expression or a value
} LetStatement;

char *ProgramTokenLiteral(Node *p);
char *IdentifierTokenLiteral(Node *i);
char *LetStatementTokenLiteral(Node *ls);

#endif
