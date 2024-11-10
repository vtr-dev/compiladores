%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

extern int yylex();
extern char* yytext;
extern FILE *yyin;
extern int number_errors;
extern int yylineno;
extern int line_number;
extern int column_number;
extern int verbose;

extern int production_count;

#define YYLTYPE_IS_DECLARED 1

typedef struct YYLTYPE {
    int first_line;       
    int first_column;     
    int last_line;       
    int last_column;     
    char text[1024];    
} YYLTYPE;


void yyerror(const char *s);
void yyerror_with_location(YYLTYPE *yylloc, const char *s);
void print_production(const char* production);

#define YYERROR_VERBOSE 1


// Usamos o ChatGPT para solucionar o problema de erro do Bison
#define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do {                                                             \
        if (N) {                                                     \
            (Current).first_line   = YYRHSLOC(Rhs, 1).first_line;      \
            (Current).first_column = YYRHSLOC(Rhs, 1).first_column;    \
            (Current).last_line    = YYRHSLOC(Rhs, N).last_line;     \
            (Current).last_column  = YYRHSLOC(Rhs, N).last_column;   \
        } else {                                                     \
            (Current).first_line   = (Current).last_line   =          \
                YYRHSLOC(Rhs, 0).last_line;                          \
            (Current).first_column = (Current).last_column =          \
                YYRHSLOC(Rhs, 0).last_column;                        \
        }                                                            \
        sprintf((Current).text, "%d", yylineno); \
    } while (0)

int error_reported = 0;

%}

%union {
    int integer;      
    double real;      
    char *string;
}

%token <real> TOKEN_NUMERO
%token <string> TOKEN_STRING_LITERAL
%token <string> TOKEN_IDENTIFICADOR
%token <string> TOKEN_OP_RELACIONAL
%token <string> TOKEN_OP_ARITMETICO

%token TOKEN_ATRIBUICAO TOKEN_ABRE_PAR TOKEN_FECHA_PAR TOKEN_VIRGULA TOKEN_PONTO_E_VIRG
%token TOKEN_INICIO_FUNCAO TOKEN_FIM_FUNCAO TOKEN_INICIO_ARGS TOKEN_FIM_ARGS
%token TOKEN_ESCREVA TOKEN_SE TOKEN_ENTAO TOKEN_SENAO TOKEN_FIM_SE TOKEN_ENQUANTO TOKEN_FACA TOKEN_FIM_ENQUANTO TOKEN_ERRO TOKEN_CHAMA TOKEN_CHAMADA TOKEN_RETORNA TOKEN_TIPO

%token TOKEN_INTEIRO TOKEN_REAL TOKEN_CARACTERE TOKEN_LITERAL
%token TOKEN_SOMA TOKEN_SUB TOKEN_MULT TOKEN_DIVISAO

%right TOKEN_ATRIBUICAO
%left TOKEN_OP_RELACIONAL
%left TOKEN_SOMA TOKE_SUB
%left TOKEN_MULT TOKEN_DIVISAO

%type <real> EXPRESSAO_MATEMATICA TERMO_MATEMATICO EXPRESSAO_BOOLEANA
%type <string> VARIAVEL_TIPO

%start PROGRAMA
%locations
%debug

%%

PROGRAMA:
    LISTA_FUNCOES {
        print_production("PROGRAMA -> LISTA_FUNCOES");
    }
    ;

LISTA_FUNCOES:
    FUNCAO LISTA_FUNCOES {
        print_production("LISTA_FUNCOES -> FUNCAO LISTA_FUNCOES");
    }
    | FUNCAO {
        print_production("LISTA_FUNCOES -> FUNCAO");
    }
    ;

FUNCAO:
    TOKEN_INICIO_FUNCAO FUNCAO_DECLARACAO TOKEN_FIM_FUNCAO {
        print_production("FUNCAO -> TOKEN_INICIO_FUNCAO FUNCAO_DECLARACAO TOKEN_FIM_FUNCAO");
    }
    | TOKEN_INICIO_FUNCAO FUNCAO_DECLARACAO error { 
        yyerror_with_location(&@1, "Erro de sintaxe no fim da função"); 
        yyerrok; 
        yyclearin; 
    }
    | error TOKEN_FIM_FUNCAO { 
        yyerror_with_location(&@1, "Erro de sintaxe no início da função"); 
        yyerrok; 
        yyclearin; 
    }
    ;

