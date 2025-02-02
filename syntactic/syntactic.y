%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "scope_manager.h"
#include "semantic_utils.h"
#include "semantic_rules.h"
#include "semantic_translate.h"
#include "position_manager.h"

extern int yylex();
extern int errors_number;
extern int yylineno;
extern int verbose;
extern scope* current_scope;

#define YYLTYPE_IS_DECLARED 1

typedef struct YYLTYPE {
  int first_line;       
  int first_column;     
  int last_line;       
  int last_column;     
  char text[1024];    
} YYLTYPE;

void yyerror(const char *s);
void yyerror_detailed(const char *s);
void production(const char* production);

#define YYERROR_VERBOSE 1

// Usamos o ChatGPT para solucionar o problema de erro do Bison
#define YYLLOC_DEFAULT(Current, Rhs, N)                          \
  do {                                                          \
    if (N) {                                                    \
      (Current).first_line   = YYRHSLOC(Rhs, 1).first_line;       \
      (Current).first_column = YYRHSLOC(Rhs, 1).first_column;     \
      (Current).last_line    = YYRHSLOC(Rhs, N).last_line;      \
      (Current).last_column  = YYRHSLOC(Rhs, N).last_column;    \
    } else {                                                    \
      (Current).first_line   = (Current).last_line   =           \
        YYRHSLOC(Rhs, 0).last_line;                             \
      (Current).first_column = (Current).last_column =           \
        YYRHSLOC(Rhs, 0).last_column;                           \
    }                                                           \
    sprintf((Current).text, "%d", yylineno);                    \
  } while (0)

  int error_reported = 0;
  int id_while_block = 0;
  int id_if_block = 0;
  int id_bool_expr = 0;
  var_type current_declaracao_type = TYPE_UNDEFINED;
  var_type current_funcao_retorno = TYPE_UNDEFINED;
%}
%code requires {
  #include "utils.h"
  #include "hash_table.h"
  
    typedef struct {
        var_type type;
        char *name;
        symbol_kind kind;
        char *op_lex;
        char *term1_lex;
        char *term2_lex;
        symbol_kind term1_kind; 
        symbol_kind term2_kind;
        int id_bool_expr;
        int scope;
        char * assign_content;
        char *code;
    } semantic_info;

    typedef struct {
        int count;
        char **names;
        var_type type;
    } id_list_info;

    typedef struct {
        int param_count;
        var_type *param_types; 
        char **param_names;
    } func_info;
}

%union {
    int integer;
    double real;
    char *string;
    semantic_info semantic;
    id_list_info id_list;
    func_info func;
}


%token <string> TOKEN_NUMERO
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
%left TOKEN_SOMA TOKEN_SUB
%left TOKEN_MULT TOKEN_DIVISAO
%precedence TOKEN_IDENTIFICADOR

%type <string> FUNCAO_NOME TOKEN_SOMA TOKEN_SUB TOKEN_MULT TOKEN_DIVISAO VARIAVEL_DECLARACAO_IDENTIFICADOR

%type <id_list> LISTA_CHAMA_IDENTIFICADORES
%type <id_list> LISTA_IDENTIFICADORES VARIAVEL_DECLARACAO_CORPO

%type <func> FUNCAO_ARGS FUNCAO_ARGS_CORPO LISTA_ARGS ARG_DECLARACAO

%type <semantic> PROGRAMA LISTA_FUNCOES FUNCAO FUNCAO_DECLARACAO FUNCAO_RETORNO FUNCAO_RETORNO_TIPO
%type <semantic> TIPO_ARG OPERACAO_MATEMATICA
%type <semantic> FUNCAO_CORPO LISTA_DECLARACOES DECLARACAO
%type <semantic> ESCREVA_DECLARACAO ESCREVA_CORPO
%type <semantic> CHAMA_DECLARACAO CHAMADA_FUNCAO
%type <semantic> VARIAVEL_DECLARACAO VARIAVEL_TIPO
%type <semantic> RETORNA_DECLARACAO VALOR
%type <semantic> SE_DECLARACAO SENAO_SE_BLOCO SE_CORPO SE_LISTA_DECLARACOES SE_CORPO_DECLARACAO
%type <semantic> ENQUANTO_DECLARACAO ENQUANTO_CORPO
%type <semantic> ATRIBUICAO_DECLARACAO EXPRESSAO_MATEMATICA
%type <semantic> FATOR_MATEMATICO EXPRESSAO
%type <semantic> OPERACAO_BINARIA SINAL_MATEMATICO OPERACAO_UNARIA
%type <semantic> EXPRESSAO_BOOLEANA TERMO_BOOLEANO
%type <integer> ENQUANTO_CABECALHO SE_CABECALHO

