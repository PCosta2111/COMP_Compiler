#include <stdio.h>
#include "parser.h"

int eval(Expr* expr) {
  int result = 0;
  if (expr == 0) {
    yyerror("Null expression!!");
  }
  else if (expr->kind == E_INTEGER) {
    result = expr->attr.value; 
  } 
  else if (expr->kind == E_OPERATION) {
    int vLeft = eval(expr->attr.op.left);
    int vRight = eval(expr->attr.op.right);
    switch (expr->attr.op.operator) {
      case PLUS: 
        result = vLeft + vRight; 
        break;
      case MINUS: 
        result = vLeft - vRight; 
        break;
      case MUL: 
        result = vLeft * vRight; 
        break;
      case DIV: 
        result = vLeft / vRight; 
        break;
      case MOD: 
        result = vLeft % vRight; 
        break;
      case EQUAL: 
		if( vLeft == vRight)
			result = 1;
		else
			result = 0; 
        break;
      case NOT_EQUAL: 
		if( vLeft != vRight)
			result = 1;
		else
			result = 0; 
        break;
      case E_GREATER: 
        if( vLeft >= vRight)
			result = 1;
		else
			result = 0; 
        break;
      case GREATER: 
        if( vLeft > vRight)
			result = 1;
		else
			result = 0; 
        break;
      case E_SMALLER: 
        if( vLeft <= vRight)
			result = 1;
		else
			result = 0; 
        break;
      case SMALLER: 
        if( vLeft < vRight)
			result = 1;
		else
			result = 0; 
        break;
       
      // TODO Other cases here ...
      default: yyerror("Unknown operator!");
    }
  }
  return result;
}

void printOp(int x){
	 switch (x) {
      case PLUS: 
        printf("+:\n");
        break;
      case MINUS: 
        printf("-:\n");
        break;
      case MUL: 
        printf("*:\n");
        break;
      case DIV: 
        printf("/:\n"); 
        break;
      case MOD: 
        printf("%:\n"); 
        break;
      case EQUAL: 
        printf("==:\n");
        break;
      case NOT_EQUAL: 
        printf("!=:\n"); 
        break;
      case E_GREATER: 
        printf(">=:\n"); 
        break;
      case GREATER: 
        printf(">:\n");
        break;
      case E_SMALLER:
        printf("<=:\n"); 
        break;
      case SMALLER:
        printf("<:\n"); 
        break;
       
      // TODO Other cases here ...
      default: yyerror("Unknown operator!");
    }
	
	
}

void recPrint(Expr* exp,int tabs){
	int c;
	if(exp != NULL){
		for(c = 0 ; c < tabs ; c++)
			printf("   ");
			
		if (exp->kind == E_INTEGER) {
			printf("%d\n",exp->attr.value);
		}else if(exp->kind == E_VAR){
			printf("%s\n",exp->attr.varname);
		}else{
			printOp(exp->attr.op.operator);
			tabs++;
			recPrint(exp->attr.op.left,tabs);
			recPrint(exp->attr.op.right,tabs);
		}
	}
}

void printVarList(VarList* v,int tabs){
	if(v != NULL){
		putTabs(tabs);
		printf("%s\n", v->head);
		printVarList(v->next,tabs);
	}
}

/*
 * PRINT BOOLEAN EXPRESSIONS
 * 
 * 
 * */
void printBoolExpr(BoolExpr* b,int tabs){
	int c;
	if(b != NULL){
		for(c = 0 ; c < tabs ; c++)
			printf("   ");
		printf("COND:\n");
		if (b->kind == E_BOOL) {
			if(b->attr.value == 1)
				printf("true\n");
			else
				printf("false\n");
		}else{
			
			putTabs(tabs+1);
			printOp(b->attr.op.operator);
			tabs += 2;
			recPrint(b->attr.op.left,tabs);
			recPrint(b->attr.op.right,tabs);
		}
	}
}

void printAbsTree(Expr* exp){
	printf("\nABSTRACT TREE: \n");
	recPrint(exp,0);
}

void putTabs(int tabs){
	int i;
	for(i = 0 ; i < tabs ; i++)
		printf("   ");
		
}
	

