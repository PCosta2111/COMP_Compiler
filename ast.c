// AST constructor functions

#include <stdlib.h> // for malloc
#include <stdio.h> // for malloc
#include <string.h> // for malloc
#include <stdbool.h>
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr* ast_expr(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

/*
 * 
 * 
 * 
 * 
 * */

BoolExpr* ast_Bool_operation
(int operator, Expr* left, Expr* right) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_B_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}
BoolExpr* ast_bool(int v) {
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = E_BOOL;
  node->attr.value = v;
  return node;
}

CMDList* ast_cmdlist(CMD* c, CMDList* next){
	CMDList* res = (CMDList*) malloc(sizeof(CMDList));
	res->cmd = c;
	//rintf("Here in cmdList\n");
	res->next=next;
	return res;

}

CMD* ast_cmd(char* str1,char* str2,CMDList* inside){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->leftTXT = str1;
	//printf("%s",str1);
	res->rightTXT = str2;
	res->insideBlock=inside;
	return res;

}