%right TOKEN_ENTAO TOKEN_SENAO

%start PROGRAMA
%locations
%debug

%%

PROGRAMA:
  LISTA_FUNCOES {
    production("PROGRAMA -> LISTA_FUNCOES");
  };

LISTA_FUNCOES:
  FUNCAO LISTA_FUNCOES {
      production("LISTA_FUNCOES -> FUNCAO LISTA_FUNCOES");
  }
  | FUNCAO {
      production("LISTA_FUNCOES -> FUNCAO");
  }
  | error LISTA_FUNCOES {
      yyerrok;
      yyclearin;
  };

FUNCAO:
  TOKEN_INICIO_FUNCAO FUNCAO_DECLARACAO TOKEN_FIM_FUNCAO {
    production("FUNCAO -> TOKEN_INICIO_FUNCAO FUNCAO_DECLARACAO TOKEN_FIM_FUNCAO");
    exit_scope();
    translate_function_end();
    current_funcao_retorno = TYPE_UNDEFINED;
  }
  | TOKEN_INICIO_FUNCAO error TOKEN_FIM_FUNCAO {
    yyerrok;
    yyclearin;
    exit_scope();
    current_funcao_retorno = TYPE_UNDEFINED;
  };

FUNCAO_DECLARACAO:
  FUNCAO_INIT FUNCAO_CORPO {
    production("FUNCAO_DECLARACAO -> FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS FUNCAO_CORPO");
  
    var_type func_return_type = current_scope_return_type();
    semantic_rule_retorna_declaracao(func_return_type, current_funcao_retorno);
  }
  | error FUNCAO_CORPO { 
    yyerrok;
    yyclearin;
  };

FUNCAO_INIT:
  FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS {
    production("FUNCAO_INIT -> FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS");
    semantic_rule_funcao_declaracao($1, $2.type, $3.param_count, $3.param_types, yylineno);

    translate_function_declaration($1, $2.type, $3.param_names, $3.param_types, $3.param_count);
    
    free($3.param_types);
    for (int i = 0; i < $3.param_count; i++) {
        free($3.param_names[i]);
    }
    free($3.param_names);
  };

FUNCAO_NOME:
  TOKEN_IDENTIFICADOR {
    production("FUNCAO_NOME -> TOKEN_IDENTIFICADOR");
    $$ = $1;
  };

FUNCAO_RETORNO:
  TOKEN_TIPO FUNCAO_RETORNO_TIPO {
    production("FUNCAO_RETORNO -> TOKEN_TIPO FUNCAO_RETORNO_TIPO");
    $$.type = $2.type;
    enter_scope($2.type);
  }
  | {
    production("FUNCAO_RETORNO -> epsilon");
    $$.type = TYPE_UNDEFINED;
    enter_scope(TYPE_UNDEFINED);
  };

FUNCAO_RETORNO_TIPO:
  TOKEN_INTEIRO {
    production("FUNCAO_RETORNO_TIPO -> TOKEN_INTEIRO");
    $$.type = TYPE_INT;
  }
  | TOKEN_CARACTERE {
    production("FUNCAO_RETORNO_TIPO -> TOKEN_CARACTERE");
    $$.type = TYPE_CHAR;
  }
  | TOKEN_REAL {
    production("FUNCAO_RETORNO_TIPO -> TOKEN_REAL");
    $$.type = TYPE_REAL;
  }
  | TOKEN_LITERAL {
    production("FUNCAO_RETORNO_TIPO -> TOKEN_LITERAL");
    $$.type = TYPE_STRING;
  };

FUNCAO_ARGS:
  TOKEN_INICIO_ARGS FUNCAO_ARGS_CORPO TOKEN_FIM_ARGS {
    production("FUNCAO_ARGS -> FUNCAO_ARGS_CORPO");
    $$ = $2;
  }
  | {
    production("FUNCAO_ARGS -> epsilon");
    $$ = (func_info){ .param_count = 0, .param_types = NULL, .param_names = NULL };
  };

FUNCAO_ARGS_CORPO:
  LISTA_ARGS {
    production("FUNCAO_ARGS_CORPO -> LISTA_ARGS");
    $$ = $1;
  };

