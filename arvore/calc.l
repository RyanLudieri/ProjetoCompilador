%{
#include "calc.h"
#include <stdlib.h>
#define YYSTYPE ptno
#include "calc.h"
void yyerror (char *);
%}

%%
[0-9]+   { yylval = criaNO ( 'n', atoi(yytext)); return NUM; }
[a-z]    { yylval = criaNO ( 'v', *yytext - 'a'); return VAR;}
"="    return IGUAL;
"+"	 return MAIS;
"-"	 return MENOS;
"*"	 return VEZES;
"div"	 return DIV;
"("	 return ABRE;
")"	 return FECHA;
\n 	 return ENTER;
[ \t]+   /* saltar espacos e tabulacoes */
.        yyerror("caracter invalido");
%%

int yywrap(void) {
   return 1;
}
