#include "ecc.h"

int labelNo = 0;

void gen_lval(Node *node) {
  if (node->kind != ND_LVAR)
    error("代入の左辺値が変数ではありません");

  printf("# GEN_LVAL\n");
  printf("  mov rax, rbp\n");
  printf("  sub rax, %d\n", node->offset);
  printf("  push rax\n");
}

void gen(Node *node) {
  if (!node)
    return;

  switch (node->kind) {
  case ND_NUM:
    printf("# ND_NUM\n");
    printf("  push %d\n", node->val);
    return;
  case ND_LVAR:
    gen_lval(node);
    printf("# ND_LVAR\n");
    printf("  pop rax\n");
    printf("  mov rax, [rax]\n");
    printf("  push rax\n");
    return;
  case ND_ASSIGN:
    gen_lval(node->lhs);
    gen(node->rhs);
    printf("# ND_ASSIGN\n");
    printf("  pop rdi\n");
    printf("  pop rax\n");
    printf("  mov [rax], rdi\n");
    printf("  push rdi\n");
    return;
  case ND_COMMA:
    gen(node->lhs);
    printf("# ND_COMMA\n");
    printf("  pop rax #remove stack top(comma)\n"); // !!!for Stack problem
    gen(node->rhs);
    return;

  case ND_RETURN:
    gen(node->lhs);
    printf("# ND_RETURN\n");
    printf("  pop rax\n");
    printf("  mov rsp, rbp\n");
    printf("  pop rbp\n");
    printf("  ret\n");
    return;
  case ND_IF:
    if (!node->els) {
      gen(node->cond);
    printf("# ND_IF\n");
      printf("  pop rax\n");
      printf("  cmp rax, 0\n");
      printf("  je  .Lend%03d\n", labelNo);
      gen(node->then);
    printf("# ND_IF(THEN)\n");
      printf(".Lend%03d:\n", labelNo++);
    }
    else {
      gen(node->cond);
    printf("# ND_IF\n");
      printf("  pop rax\n");
      printf("  cmp rax, 0\n");
      printf("  je  .Lelse%03d\n", labelNo);
      gen(node->then);
    printf("# ND_IF(THEN)\n");
      printf("  jmp .Lend%03d\n", labelNo + 1);
      printf(".Lelse%03d:\n", labelNo);
      gen(node->els);
    printf("# ND_IF(ELSE)\n");
      printf(".Lend%03d:\n", labelNo + 1);
      labelNo += 2;
    }
    return;
  case ND_WHILE:
    printf("# ND_WHILE\n");
    printf(".Lbegin%03d:\n", labelNo);
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je  .Lend%03d\n", labelNo + 1);
    gen(node->body);
    printf("  jmp .Lbegin%03d\n", labelNo);
    printf(".Lend%03d:\n", labelNo + 1);
    labelNo += 2;
    return;
  case ND_FOR:
    printf("# ND_FOR(INIT)\n");
    gen(node->init);
    printf("  pop rax #remove stack top(if-init)\n"); // !!!for Stack problem
    printf(".Lbegin%03d:\n", labelNo);
    printf("# ND_FOR(COND)\n");
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je  .Lend%03d\n", labelNo + 1);
    printf("# ND_FOR(BODY)\n");
    gen(node->body);
    printf("# ND_FOR(INC)\n");
    gen(node->inc);
    printf("  pop rax #remove stack top(if-inc)\n"); // !!!for Stack problem
    printf("  jmp .Lbegin%03d\n", labelNo);
    printf(".Lend%03d:\n", labelNo + 1);
    labelNo += 2;
    return;
  case ND_BLOCK:
    node = node->body; // important!!!
    while (node) {
    printf("# ND_BLOCK(STMT)\n");
      gen(node);
      // pop from stack?
      node = node->next;
    }
    return;
  case ND_EXPRSTMT:
    printf("# ND_EXPRSTMT\n");
    gen(node->lhs);
    printf("  pop rax #remove stack top(exprstmt)\n"); // !!!for Stack problem
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