void recPrintCode(CMDList* code,int tabs){ // REFAZER COM SWITCH
	
	if(code != NULL){
		
		CMD* c = (CMD*) malloc(sizeof(CMD));
		c = code->cmd;
		putTabs(tabs);
		switch(c->id){
			case CMD_DECL:
				printf("%s %s =:\n", c->att.sdecl.var_type, c->att.sdecl.declared_var);
				recPrint(c->att.sdecl.expr,tabs+1);
				printf("\n");
				break;
			case CMD_ASSIGN:
				printf("%s =:\n", c->att.sassign.assigned_var);
				recPrint(c->att.sassign.expr,tabs+1);
				printf("\n");
				break;
			case CMD_IF:
				printf("IF :\n");
				printBoolExpr(c->att.sif.cond,tabs+1);
				recPrintCode(c->att.sif.insideBlock,tabs+1);
				if( c->att.sif.cmd_else != NULL){
					putTabs(tabs);
					printf("ELSE:\n");
					recPrintCode(c->att.sif.cmd_else->att.selse.insideBlock,tabs+1);
				}
				//recPrintCode(c->att.sif.cmd_else,tabs);
				printf("\n");
				break;
			case CMD_WHILE:
				printf("WHILE :\n");
				printBoolExpr(c->att.swhile.cond,tabs+1);
				recPrintCode(c->att.swhile.insideBlock,tabs+1);
				printf("\n");
				break;
			case CMD_FOR:
				printf("FOR :\n");
				putTabs(tabs+1);
				printf("INIT_EXPR:\n");
				putTabs(tabs+2);
				if(c->att.sfor.cmd_init->id == CMD_DECL){
					printf("%s %s =:\n",c->att.sfor.cmd_init->att.sdecl.var_type,c->att.sfor.cmd_init->att.sdecl.declared_var);
					recPrint(c->att.sfor.cmd_init->att.sdecl.expr,tabs+3); // ->att.sdecl.expr
				}
				else {
					printf("%s =:\n",c->att.sfor.cmd_init->att.sassign.assigned_var);
					recPrint(c->att.sfor.cmd_init->att.sassign.expr,tabs+3);
				}	
				printBoolExpr(c->att.sfor.cond,tabs+1);
				
				putTabs(tabs+1);
				printf("INCR_EXPR:\n");
				putTabs(tabs+2);
				printf("%s =:\n",c->att.sfor.cmd_incr->att.sassign.assigned_var); 
				recPrint(c->att.sfor.cmd_incr->att.sassign.expr,tabs+3); // ->att.sassign.expr
				printf("\n");
				break;
				
			case CMD_PRINT:
				printf("PRINT :\n");
				putTabs(tabs+1);
				printf("STRING : \n");
				putTabs(tabs+2);
				printf("%s\n",c->att.sprint.str);
				putTabs(tabs+1);
				printf("VARS : \n");
				printVarList(c->att.sprint.vList,tabs+2);
				printf("\n");
				break;
				
			case CMD_SCAN:
				printf("SCAN :\n");
				putTabs(tabs+1);
				printf("STRING : \n");
				putTabs(tabs+2);
				printf("%s\n",c->att.sscan.str);
				putTabs(tabs+1);
				printf("VARS : \n");
				printVarList(c->att.sscan.vList,tabs+2);
				printf("\n");
				break;

			default:
				printf("Unrecognized cmd\n");
			break;
		}
	}
	if(code->next != NULL){
		recPrintCode(code->next,tabs);
	}
}


void printCodeTree(CMDList* code){
	printf("\nABSTRACT TREE: \n\n");
	printf("INT MAIN():\n");
	recPrintCode(code,1);	
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
	  /*while(root->tail != NULL){
		printf("Result = %d\n", eval(root->exp));
		root = root->tail;
		printAbsTree(root->exp);
	  }
	  printf("Result = %d\n", eval(root->exp));
		printAbsTree(root->exp);*/
	  printf("accepted\n");
	  
	  printCodeTree(root);
	  
  }
  return 0;


}
