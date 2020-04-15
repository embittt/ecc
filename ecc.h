#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_RETURN,   // keyword return
  TK_IDENT,    // 識別子
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len;
};

// 現在着目しているトークン
extern Token *token;


// 抽象構文木のノードの種類
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /


  ND_EQ,  // ==
  ND_NE, // !=
  ND_LT, // <
  //ND_GT, // >
  ND_LE, // <=
  //ND_GE, // >=

  ND_ASSIGN, // =
  ND_LVAR, // ローカル変数
  ND_NUM, // 整数

  ND_RETURN, // return文
} NodeKind;

typedef struct Node Node;

// 抽象構文木のノードの型
struct Node {
  NodeKind kind; // ノードの型
  Node *lhs;     // 左辺
  Node *rhs;     // 右辺
  int val;       // kindがND_NUMの場合のみ使う
  int offset;    // kindがND_LVARの場合のみ使う、ローカル変数のベースポインタからのオフセット
};


typedef struct LVar LVar;
// local variable type
struct LVar {
  LVar *next;
  char *name;
  int len; // name length
  int offset; // offset from RBP
};

// local variable
extern LVar *locals; // !!!

void program();
Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

// 入力プログラム
extern char *user_input;

void error(char *fmt, ...);

Token *tokenize();
void gen(Node *node);

extern Node *code[100];

