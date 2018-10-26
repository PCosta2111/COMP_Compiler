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
}

%type <intValue> INT
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
	TYPE_INT VAR_NAME {$$ = ast_cmd("INT",NULL,NULL);}
	|
	TYPE_FLOAT VAR_NAME {$$ = ast_cmd("FLOAT",NULL,NULL);}
	|
	TYPE_INT VAR_NAME ASSIGN expr {$$ = ast_cmd("INT $2",NULL,NULL);}
	|
	TYPE_FLOAT VAR_NAME ASSIGN expr {$$ = ast_cmd("FLOAT",NULL,NULL);}
	|
	VAR_NAME ASSIGN expr {$$ = ast_cmd("INT",NULL,NULL);};

if:
	IF OPEN_PAR bexpr CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd("IF",NULL,$6);}
	|
	IF OPEN_PAR bexpr CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET else {$$ = ast_cmd("IF",$8,$6);};

else:
	ELSE OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd("ELSE",NULL,$3);};

for:
	FOR OPEN_PAR atrib SEMI_COLON bexpr SEMI_COLON atrib CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd("FOR",NULL,$10);};

while:
	WHILE OPEN_PAR bexpr CLOSE_PAR OPEN_BRACKET code CLOSE_BRACKET {$$ = ast_cmd("WHILE",NULL,$6);};
	
printf:
	PRINT OPEN_PAR STRING var_list CLOSE_PAR SEMI_COLON {$$ = ast_cmd("PRINTF",NULL,NULL);}; 

scanf:
	SCAN OPEN_PAR STRING s_var_list CLOSE_PAR SEMI_COLON {$$ = ast_cmd("SCANF",NULL,NULL);};
		
var_list:
	|
	COLON VAR_NAME var_list 

s_var_list:
	|
	COLON COM_E VAR_NAME s_var_list
	
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
  

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

