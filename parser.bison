// Tokens
%token 
  INT
  TRUE
  FALSE
  PLUS
  MINUS
  MUL
  DIV
  MOD
  EQUAL
  NOT_EQUAL
  E_GREATER
  GREATER
  E_SMALLER
  SMALLER
  IF_SIGN
  
// Operator associativity & precedence
%left PLUS MINUS
%left MUL DIV MOD
%left EQUAL NOT_EQUAL E_GREATER GREATER E_SMALLER SMALLER

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  int boolValue;
  Expr* exprValue; 
  ExprList* exprL; 
  BoolExpr* exprBool; 
}

%type <intValue> INT
%type <boolValue> TRUE
%type <boolValue> FALSE
%type <exprValue> expr
%type <exprBool> bexpr
%type <exprL> expr_list

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
ExprList* root;
BoolExpr* broot;
}

%%
program: expr_list { root = $1; }
  | bexpr { broot = $1;}
  
expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  } 
  |
  expr MINUS expr { 
    $$ = ast_operation(MINUS, $1, $3); 
  } 
  |
  expr MUL expr { 
    $$ = ast_operation(MUL, $1, $3); 
  }
  | 
  expr DIV expr { 
    $$ = ast_operation(DIV, $1, $3); 
  }
  | 
  expr MOD expr { 
    $$ = ast_operation(MOD, $1, $3); 
  } 
  
bexpr:
  TRUE {
    $$ = ast_bool($1); 
  }
  |
  FALSE {
    $$ = ast_bool($1); 
  }
  |
  expr EQUAL expr { 
    $$ = ast_Bool_operation(EQUAL, $1, $3); 
  } 
  |
  expr NOT_EQUAL expr { 
    $$ = ast_Bool_operation(NOT_EQUAL, $1, $3); 
  } 
  |
  expr E_GREATER expr { 
    $$ = ast_Bool_operation(E_GREATER, $1, $3); 
  }
  | 
  expr GREATER expr { 
    $$ = ast_Bool_operation(GREATER, $1, $3); 
  }
  | 
  expr E_SMALLER expr { 
    $$ = ast_Bool_operation(E_SMALLER, $1, $3); 
  }
  | 
  expr SMALLER expr { 
    $$ = ast_Bool_operation(SMALLER, $1, $3); 
  } 
  
expr_list: 
  { 
    $$ = NULL; 
  }
  |
  expr expr_list { $$ = ast_exprlist($1,$2);}
  ;
  

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

