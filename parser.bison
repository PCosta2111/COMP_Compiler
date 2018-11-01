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
  VAR_NAME
  MAIN
  TYPE_INT
  TYPE_FLOAT
  OPEN_BRACKET
  CLOSE_BRACKET 
  SEMI_COLON 
  ASSIGN
  IF
  THEN
  ELSE
  FOR
  WHILE
  OPEN_PAR
  CLOSE_PAR
  STRING
  PRINT
  COLON
  SCAN
  COM_E
  
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
  char* varName;
  Expr* exprValue; 
  CMD* cmd; 
  CMDList* cmdList; 
  BoolExpr* exprBool;
  VarList* vList;  
}

%type <intValue> INT
%type <varName> STRING
%type <varName> VAR_NAME
%type <boolValue> TRUE
%type <boolValue> FALSE
%type <exprValue> expr
%type <exprBool> bexpr
%type <cmdList> program
%type <cmdList> code
%type <cmd> atrib
%type <cmd> if
%type <cmd> else
%type <cmd> for
%type <cmd> while
%type <cmd> printf
%type <cmd> scanf
%type <vList> var_list
%type <vList> s_var_list

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
CMDList* root;
BoolExpr* broot;
}

%%
program: TYPE_INT MAIN OPEN_PAR CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET { root = $6; }

code:
	{
		$$ = NULL;
	}
	|
	atrib SEMI_COLON code {$$ = ast_cmdlist($1,$3);}
	|
	if code {$$ = ast_cmdlist($1,$2);}
	|
	for code {$$ = ast_cmdlist($1,$2);}
	|
	while code {$$ = ast_cmdlist($1,$2);}
	|
	printf code {$$ = ast_cmdlist($1,$2);}
	|
	scanf code {$$ = ast_cmdlist($1,$2);};
	
atrib:
	TYPE_INT VAR_NAME ASSIGN expr {$$ = ast_cmd_decl("INT",$2,$4);}
	|
	TYPE_FLOAT VAR_NAME ASSIGN expr {$$ = ast_cmd_decl("FLOAT",$2,$4);}
	|
	VAR_NAME ASSIGN expr {$$ = ast_cmd_assign($1,$3);}

if:
	IF OPEN_PAR bexpr CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd_if(NULL,$6,$3);}
	|
	IF OPEN_PAR bexpr CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET else {$$ = ast_cmd_if($8,$6,$3);};

else:
	ELSE OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd_else($3);};

for:
	FOR OPEN_PAR atrib SEMI_COLON bexpr SEMI_COLON atrib CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd_for($3,$5,$7,$10);};

while:
	WHILE OPEN_PAR bexpr CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd_while($6,$3);};
	
printf:
	PRINT OPEN_PAR STRING var_list CLOSE_PAR SEMI_COLON {$$ = ast_cmd_print($3,$4);}; 

scanf:
	SCAN OPEN_PAR STRING s_var_list CLOSE_PAR SEMI_COLON {$$ = ast_cmd_scan($3,$4);};
		
var_list:
	{ $$ = NULL;}
	|
	COLON VAR_NAME var_list { $$ = ast_var_list($2,$3);}

s_var_list:
	{ $$ = NULL;}
	|
	COLON COM_E VAR_NAME s_var_list { $$ = ast_var_list($3,$4);}
	
expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  |
  VAR_NAME { 
    $$ = ast_var($1); 
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
    $$ = ast_bool(1); 
  }
  |
  FALSE {
    $$ = ast_bool(0); 
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
  

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

