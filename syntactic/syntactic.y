%{
// Inclusão das bibliotecas necessárias para o analisador sintático
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

// Declaração das funções externas fornecidas pelo analisador léxico
extern int yylex();
extern YYSTYPE yylval;
extern char* yytext;
extern FILE *yyin;
extern int number_errors;
extern char current_line[1024];
extern int verbose;

// Variável global para contar produções
extern int production_count;

// Definição de uma macro para declarar que YYLTYPE está definido
#define YYLTYPE_IS_DECLARED 1

// Estrutura para armazenar informações sobre a localização dos tokens no código fonte
typedef struct YYLTYPE {
    int first_line;       // Primeira linha do token
    int first_column;     // Primeira coluna do token
    int last_line;       // Última linha do token
    int last_column;     // Última coluna do token
    char text[1024];     // Texto do token
} YYLTYPE;

// Protótipos das funções de tratamento de erros
void yyerror_with_location(YYLTYPE *yylloc, const char *s);
void print_production(const char* production);

// Definição de uma macro para permitir mensagens de erro detalhadas
#define YYERROR_VERBOSE 1

// Definição de uma macro para configurar a localização padrão de erros
// Criado pelo ChatGPT
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
        strncpy((Current).text, current_line, sizeof(current_line)); \
        (Current).text[sizeof(current_line) - 1] = '\0';             \
    } while (0)

// Variável global para indicar se um erro foi reportado
int error_reported = 0;

%}

// Declaração de uma união para armazenar diferentes tipos de valores de tokens
%union {
    int integer;         // Para armazenar valores inteiros
    double real;         // Para armazenar valores reais (ponto flutuante)
    char *string;        // Para armazenar strings
}

// Declaração dos tokens e seus tipos de valor
%token <real> TOKEN_NUMERO
%token <string> TOKEN_LITERAL
%token <string> TOKEN_IDENTIFICADOR
%token <string> TOKEN_OP_RELACIONAL
%token <string> TOKEN_OP_ARITMETICO

%token TOKEN_ATRIBUICAO TOKEN_ABRE_PAR TOKEN_FECHA_PAR TOKEN_VIRGULA TOKEN_PONTO_E_VIRG
%token TOKEN_INICIOPROG TOKEN_FIMPROG TOKEN_INICIOARGS TOKEN_FIMARGS
%token TOKEN_INICIOVARS TOKEN_FIMVARS TOKEN_ESCREVA TOKEN_SE TOKEN_ENTAO TOKEN_FIMSE TOKEN_ENQUANTO TOKEN_FACA TOKEN_FIMENQUANTO TOKEN_ERRO

// Definição da precedência dos operadores
%right TOKEN_ATRIBUICAO
%left TOKEN_OP_RELACIONAL
%left '+' '-'
%left '*' '/'

// Declaração dos tipos utilizados nas produções
%type <real> MATH_EXPR MATH_FACTOR BOOLEAN_EXPRESSION
%type <string> VAR_TYPE STRING_EXPRESSION
%type <real> NUMERIC_EXPRESSION
%type <string> EXPRESSION

// Declaração do símbolo inicial e configurações adicionais
%start PROGRAMA
%locations
%debug

%%

// Definição das produções da gramática
// Não-terminal PROGRAMA: Produção inicial
PROGRAMA:
    LISTA_FUNCOES {
        // Produção inicial: LISTA_FUNCOES
        print_production("PROGRAMA -> LISTA_FUNCOES");
    }
    ;

// Não-terminal LISTA_FUNCOES: Lista de funções
LISTA_FUNCOES:
    FUNCAO LISTA_FUNCOES {
        // Produção para lista de funções: uma função seguida de uma lista de funções
        print_production("LISTA_FUNCOES -> FUNCAO LISTA_FUNCOES");
    }
    | FUNCAO {
        // Produção para lista de funções: uma única função
        print_production("LISTA_FUNCOES -> FUNCAO");
    }
    ;

