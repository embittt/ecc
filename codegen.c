#include "ecc.h"

void gen(Node *node) {
  if (node->kind == ND_NUM) {
    printf("  push %d\n", node->val);
    return;
  }

  gen(node->lhs);
  gen(node->rhs);

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->kind) {
  case ND_ADD:
    printf("  add rax, rdi\n");
    break;
  case ND_SUB:
    printf("  sub rax, rdi\n");
    break;
  case ND_MUL:
    printf("  imul rax, rdi\n");
    break;
  case ND_DIV:
    printf("  cqo\n");
    printf("  idiv rdi\n");
    break;
  case ND_EQ:
    printf("  cmp rax, rdi\n");
    printf("  sete al\n"); // if equal then al = 1 else al = 0
    printf("  movzb rax, al\n"); // upper 56bits = 0
    break;
  case ND_NE:
    printf("  cmp rax, rdi\n");
    printf("  setne al\n"); // if not equal then al = 1 else al = 0
    printf("  movzb rax, al\n"); // upper 56bits = 0
    break;
  case ND_LT:
    printf("  cmp rax, rdi\n");
    printf("  setl al\n"); // if less then al = 1 else al = 0
    printf("  movzb rax, al\n"); // upper 56bits = 0
    break;
  case ND_LE:
    printf("  cmp rax, rdi\n");
    printf("  setle al\n"); // if less equal then al = 1 else al = 0
    printf("  movzb rax, al\n"); // upper 56bits = 0
    break;
  }

  printf("  push rax\n");
}