LISTA_ARGS:
  ARG_DECLARACAO LISTA_ARGS {
    production("LISTA_ARGS -> ARG_DECLARACAO LISTA_ARGS");
    $2.param_count += $1.param_count;

    $2.param_types = realloc($2.param_types, $2.param_count * sizeof(var_type));
    $2.param_names = realloc($2.param_names, $2.param_count * sizeof(char *));

    for (int i = 0; i < $1.param_count; i++) {
        $2.param_types[$2.param_count - $1.param_count + i] = $1.param_types[i];
        $2.param_names[$2.param_count - $1.param_count + i] = $1.param_names[i];
    }

    free($1.param_types);
    free($1.param_names);

    $$ = $2;
  }
  | ARG_DECLARACAO {
    production("LISTA_ARGS -> ARG_DECLARACAO");
    $$ = $1;
  };

ARG_DECLARACAO:
  TIPO_ARG LISTA_IDENTIFICADORES TOKEN_PONTO_E_VIRG {
    production("ARG_DECLARACAO -> TIPO_ARG LISTA_IDENTIFICADORES TOKEN_PONTO_E_VIRG");

    func_info arg_info;
    arg_info.param_count = $2.count;
    arg_info.param_types = malloc($2.count * sizeof(var_type));
    arg_info.param_names = malloc($2.count * sizeof(char *));

    for (int i = 0; i < $2.count; i++) {
        arg_info.param_types[i] = $1.type; 
        arg_info.param_names[i] = strdup($2.names[i]);
    }

    $$ = arg_info;
  }
  | error TOKEN_PONTO_E_VIRG {
      yyerrok;
      yyclearin;
  };

TIPO_ARG:
  VARIAVEL_TIPO {
    production("TIPO_ARG -> VARIAVEL_TIPO");
    $$ = $1;
  };

LISTA_IDENTIFICADORES:
  TOKEN_IDENTIFICADOR TOKEN_VIRGULA LISTA_IDENTIFICADORES {
    production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR TOKEN_VIRGULA LISTA_IDENTIFICADORES");
    $3.names = realloc($3.names, sizeof(char*) * ($3.count + 1));
    $3.names[$3.count++] = strdup($1);
    $$ = $3;
    semantic_rule_variavel_declaracao($1, current_declaracao_type, yylineno);
  }
  | TOKEN_IDENTIFICADOR {
    production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR");
    $$ = (id_list_info){.count = 1, .names = malloc(sizeof(char*))};
    $$.names[0] = strdup($1);
    semantic_rule_variavel_declaracao($1, current_declaracao_type, yylineno);
  };

FUNCAO_CORPO:
  LISTA_DECLARACOES {
    production("FUNCAO_CORPO -> LISTA_DECLARACOES");
  };

LISTA_DECLARACOES:
  DECLARACAO LISTA_DECLARACOES {
    production("LISTA_DECLARACOES -> DECLARACAO LISTA_DECLARACOES");
  }
  | DECLARACAO {
    production("LISTA_DECLARACOES -> DECLARACAO");
  };

DECLARACAO:
  ESCREVA_DECLARACAO
  | CHAMA_DECLARACAO
  | VARIAVEL_DECLARACAO
  | SE_DECLARACAO
  | ENQUANTO_DECLARACAO
  | ATRIBUICAO_DECLARACAO
  | RETORNA_DECLARACAO
  | error TOKEN_PONTO_E_VIRG {
      yyerrok;
      yyclearin;
  };

ESCREVA_DECLARACAO:
  TOKEN_ESCREVA ESCREVA_CORPO TOKEN_PONTO_E_VIRG {
    production("ESCREVA_DECLARACAO -> TOKEN_ESCREVA ESCREVA_CORPO TOKEN_PONTO_E_VIRG");
    translate_print($2.name, $2.kind);
  }
  | TOKEN_ESCREVA error TOKEN_PONTO_E_VIRG {
      yyerrok;
      yyclearin;
  };