FUNCAO_DECLARACAO:
    FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS FUNCAO_CORPO {
        print_production("FUNCAO_DECLARACAO -> FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS FUNCAO_CORPO");
    }
    | error FUNCAO_CORPO { 
        yyerror_with_location(&@1, "Erro de sintaxe na declaração da função"); 
        yyerrok; 
        yyclearin; 
    }
    ;

FUNCAO_NOME:
    TOKEN_IDENTIFICADOR {
        print_production("FUNCAO_NOME -> TOKEN_IDENTIFICADOR");
    }
    ;

FUNCAO_RETORNO:
    TOKEN_TIPO FUNCAO_RETORNO_TIPO {
        print_production("FUNCAO_RETORNO -> TOKEN_TIPO FUNCAO_RETORNO_TIPO");
    }
    | {
        print_production("FUNCAO_RETORNO -> epsilon");
    }
    ;

FUNCAO_RETORNO_TIPO:
    TOKEN_INTEIRO {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_INTEIRO");
    }
    | TOKEN_CARACTERE {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_CARACTERE");
    }
    | TOKEN_REAL {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_REAL");
    }
    | TOKEN_LITERAL {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_LITERAL");
    }
    ;

FUNCAO_ARGS:
    FUNCAO_ARGS_CORPO {
        print_production("FUNCAO_ARGS -> FUNCAO_ARGS_CORPO");
    }
    | {
        print_production("FUNCAO_ARGS -> epsilon");
    }
    ;

FUNCAO_ARGS_CORPO:
    LISTA_ARGS {
        print_production("FUNCAO_ARGS_CORPO -> LISTA_ARGS");
    }
    ;

LISTA_ARGS:
    ARG_DECLARACAO LISTA_ARGS {
        print_production("LISTA_ARGS -> ARG_DECLARACAO LISTA_ARGS");
    }
    | ARG_DECLARACAO {
        print_production("LISTA_ARGS -> ARG_DECLARACAO");
    }
    ;

ARG_DECLARACAO:
    TIPO_ARG LISTA_IDENTIFICADORES {
        print_production("ARG_DECLARACAO -> TIPO_ARG LISTA_IDENTIFICADORES");
    }
    ;

TIPO_ARG:
    VARIAVEL_TIPO {
        print_production("TIPO_ARG -> VARIAVEL_TIPO");
    };

LISTA_IDENTIFICADORES:
    TOKEN_IDENTIFICADOR TOKEN_VIRGULA LISTA_IDENTIFICADORES {
        print_production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR , LISTA_IDENTIFICADORES");
    }
    | TOKEN_IDENTIFICADOR {
        print_production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR");
    }
    ;

FUNCAO_CORPO:
    LISTA_DECLARACOES {
        print_production("FUNCAO_CORPO -> { LISTA_DECLARACOES }");
    }
    ;

LISTA_DECLARACOES:
    DECLARACAO LISTA_DECLARACOES {
        print_production("LISTA_DECLARACOES -> DECLARACAO LISTA_DECLARACOES");
    }
    | DECLARACAO {
        print_production("LISTA_DECLARACOES -> DECLARACAO");
    }
    ;

DECLARACAO:
    ESCREVA_DECLARACAO
    | CHAMA_DECLARACAO
    | VARIAVEL_DECLARACAO
    | SE_DECLARACAO
    | ENQUANTO_DECLARACAO
    | ATRIBUICAO_DECLARACAO
    | RETORNA_DECLARACAO
    ;

ESCREVA_DECLARACAO:
    TOKEN_ESCREVA ESCREVA_CORPO TOKEN_PONTO_E_VIRG {
        print_production("ESCREVA_DECLARACAO -> TOKEN_ESCREVA ESCREVA_CORPO ;");
    }
    ;

ESCREVA_CORPO:
    TOKEN_STRING_LITERAL {
        print_production("ESCREVA_CORPO -> TOKEN_STRING_LITERAL");
    }
    | TOKEN_IDENTIFICADOR {
        print_production("ESCREVA_CORPO -> TOKEN_IDENTIFICADOR");
    }
    ;

CHAMA_DECLARACAO:
    TOKEN_CHAMA TOKEN_CHAMADA TOKEN_IDENTIFICADOR CHAMA_ARGS TOKEN_PONTO_E_VIRG {
        print_production("CHAMA_DECLARACAO -> TOKEN_CHAMA TOKEN_CHAMADA TOKEN_IDENTIFICADOR CHAMA_ARGS ;");
    }
    ;

