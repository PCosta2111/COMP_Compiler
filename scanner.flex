%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }
\-?[0-9]+ {   yylval.intValue = atoi(yytext); return INT; }
int 	{ return TYPE_INT;}
float 	{ return TYPE_FLOAT;}
"true"  { return TRUE;}
"false" { return FALSE;}
"main"	{ return MAIN;}
","		{ return COLON;}
"{" 	{ return OPEN_BRACKET; }
"}" 	{ return CLOSE_BRACKET; }
"(" 	{ return OPEN_PAR; }
")" 	{ return CLOSE_PAR; }
";" 	{ return SEMI_COLON; }
"if" 	{ return IF; }
"then" 	{ return THEN; }
"else" 	{ return ELSE; }
"for" 	{ return FOR; }
"while" 	{ return WHILE; }
"printf" 	{ return PRINT; }
"scanf" 	{ return SCAN; }
"=" { return ASSIGN;}
"&"	 { return COM_E;}
"+"  { return PLUS; }
"-"  { return MINUS; }
"*"  { return MUL; }
"/"  { return DIV; }
"%"  { return MOD; }
"==" { return EQUAL;}
"!=" { return NOT_EQUAL;}
">=" { return E_GREATER;}
">"  { return GREATER;}
"<=" { return E_SMALLER;}
"<"  { return SMALLER;}
[a-z][a-zA-Z0-9_]* {  
	yylval.varName = strdup(yytext);
	return VAR_NAME; }
[a-zA-Z_]?\"(\\.|[^\\"])*\" { return STRING;}
.  { yyerror("unexpected character"); }
%%