ESCREVA_CORPO:
  TOKEN_STRING_LITERAL {
    production("ESCREVA_CORPO -> TOKEN_STRING_LITERAL");
    char *string_without_quotes = strdup($1 + 1);
    string_without_quotes[strlen(string_without_quotes) - 1] = '\0';
    $$ = (semantic_info){.type = TYPE_STRING, .name = string_without_quotes, .kind = SYMBOL_UNDEFINED, .scope = -1};
  }
  | TOKEN_IDENTIFICADOR {
    production("ESCREVA_CORPO -> TOKEN_IDENTIFICADOR");
    $$ = (semantic_info){.type = TYPE_UNDEFINED, .name = strdup($1), .kind = SYMBOL_VAR, .scope = -1};
  };

CHAMA_DECLARACAO:
  CHAMADA_FUNCAO TOKEN_PONTO_E_VIRG {
    production("CHAMA_DECLARACAO -> CHAMADA_FUNCAO TOKEN_PONTO_E_VIRG");
    write_with_indent($1.assign_content);
    translate_declaration_footer();
  }
  | TOKEN_CHAMA error TOKEN_PONTO_E_VIRG {
      yyerrok;
      yyclearin;
  };

CHAMADA_FUNCAO:
    TOKEN_CHAMA TOKEN_CHAMADA LISTA_CHAMA_IDENTIFICADORES {
        production("CHAMADA_FUNCAO -> TOKEN_CHAMA TOKEN_CHAMADA LISTA_CHAMA_IDENTIFICADORES");
        $$.type = semantic_rule_chamada_funcao($3.names, $3.count);
        $$.assign_content = translate_function_call($3.names, $3.count);
    }
    ;

LISTA_CHAMA_IDENTIFICADORES:
    TOKEN_IDENTIFICADOR LISTA_CHAMA_IDENTIFICADORES {
        production("LISTA_CHAMA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR LISTA_CHAMA_IDENTIFICADORES");
        $2.names = realloc($2.names, sizeof(char*) * ($2.count + 1));
        $2.names[$2.count++] = strdup($1);
        $$ = $2;
    }
    | TOKEN_IDENTIFICADOR {
        production("LISTA_CHAMA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR");
        $$ = (id_list_info){.count = 1, .names = malloc(sizeof(char*))};
        $$.names[0] = strdup($1);
    }
    ;


VARIAVEL_DECLARACAO:
  VARIAVEL_TIPO VARIAVEL_DECLARACAO_CORPO {
    production("VARIAVEL_DECLARACAO -> VARIAVEL_TIPO VARIAVEL_DECLARACAO_CORPO");
    translate_var_declaration($2.names, $1.type, $2.count);
  }
  | VARIAVEL_TIPO VARIAVEL_DECLARACAO_IDENTIFICADOR TOKEN_ATRIBUICAO EXPRESSAO TOKEN_PONTO_E_VIRG {
        production("VARIAVEL_DECLARACAO -> VARIAVEL_TIPO TOKEN_IDENTIFICADOR TOKEN_ATRIBUICAO EXPRESSAO TOKEN_PONTO_E_VIRG");
        semantic_rule_atribuicao($2, $4.type);
        
        translate_assignment($2, $1.type, $4.assign_content);
        translate_declaration_footer();
    }
  ;

VARIAVEL_DECLARACAO_IDENTIFICADOR:
  TOKEN_IDENTIFICADOR {
    semantic_rule_variavel_declaracao($1, current_declaracao_type, yylineno);
    $$ = $1;
  };

VARIAVEL_DECLARACAO_CORPO:
    LISTA_IDENTIFICADORES TOKEN_PONTO_E_VIRG {
        production("VARIAVEL_DECLARACAO_CORPO -> LISTA_IDENTIFICADORES TOKEN_PONTO_E_VIRG");
        $$ = $1;
    }
    | error TOKEN_PONTO_E_VIRG {
        yyerrok;
        yyclearin;
        $$ = (id_list_info){.count = 0, .names = NULL};
    }
    ;

VARIAVEL_TIPO:
  TOKEN_INTEIRO {
    $$.type = TYPE_INT;
    current_declaracao_type = TYPE_INT;
    production("VARIAVEL_TIPO -> TOKEN_INTEIRO");
  }
  | TOKEN_REAL {
    $$.type = TYPE_REAL;
    current_declaracao_type = TYPE_REAL;
    production("VARIAVEL_TIPO -> TOKEN_REAL");
  }
  | TOKEN_CARACTERE {
    $$.type = TYPE_CHAR;
    current_declaracao_type = TYPE_CHAR;
    production("VARIAVEL_TIPO -> TOKEN_CARACTERE");
  }
  | TOKEN_LITERAL {
    $$.type = TYPE_STRING;
    current_declaracao_type = TYPE_STRING;
    production("VARIAVEL_TIPO -> TOKEN_LITERAL");
  };


