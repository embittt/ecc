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
  //Node *node = expr();
  program();

  // アセンブリの前半部分を出力
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // prologue
  // 26 var erea
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, 208\n"); // 8 * 26 // !!!

  // AST->assembly code generation
  //gen(node);
  for (int i = 0; code[i]; i++) {
    gen(code[i]);

  // expression value is on the stack top
  printf("  pop rax\n");
  }

  // epilogue
  printf("  mov rsp, rbp\n");
  printf("  pop rbp\n");
  printf("  ret\n");
  return 0;
}

