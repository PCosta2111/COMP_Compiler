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
		}else{
			printOp(exp->attr.op.operator);
			tabs++;
			recPrint(exp->attr.op.left,tabs);
			recPrint(exp->attr.op.right,tabs);
		}
	}
}

void printAbsTree(Expr* exp){
	printf("\nABSTRACT TREE: \n");
	recPrint(exp,0);
}

void printCMD(CMD* c,int tabs){
	int i;
	for(i = 0 ; i < tabs ; i++)
		printf("   ");
	
	printf("%s\n",c->leftTXT);
	
}

void recPrintCode(CMDList* code,int tabs){
	if(code != NULL){
		printCMD(code->cmd,tabs);
		recPrintCode(code->cmd->insideBlock,tabs+1);
		if( code->cmd->cmd_else != NULL){
			printCMD(code->cmd->cmd_else,tabs);
			recPrintCode(code->cmd->cmd_else->insideBlock,tabs+1);
		}
		recPrintCode(code->next,tabs);
	}
}


void printCodeTree(CMDList* code){
	printf("\nABSTRACT TREE: \n");
	recPrintCode(code,0);	
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