RETORNA_DECLARACAO:
    TOKEN_RETORNA EXPRESSAO TOKEN_PONTO_E_VIRG {
        production("RETORNA_DECLARACAO -> TOKEN_RETORNA RETORNA_CORPO TOKEN_PONTO_E_VIRG");
        var_type func_return_type = current_scope_return_type();
        current_funcao_retorno = $2.type;
        semantic_rule_retorna_declaracao(func_return_type, current_funcao_retorno);
        translate_return($2.assign_content);
    }
    | TOKEN_RETORNA error TOKEN_PONTO_E_VIRG {
        yyerrok;
        yyclearin;
    }
    ;

VALOR:
    TOKEN_NUMERO {
        production("VALOR -> TOKEN_NUMERO");
        var_type type = is_integer($1) ? TYPE_INT : TYPE_REAL;
        $$ = (semantic_info){.type = type, .name = $1, .kind = SYMBOL_UNDEFINED, .scope = -1, .assign_content = translate_constant($1)};
    }
    | TOKEN_STRING_LITERAL {
        production("VALOR -> TOKEN_STRING_LITERAL");
        char * str_value = translate_string($1);

        if(str_value == NULL) {
          yyerror("Linguagem não oferece suporte a literal com tamanho maior que 1 para atribuição");
        }

        $$ = (semantic_info){.type = TYPE_CHAR, .name = str_value, .kind = SYMBOL_UNDEFINED, .scope = -1, .assign_content = translate_constant(str_value)};
    }
    ;

SE_DECLARACAO:
    TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO {
        production("SE_DECLARACAO -> TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO");
        translate_if_footer($2);
    }
    | TOKEN_SE error TOKEN_FIM_SE {
        yyerrok;
        yyclearin;
    }
    ;

SE_CABECALHO:
  TOKEN_ABRE_PAR EXPRESSAO_BOOLEANA TOKEN_FECHA_PAR TOKEN_ENTAO {
    production("SE_CABECALHO -> TOKEN_ABRE_PAR EXPRESSAO_BOOLEANA TOKEN_FECHA_PAR TOKEN_ENTAO");
    $$ = id_if_block;
    translate_if_header($2.term1_lex, $2.term1_kind, $2.term2_lex, $2.term2_kind, $2.type, $2.op_lex, id_if_block, $2.id_bool_expr);
    id_if_block++;
  }
  | TOKEN_ABRE_PAR error TOKEN_FIM_SE {
      yyerrok;
      yyclearin;
  };

SENAO_SE_BLOCO: 
  TOKEN_SENAO TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO {
    production("SENAO_SE_BLOCO ->  TOKEN_SENAO TOKEN_SE  SE_CABECALHO SE_CORPO SENAO_SE_BLOCO");
  }
  | TOKEN_SENAO SE_CORPO TOKEN_FIM_SE {
    production("SENAO_SE_BLOCO -> TOKEN_SENAO SE_CORPO TOKEN_FIM_SE");
  }
  | TOKEN_FIM_SE {
    production("SENAO_SE_BLOCO -> TOKEN_FIM_SE");
  }
  | TOKEN_SENAO TOKEN_SE error TOKEN_FIM_SE {
      yyerrok;
      yyclearin;
  }
  | TOKEN_SENAO error TOKEN_FIM_SE {
      yyerrok;
      yyclearin;
  };

SE_CORPO:
  SE_LISTA_DECLARACOES {
    production("SE_CORPO -> SE_LISTA_DECLARACOES");
  };

SE_LISTA_DECLARACOES:
  SE_CORPO_DECLARACAO SE_LISTA_DECLARACOES {
    production("SE_LISTA_DECLARACOES -> SE_CORPO_DECLARACAO SE_LISTA_DECLARACOES");
  }
  | SE_CORPO_DECLARACAO {
    production("SE_LISTA_DECLARACOES -> SE_CORPO_DECLARACAO");
  };

SE_CORPO_DECLARACAO:
  ESCREVA_DECLARACAO
  | CHAMA_DECLARACAO
  | VARIAVEL_DECLARACAO
  | ENQUANTO_DECLARACAO
  | ATRIBUICAO_DECLARACAO
  | RETORNA_DECLARACAO
  | error TOKEN_PONTO_E_VIRG {
      yyerrok;
      yyclearin;
  };