// Não-terminal FUNCAO: Definição de uma função
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
    | {
        print_production("FUNCAO -> epsilon");
    }
    ;

// Não-terminal FUNCAO_DECLARACAO: Declaração de função
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

// Não-terminal FUNCAO_NOME: Nome da função
FUNCAO_NOME:
    TOKEN_IDENTIFICADOR {
        // Nome da função: identificador
        print_production("FUNCAO_NOME -> TOKEN_IDENTIFICADOR");
    }
    ;

// Não-terminal FUNCAO_RETORNO: Retorno da função
FUNCAO_RETORNO:
    TOKEN_TIPO FUNCAO_RETORNO_TIPO {
        // Produção para tipo de retorno
        print_production("FUNCAO_RETORNO -> TOKEN_TIPO FUNCAO_RETORNO_TIPO");
    }
    | {
        // Retorno vazio (epsilon)
        print_production("FUNCAO_RETORNO -> epsilon");
    }
    ;

// Não-terminal FUNCAO_RETORNO_TIPO: Tipo de retorno da função
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
    ;

// Argumentos de Função
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

LISTA_IDENTIFICADORES:
    TOKEN_IDENTIFICADOR ',' LISTA_IDENTIFICADORES {
        print_production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR , LISTA_IDENTIFICADORES");
    }
    | TOKEN_IDENTIFICADOR {
        print_production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR");
    }
    ;

  // Corpo da Função
FUNCAO_CORPO:
    '{' LISTA_DECLARACOES '}' {
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
    TOKEN_LITERAL {
        print_production("ESCREVA_CORPO -> TOKEN_LITERAL");
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
    | {
        print_production("CHAMA_ARGS -> epsilon");
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

SE_DECLARACAO:
    TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO SENAO_BLOCO TOKEN_FIM_SE {
        print_production("SE_DECLARACAO -> TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO SENAO_BLOCO TOKEN_FIM_SE");
    }
    ;

SE_CABECALHO:
    '(' EXPRESSAO_BOOLEANA ')' TOKEN_ENTAO {
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
    TOKEN_ENQUANTO '(' EXPRESSAO_BOOLEANA ')' TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO {
        print_production("ENQUANTO_DECLARACAO -> TOKEN_ENQUANTO ( EXPRESSAO_BOOLEANA ) TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO");
    }
    ;

ENQUANTO_CORPO:
    FUNCAO_CORPO {
        print_production("ENQUANTO_CORPO -> FUNCAO_CORPO");
    }
    ;

ENQUANTO_DECLARACAO:
    TOKEN_ENQUANTO '(' EXPRESSAO_BOOLEANA ')' TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO {
        print_production("ENQUANTO_DECLARACAO -> TOKEN_ENQUANTO ( EXPRESSAO_BOOLEANA ) TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO");
    }
    ;

ENQUANTO_CORPO:
    FUNCAO_CORPO {
        print_production("ENQUANTO_CORPO -> FUNCAO_CORPO");
    }
    ;


ATRIBUICAO_DECLARACAO:
    TOKEN_IDENTIFICADOR '=' EXPRESSAO TOKEN_PONTO_E_VIRG {
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
    | '(' EXPRESSAO_MATEMATICA ')' {
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

// Implementação da função de tratamento de erros com localização
void yyerror_with_location(YYLTYPE *yylloc, const char *s) {
    // Imprime uma mensagem de erro com a localização do erro
    fprintf(stderr, "\033[1;33m\033[1mErro sintático na linha %d, coluna %d:\033[0m %s\n", yylloc->first_line, yylloc->last_column, s);
    fprintf(stderr, "\033[1;33mLinha do erro sintático:\033[0m \"%s\"\n\n", yylloc->text);
}

// Implementação da função para imprimir a produção utilizada
void print_production(const char* production) {
    if(verbose){
        // Imprime a produção utilizada e incrementa o contador de produções
        fprintf(stdout, "Produção utilizada: %s\n", production);
    }
    production_count++;
}