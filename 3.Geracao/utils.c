//Tabela de Simbolos

enum{
    INT, 
    LOG,
    REG
};

char nomeTipo[3][4] = {"INT","LOG","REG"};

//criar uma estrutura e operações para manipular uma lista de campos

#define TAM_TAB 100

// acrescentar campos na tabela TAM|POS|CAMPOS Cada variavel dentro da struct gera um campo.

struct elemTabSimbolos{
    char id[100]; // nome do identificador
    int end; // endereço
    int tip; // tipo
}tabSimb[TAM_TAB], elemTab;

int posTab = 0; // indica a proxima posicao livre para inserir

int buscaSimbolo(char * s){
    int i;
    for (i = posTab - 1; strcmp(tabSimb[i].id, s) && i >= 0; i--)
    ;
    if(i == -1){
        char msg[200];
        sprintf(msg, "Identificador [%s] não encontrado", s);
        yyerror(msg);
    }
    return i;
}

void insereSimbolo(struct elemTabSimbolos elem){
    int i;
    if(posTab == TAM_TAB){
        yyerror ("Tabela de Simbolos cheia!");
    }
    for (i = posTab - 1; strcmp(tabSimb[i].id, elem.id) && i >= 0; i--)
    ;
    if(i != -1){
        char msg[200];
        sprintf(msg, "Identificador [%s] duplicado", elem.id);
        yyerror(msg);
    }
    tabSimb[posTab++] = elem;
}



void mostraTab(){
    puts("Tabela de simbolos");
    puts("------------------");
    printf("%30s | %s | %s\n", "ID", "END", "TIP");
    for(int i = 0; i < 50 ; i++)
        printf("-");
    for(int i = 0; i < posTab; i++)
        printf("\n%30s | %3d | %s", 
             tabSimb[i].id, 
             tabSimb[i].end, 
             nomeTipo[tabSimb[i].tip]
             );
    puts("");
}

//Pilha Semantica
#define TAM_PIL 100
int pilha[TAM_PIL];
int topo = -1;

void empilha(int valor){
    if(topo == TAM_PIL)
        yyerror("Pilha semantica cheia!");
    pilha[++topo] = valor;
}

int desempilha(void){
    if(topo == -1)
        yyerror("Pilha semantica vazia!");
    return pilha[topo--];
}

//tipo1 e tipo2 são os tipos esperados na expressão
//ret é o tipo que será empilhado como resultado da expressão
void testaTipo(int tipo1, int tipo2, int ret){
    int t1 = desempilha();
    int t2 = desempilha();
    if(t1 != tipo1 || t2 != tipo2)
        yyerror("Incompatibilidade de tipo !");
    empilha(ret);
}


