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

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}
"true"  {  return TRUE;}
"false" { return FALSE;}
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
"?"  { return IF_SIGN;}


.  { yyerror("unexpected character"); }
%%