CHAMA_ARGS:
    TOKEN_IDENTIFICADOR CHAMA_ARGS {
        print_production("CHAMA_ARGS -> TOKEN_IDENTIFICADOR CHAMA_ARGS");
    }
    | TOKEN_IDENTIFICADOR {
        print_production("CHAMA_ARGS -> TOKEN_IDENTIFICADOR");
    }
    ;

VARIAVEL_DECLARACAO:
    VARIAVEL_TIPO VARIAVEL_DECLARACAO_CORPO {
        print_production("VARIAVEL_DECLARACAO -> VARIAVEL_TIPO VARIAVEL_DECLARACAO_CORPO");
    }
    ;

VARIAVEL_DECLARACAO_CORPO:
    TOKEN_IDENTIFICADOR TOKEN_PONTO_E_VIRG {
        print_production("VARIAVEL_DECLARACAO_CORPO -> TOKEN_IDENTIFICADOR ;");
    }
    | ATRIBUICAO_DECLARACAO {
        print_production("VARIAVEL_DECLARACAO_CORPO -> ATRIBUICAO_DECLARACAO");
    }
    ;

VARIAVEL_TIPO:
    TOKEN_INTEIRO {
        print_production("VARIAVEL_TIPO -> TOKEN_INTEIRO");
    }
    | TOKEN_REAL {
        print_production("VARIAVEL_TIPO -> TOKEN_REAL");
    }
    | TOKEN_CARACTERE {
        print_production("VARIAVEL_TIPO -> TOKEN_CARACTERE");
    }
    | TOKEN_LITERAL {
        print_production("VARIAVEL_TIPO -> TOKEN_LITERAL");
    }
    ;

RETORNA_DECLARACAO:
    TOKEN_RETORNA RETORNA_CORPO TOKEN_PONTO_E_VIRG {
        print_production("RETORNA_DECLARACAO -> TOKEN_RETORNA RETORNA_CORPO ;");
    }
    ;

RETORNA_CORPO:
    TOKEN_IDENTIFICADOR {
        print_production("RETORNA_CORPO -> TOKEN_IDENTIFICADOR");
    }
    | VALOR {
        print_production("RETORNA_CORPO -> VALOR");
    }
    ;

VALOR:
    TOKEN_NUMERO {
        print_production("VALOR -> TOKEN_NUM");
    }
    | TOKEN_STRING_LITERAL {
        print_production("VALOR -> TOKEN_STRING_LITERAL");
    }
  
SE_DECLARACAO:
    TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO SENAO_BLOCO TOKEN_FIM_SE {
        print_production("SE_DECLARACAO -> TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO SENAO_BLOCO TOKEN_FIM_SE");
    }
    ;

SE_CABECALHO:
    TOKEN_ABRE_PAR EXPRESSAO_BOOLEANA TOKEN_FECHA_PAR TOKEN_ENTAO {
        print_production("SE_CABECALHO -> ( EXPRESSAO_BOOLEANA ) TOKEN_ENTAO");
    }
    ;

SENAO_SE_BLOCO:
    TOKEN_SENAO TOKEN_SE SE_CABECALHO SE_CORPO {
        print_production("SENAO_SE_BLOCO -> TOKEN_SENAO TOKEN_SE SE_CABECALHO SE_CORPO");
    }
    | {
        print_production("SENAO_SE_BLOCO -> epsilon");
    }
    ;

SENAO_BLOCO:
    TOKEN_SENAO SE_CORPO {
        print_production("SENAO_BLOCO -> TOKEN_SENAO SE_CORPO");
    }
    | {
        print_production("SENAO_BLOCO -> epsilon");
    }
    ;

SE_CORPO:
    FUNCAO_CORPO {
        print_production("SE_CORPO -> FUNCAO_CORPO");
    }
    ;

ENQUANTO_DECLARACAO:
    TOKEN_ENQUANTO TOKEN_ABRE_PAR EXPRESSAO_BOOLEANA TOKEN_FECHA_PAR TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO {
        print_production("ENQUANTO_DECLARACAO -> TOKEN_ENQUANTO ( EXPRESSAO_BOOLEANA ) TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO");
    }
    ;

ENQUANTO_CORPO:
    FUNCAO_CORPO {
        print_production("ENQUANTO_CORPO -> FUNCAO_CORPO");
    }
    ;


ATRIBUICAO_DECLARACAO:
    TOKEN_IDENTIFICADOR TOKEN_ATRIBUICAO EXPRESSAO TOKEN_PONTO_E_VIRG {
        print_production("ATRIBUICAO_DECLARACAO -> TOKEN_IDENTIFICADOR = EXPRESSAO ;");
    }
    ;