ENQUANTO_DECLARACAO:
  ENQUANTO_CABECALHO ENQUANTO_CORPO TOKEN_FIM_ENQUANTO {
    production("ENQUANTO_DECLARACAO -> TOKEN_ENQUANTO TOKEN_ABRE_PAR EXPRESSAO_BOOLEANA TOKEN_FECHA_PAR TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO");
    exit_scope();
    translate_while_footer($1);
  }
  | error TOKEN_FIM_ENQUANTO {
      exit_scope();
      yyerrok;
      yyclearin;
  };

ENQUANTO_CABECALHO: 
  TOKEN_ENQUANTO TOKEN_ABRE_PAR EXPRESSAO_BOOLEANA TOKEN_FECHA_PAR TOKEN_FACA {
    $$ = id_while_block;
    translate_while_header($3.term1_lex, $3.term1_kind, $3.term2_lex, $3.term2_kind, $3.type, $3.op_lex, id_while_block, $3.id_bool_expr);
    id_while_block++;
    enter_scope(TYPE_UNDEFINED);
}

ENQUANTO_CORPO:
  FUNCAO_CORPO {
    production("ENQUANTO_CORPO -> FUNCAO_CORPO");
  };

ATRIBUICAO_DECLARACAO:
    TOKEN_IDENTIFICADOR TOKEN_ATRIBUICAO EXPRESSAO TOKEN_PONTO_E_VIRG {
        production("ATRIBUICAO_DECLARACAO -> TOKEN_IDENTIFICADOR TOKEN_ATRIBUICAO EXPRESSAO TOKEN_PONTO_E_VIRG");
        semantic_rule_atribuicao($1, $3.type);
        translate_assignment($1, $3.type, $3.assign_content);
        translate_declaration_footer();
    }
    | TOKEN_IDENTIFICADOR error TOKEN_PONTO_E_VIRG {
        yyerrok;
        yyclearin;
    }
    ;

EXPRESSAO:
    CHAMADA_FUNCAO {
        production("EXPRESSAO -> CHAMADA_FUNCAO");
        $$ = $1;
    }
    | TOKEN_IDENTIFICADOR {
        production("EXPRESSAO -> TOKEN_IDENTIFICADOR");
        semantic_rule_var_existe($1);
        node *symbol = lookup_symbol_scope($1);
        $$ = (semantic_info){.type = get_symbol_type(symbol), .name = strdup($1), .kind = SYMBOL_VAR, .scope = -1, .assign_content = strdup($1)};
    }
    | EXPRESSAO_MATEMATICA {
        production("EXPRESSAO -> EXPRESSAO_MATEMATICA");
        $$ = $1;
    }
    | VALOR {
        production("EXPRESSAO -> VALOR");
        $$ = $1;
    }
    ;

EXPRESSAO_MATEMATICA:
    OPERACAO_BINARIA {
        production("EXPRESSAO_MATEMATICA -> OPERACAO_BINARIA");
      
        $$ = $1;
        $$.code = strdup($1.code);
        $$.assign_content = translate_bril_from_postfix($1.code, $1.type);
    }
    | OPERACAO_UNARIA {
        production("EXPRESSAO_MATEMATICA -> OPERACAO_UNARIA");
        $$ = $1;
        $$.code = strdup($1.code);
        $$.assign_content = translate_bril_from_postfix($1.code, $1.type);
    }
    ;


OPERACAO_BINARIA:
    FATOR_MATEMATICO OPERACAO_MATEMATICA EXPRESSAO_MATEMATICA {
        production("OPERACAO_BINARIA -> FATOR_MATEMATICO OPERACAO_MATEMATICA EXPRESSAO_MATEMATICA");
        $$.type = semantic_rule_operacao_binaria($1.type, $3.type);
        $$.code = combine_postfix($1.code, $3.code, $2.code); 
    }
    | FATOR_MATEMATICO OPERACAO_MATEMATICA FATOR_MATEMATICO {
        production("OPERACAO_BINARIA -> FATOR_MATEMATICO OPERACAO_MATEMATICA FATOR_MATEMATICO");
        $$.type = semantic_rule_operacao_binaria($1.type, $3.type);
        $$.code = combine_postfix($1.code, $3.code, $2.code); 
    }
    ;

