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
%token <string> TOKEN_STRING_LITERAL TOKEN_STRING_LITERAL_NEWLINE TOKEN_STRING_LITERAL_TAB
%token <string> TOKEN_IDENTIFICADOR
%token TOKEN_OP_RELACIONAL
%token <string> TOKEN_OP_ARITMETICO

%token TOKEN_ATRIBUICAO TOKEN_ABRE_PAR TOKEN_FECHA_PAR TOKEN_VIRGULA TOKEN_PONTO_E_VIRG
%token TOKEN_INICIOPROG TOKEN_FIMPROG TOKEN_INICIOARGS TOKEN_FIMARGS
%token TOKEN_INICIOVARS TOKEN_FIMVARS TOKEN_ESCREVA TOKEN_SE TOKEN_ENTAO TOKEN_FIMSE TOKEN_ENQUANTO TOKEN_FACA TOKEN_FIMENQUANTO TOKEN_ERRO

%token <string> TOKEN_LITERAL TOKEN_INTEIRO TOKEN_REAL

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
%start S
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
        // Produção para função: delimitadores de início e fim e declaração da função
        print_production("FUNCAO -> TOKEN_INICIO_FUNCAO FUNCAO_DECLARACAO TOKEN_FIM_FUNCAO");
    }
    | VAZIO {
        // Produção para função vazia (epsilon)
        print_production("FUNCAO -> epsilon");
    }
    ;

// Não-terminal FUNCAO_DECLARACAO: Declaração de função
FUNCAO_DECLARACAO:
    FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS FUNCAO_CORPO {
        // Declaração completa da função com nome, retorno, argumentos e corpo
        print_production("FUNCAO_DECLARACAO -> FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS FUNCAO_CORPO");
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
    | VAZIO {
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
    | TOKEN_LITERAL {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_LITERAL");
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