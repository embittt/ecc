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
  TK_IF,   // keyword if
  TK_ELSE,   // keyword else
  TK_WHILE,   // keyword while
  TK_FOR,   // keyword for
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

  ND_REF, // reference
  ND_DEREF, // dereference

  ND_EQ,  // ==
  ND_NE, // !=
  ND_LT, // <
  //ND_GT, // >
  ND_LE, // <=
  //ND_GE, // >=

  ND_ASSIGN, // =
  ND_LVAR, // ローカル変数
  ND_NUM, // 整数

  ND_FNCALL, // 関数呼び出し
  ND_FNDEF, // 関数定義
  ND_ARG, // 仮引数

  ND_COMMA, // ,

  ND_RETURN, // return文
  ND_IF, // if文
  ND_WHILE, // while文
  ND_FOR, // for文
  ND_BLOCK, // {...}

  ND_EXPRSTMT, // 式文
  ND_EMPTYSTMT, // 空文
} NodeKind;

typedef struct Node Node;

// 抽象構文木のノードの型
struct Node {
  NodeKind kind; // ノードの型

  Node *next;    // next node for {...} support

  Node *lhs;     // 左辺
  Node *rhs;     // 右辺
  int val;       // kindがND_NUMの場合のみ使う
  int offset;    // kindがND_LVARの場合のみ使う、ローカル変数のベースポインタからのオフセット

  char *str;     // kindがND_FNCALLの場合のみ使う
  int len;       // kindがND_FNCALLの場合のみ使う
  Node *args;    // kindがND_FNCALLの場合のみ使う

  // "if" ( cond ) then "else" els
  // "for" ( init; cond; inc ) body
  // "while" ( cond ) body
  // "do" body "while" ( cond )
  // "switch" ( cond ) body
  // "case" val ":" body
  Node *cond;
  Node *then;
  Node *els;
  Node *init;
  Node *inc;
  Node *body;
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
//extern LVar *locals; // !!!

void program();

Node *function();

Node *stmt();
Node *expr();

Node *comma();

Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

Node *arg();

// 入力プログラム
extern char *user_input;

void error(char *fmt, ...);

Token *tokenize();
void gen(Node *node);

extern Node *code[100];

