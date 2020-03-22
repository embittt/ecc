#include "ecc.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    error("引数の個数が正しくありません");
    return 1;
  }

  user_input = argv[1];

  // トークナイズする
  //token = tokenize(argv[1]);
  token = tokenize();
  // parse
  Node *node = expr();

  // アセンブリの前半部分を出力
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // AST->assembly code generation
  gen(node);

  // expression value is on the stack top
  printf("  pop rax\n");

  printf("  ret\n");
  return 0;
}