OPERACAO_MATEMATICA: 
    TOKEN_SOMA {
      production("OPERACAO_MATEMATICA -> TOKEN_SOMA");
      $$.code = strdup("+");
    }
    | TOKEN_SUB {
        production("OPERACAO_MATEMATICA -> TOKEN_SUB");
        $$.code = strdup("-");
    }
    | TOKEN_MULT {
        production("OPERACAO_MATEMATICA -> TOKEN_MULT");
        $$.code = strdup("*");
    }
    | TOKEN_DIVISAO {
        production("OPERACAO_MATEMATICA -> TOKEN_DIVISAO");
        $$.code = strdup("/");
    }
    ;
  
OPERACAO_UNARIA:
    SINAL_MATEMATICO FATOR_MATEMATICO {
        production("OPERACAO_UNARIA -> SINAL_MATEMATICO FATOR_MATEMATICO");
        $$ = $2;
        if (strcmp($1.code, "-") == 0) {
            $$.code = combine_unary_postfix($2.code, "~");
        } else {
            $$.code = strdup($2.code);
        }
        $$.type = $2.type;
    }
    ;

SINAL_MATEMATICO:
    TOKEN_SOMA {
        production("SINAL_MATEMATICO -> TOKEN_SOMA");
        $$.code = strdup("+");
    }
    | TOKEN_SUB {
        production("SINAL_MATEMATICO -> TOKEN_SUB");
        $$.code = strdup("-");
    }
    ;

FATOR_MATEMATICO:
    TOKEN_IDENTIFICADOR {
        production("FATOR_MATEMATICO -> TOKEN_IDENTIFICADOR");
        semantic_rule_var_existe($1);
        node *symbol = lookup_symbol_scope($1);
        $$.type = get_symbol_type(symbol);
        $$.code = strdup($1); 
    }
    | TOKEN_NUMERO {
        production("FATOR_MATEMATICO -> TOKEN_NUMERO");
        var_type type = is_integer($1) ? TYPE_INT : TYPE_REAL;
        $$.type = type;
        $$.code = strdup($1); 
    }
    | TOKEN_ABRE_PAR EXPRESSAO_MATEMATICA TOKEN_FECHA_PAR {
        production("FATOR_MATEMATICO -> TOKEN_ABRE_PAR EXPRESSAO_MATEMATICA TOKEN_FECHA_PAR");
        $$ = $2;
        $$.type = $2.type;
        $$.code = strdup($2.code);
    }
    ;

EXPRESSAO_BOOLEANA:
    TERMO_BOOLEANO TOKEN_OP_RELACIONAL TERMO_BOOLEANO {
        production("EXPRESSAO_BOOLEANA -> TERMO_BOOLEANO TOKEN_OP_RELACIONAL TERMO_BOOLEANO");
        $$.type = semantic_rule_expressao_booleana($1.type, $3.type);
        $$ = (semantic_info){.type = $$.type, .term1_lex = strdup($1.name), .term1_kind = $1.kind, .term2_lex = strdup($3.name), .term2_kind = $3.kind, .op_lex = strdup($2), .id_bool_expr = id_bool_expr};
        id_bool_expr++;
    } 
    ;


TERMO_BOOLEANO:
    TOKEN_IDENTIFICADOR {
        production("TERMO_BOOLEANO -> TOKEN_IDENTIFICADOR");
        semantic_rule_var_existe($1);
        node *symbol = lookup_symbol_scope($1);
        $$ = (semantic_info){.type = get_symbol_type(symbol), .name = strdup($1), .kind = SYMBOL_VAR, .scope = -1};
    }
    | VALOR {
        production("TERMO_BOOLEANO -> VALOR");
        $$ = $1;
    }
    ;
%%

void yyerror(const char *s) {
  YYLTYPE yylloc;
  yylloc.first_line = yylloc.last_line = yylineno;
  yylloc.first_column = yylloc.last_column = col_num;
  sprintf(yylloc.text, "%d", yylineno);
  yyerror_detailed(s);
  errors_number++;
}

void yyerror_detailed(const char *s) {
  fprintf(stderr, "\n🟠 Erro sintático - linha %d, coluna %d: %s\n", line_num, col_num, s);
  fprintf(stderr, "~> Linha do erro: \"%s\"\n\n", line_text);
}

void production(const char* production) {
  if(verbose){
    fprintf(stdout, "PRODUCAO: %s | LINHA: %d\n", production, yylineno);
  }
}