EXPRESSAO:
    CHAMA_DECLARACAO
    | TOKEN_IDENTIFICADOR
    | EXPRESSAO_MATEMATICA
    | VALOR
    ;


EXPRESSAO_MATEMATICA:
    TERMO_MATEMATICO EXPRESSAO_SOMA_SUB {
        print_production("EXPRESSAO_MATEMATICA -> TERMO_MATEMATICO EXPRESSAO_SOMA_SUB");
    }
    | TERMO_MATEMATICO {
        print_production("EXPRESSAO_MATEMATICA -> TERMO_MATEMATICO");
    }
    ;

EXPRESSAO_SOMA_SUB:
    TOKEN_SOMA EXPRESSAO_MATEMATICA {
        print_production("EXPRESSAO_SOMA_SUB -> TOKEN_SOMA EXPRESSAO_MATEMATICA");
    }
    | TOKEN_SUB EXPRESSAO_MATEMATICA {
        print_production("EXPRESSAO_SOMA_SUB -> TOKEN_SUB EXPRESSAO_MATEMATICA");
    }
    ;

TERMO_MATEMATICO:
    FATOR_MATEMATICO EXPRESSAO_MULT_DIV {
        print_production("TERMO_MATEMATICO -> FATOR_MATEMATICO EXPRESSAO_MULT_DIV");
    }
    | FATOR_MATEMATICO {
        print_production("TERMO_MATEMATICO -> FATOR_MATEMATICO");
    }
    ;

EXPRESSAO_MULT_DIV:
    TOKEN_MULT TERMO_MATEMATICO {
        print_production("EXPRESSAO_MULT_DIV -> TOKEN_MULT TERMO_MATEMATICO");
    }
    | TOKEN_DIVISAO TERMO_MATEMATICO {
        print_production("EXPRESSAO_MULT_DIV -> TOKEN_DIVISAO TERMO_MATEMATICO");
    }
    ;

FATOR_MATEMATICO:
    SINAL_MATEMATICO FATOR_PRIMARIO_MATEMATICO {
        print_production("FATOR_MATEMATICO -> SINAL_MATEMATICO FATOR_PRIMARIO_MATEMATICO");
    }
    ;

SINAL_MATEMATICO:
    TOKEN_SOMA {
        print_production("SINAL_MATEMATICO -> TOKEN_SOMA");
    }
    | TOKEN_SUB {
        print_production("SINAL_MATEMATICO -> TOKEN_SUB");
    }
    | {
        print_production("SINAL_MATEMATICO -> epsilon");
    }
    ;

FATOR_PRIMARIO_MATEMATICO:
    TOKEN_IDENTIFICADOR {
        print_production("FATOR_PRIMARIO_MATEMATICO -> TOKEN_IDENTIFICADOR");
    }
    | TOKEN_NUMERO {
        print_production("FATOR_PRIMARIO_MATEMATICO -> TOKEN_NUMERO");
    }
    | TOKEN_ABRE_PAR EXPRESSAO_MATEMATICA TOKEN_FECHA_PAR {
        print_production("FATOR_PRIMARIO_MATEMATICO -> ( EXPRESSAO_MATEMATICA )");
    }
    ;


EXPRESSAO_BOOLEANA:
    TERMO_BOOLEANO TOKEN_OP_RELACIONAL TERMO_BOOLEANO {
        print_production("EXPRESSAO_BOOLEANA -> TERMO_BOOLEANO TOKEN_OP_RELACIONAL TERMO_BOOLEANO");
    }
    ;

TERMO_BOOLEANO:
    TOKEN_IDENTIFICADOR {
        print_production("TERMO_BOOLEANO -> TOKEN_IDENTIFICADOR");
    }
    | VALOR {
        print_production("TERMO_BOOLEANO -> VALOR");
    }
    ;


%%

void yyerror(const char *s) {
    YYLTYPE yylloc;
    yylloc.first_line = yylloc.last_line = yylineno;
    yylloc.first_column = yylloc.last_column = column_number;
    sprintf(yylloc.text, "%d", yylineno);
    yyerror_with_location(&yylloc, s);
    number_errors++;
}

void yyerror_with_location(YYLTYPE *yylloc, const char *s) {
    fprintf(stderr, "Erro sintático na linha %d, coluna %d: %s\n", yylloc->first_line, yylloc->last_column, s);
    fprintf(stderr, "Linha do erro sintático:\"%s\"\n\n", yytext);
}

void print_production(const char* production) {
    if(verbose){
        fprintf(stdout, "Produção utilizada: %s\n", production);
    }
    production_count++;
}