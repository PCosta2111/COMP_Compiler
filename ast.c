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
  //node->attr.varname = NULL;
  return node;
}

Expr* ast_var(char* v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  //node->attr.value = 0;
  node->attr.varname = v;
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

VarList* ast_var_list(char* head,VarList* tail){
	VarList* v = (VarList*) malloc(sizeof(VarList));
	
	v->head = head;
	v->next = tail;
	
	return v;
}


CMDList* ast_cmdlist(CMD* c, CMDList* next){
	CMDList* res = (CMDList*) malloc(sizeof(CMDList));
	res->cmd = c;
	//rintf("Here in cmdList\n");
	res->next=next;
	return res;

}
/*
CMD* ast_cmd(char* str1,CMD* cmd_else,CMDList* inside){  // ISTO VIA DEIXAR DE SER UTILIZADO
	CMD* res = (CMD*) malloc(sizeof(CMD));				 // QUANDO SE FIZER O ast_cmd_for
	res->leftTXT = str1;
	//printf("%s",str1);
	res->cmd_else = cmd_else;
	res->insideBlock=inside;
	return res;

}
* */

/*	TO-DO
 * 		1. Construtores para cada tipo de instruçao
 * 		2. Ajustar no bison as regras para usarem os tipos especificos de cada construtor
 * 		3. Ajustar no interpreter.c referencias desatualizadas a variaveis.
 * 
 * ast_cmd_decl -DONE-
 * ast_cmd_assign (variavel = expressao) -DONE-
 * ast_cmd_if -DONE-
 * ast_cmd_while -DONE-
 * ast_cmd_for (depois eu faço)
 * ast_cmd_print_scan -DONE-
 * */

CMD* ast_cmd_decl(char* str1,char* vname,Expr* expr){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->leftTXT = str1;
	res->id = CMD_DECL;
	res->att.sdecl.declared_var = vname;
	res->att.sdecl.expr =  expr;
	return res;

}

CMD* ast_cmd_assign(char* vname, Expr* expr){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->id = CMD_ASSIGN;
	res->att.sassign.expr=expr;
	res->att.sassign.assigned_var=vname;
	return res;
}

CMD* ast_cmd_if(char* str1,CMD* cmd_else,CMDList* inside,BoolExpr* b){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->id = CMD_IF;
	res->leftTXT = str1;
	res->att.sif.cond= b;
	
	res->att.sif.cmd_else = cmd_else;
	res->att.sif.insideBlock=inside;
	return res;

}

CMD* ast_cmd_else(char* str1, CMDList* inside){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->id = CMD_ELSE;
	res->leftTXT= str1;
	
	res->att.selse.insideBlock=inside;
	return res;
}


CMD* ast_cmd_while(char* str1,CMDList* inside,BoolExpr* b){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->leftTXT = str1;
	res->id = CMD_WHILE;
	res->att.swhile.cond = b;
	
	res->att.swhile.insideBlock=inside;
	return res;
}

CMD* ast_cmd_for(char* str1, CMD* start, BoolExpr* b, CMD* incr, CMDList* inside){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->leftTXT = str1;
	res->id = CMD_FOR;
	
	res->att.sfor.cmd_init = start;
	res->att.sfor.cond = b;
	res->att.sfor.cmd_incr = incr;
	res->att.sfor.insideBlock = inside;
	return res;
}

CMD* ast_cmd_PRINT_SCAN(char* str1,char* str,VarList* v){
	CMD* res = (CMD*) malloc(sizeof(CMD));
	res->leftTXT = str1;
	res->id = CMD_PRINT_SCAN;
	res->att.spscan.str= str;
	res->att.spscan.vList = v;
	return res;
}






