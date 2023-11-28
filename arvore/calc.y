%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
ptno raiz = NULL;
%}

%token VAR
%token ATRIB
%token NUM
%token MAIS
%token MENOS
%token VEZES
%token DIV
%token ABRE
%token FECHA
%token ENTER

%start comando

%left MAIS MENOS 
%left DIV VEZES

%%

linha : linha comando ENTER {
                                raiz = $2;  
                                mostra(raiz, 0);
                            }
  | ;

comando
   : expr
   {
    $$ = $1;
   }
   | VAR ATRIB expr
        {
          ptno p = criaNo('=',0);
          adFilho(p, $3);
          adFilho(p, $1);
          $$ = p;
        }
   ;
	 
expr 
  : NUM			          { $$ = $1; }
  : VAR               { $$ = $1; }
  | expr MAIS expr	  
          {
            ptno p = criaNo('+',0);
            adFilho(p, $3);
            adFilho(p, $1);
            $$ = p;
          }
  | expr MENOS expr	  
          {
            ptno p = criaNo('-',0);
            adFilho(p, $3);
            adFilho(p, $1);
            $$ = p;
          }
  | expr VEZES expr	 
          {
            ptno p = criaNo('*',0);
            adFilho(p, $3);
            adFilho(p, $1);
            $$ = p;
          } 
  | expr DIV expr	    
          {
            ptno p = criaNo('/',0);
            adFilho(p, $3);
            adFilho(p, $1);
            $$ = p;
          }
  | ABRE expr FECHA 
          {$$ = $2;}	
  ;
  
%%

void yyerror (char *s) {
    printf("%s \n", s);
}

int main (void) {
    yyparse();
    return 0;
}
