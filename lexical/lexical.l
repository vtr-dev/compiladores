%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"
#include "syntactic.tab.h"

extern hash_table *ht;
extern int current_column;
extern char current_line[1024];
extern FILE *yyin;

void clear_current_line() {
  current_line[0] = '\0';
}

void append_to_current_line(const char *text) {
  strcat(current_line, text);
}

%}

D [0-9]
L [a-zA-Z]
S [~\`!@#\$%^&*()_\-+\[\]{}|‘?><.\=,]

WHITESPACE [ ]
NEW_LINE [\n]
TAB [\t]
UNDERSCORE [_]
QUOTE \"

%option yylineno
%x COMMENT

%%

funcao                                                  { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_INICIO_FUNCAO; } 
fimfuncao                                                { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_FIM_FUNCAO; } 
chama                                                   { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_CHAMA; } 
retorna                                                 { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_RETORNA; } 
tipo                                                    { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_TIPO; } 
args                                                    { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_INICIO_ARGS; } 
fimargs                                                  { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext);  current_column += yyleng; return TOKEN_FIM_ARGS; } 
escreva                                                 { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_ESCREVA; } 
inteiro                                                 { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_INTEIRO; } 
real                                                    { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_REAL; } 
caractere                                               { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_CARACTERE; }
literal                                                 { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_LITERAL; } 
se                                                      { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_SE; } 
entao                                                   { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_ENTAO; } 
senao                                                   { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_SENAO; } 
fimse                                                    { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext);  current_column += yyleng; return TOKEN_FIM_SE; } 
enquanto                                                { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_ENQUANTO; } 
faca                                                    { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_FACA; } 
fimenquanto                                              { insert(ht, yytext, yytext, yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_FIM_ENQUANTO; }                                  
{QUOTE}({D}|{L}|{S}|{WHITESPACE}|{TAB}|\\n)*{QUOTE}     { insert(ht, yytext, "string_literal", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_STRING_LITERAL; }
{WHITESPACE}                                            { append_to_current_line(yytext); current_column += 1; } 
{TAB}                                                   { append_to_current_line(yytext); current_column += yyleng; }
[\r]                                                    { append_to_current_line(yytext); current_column += yyleng; }
[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?                     { insert(ht, yytext, "numero", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_NUMERO; }
{L}({L}|{D}|{UNDERSCORE})*                              { insert(ht, yytext, "id_ou_funcao", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_IDENTIFICADOR; }
\<|\>|>=|<=|==|<>                                       { insert(ht, yytext, "op_relacional", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_OP_RELACIONAL; }
\+                                                      { insert(ht, yytext, "op_aritmetico", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_SOMA; }
\-                                                      { insert(ht, yytext, "op_aritmetico", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_SUB; }
\*                                                      { insert(ht, yytext, "op_aritmetico", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_MULT; }
\/                                                      { insert(ht, yytext, "op_aritmetico", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_DIVISAO; }
=                                                       { insert(ht, yytext, "atribuicao", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_ATRIBUICAO;}
\(                                                      { insert(ht, yytext, "abre_par", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_ABRE_PAR; }
\)                                                      { insert(ht, yytext, "fecha_par", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_FECHA_PAR; }
\{({L}|{D}|{S}|{WHITESPACE}|{TAB})*\}                   { insert(ht, yytext, "comentario", yylineno);}
,                                                       { insert(ht, yytext, "virgula", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_VIRGULA; }
;                                                       { insert(ht, yytext, "ponto_e_virg", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_PONTO_E_VIRG; }
@                                                       { insert(ht, yytext, "chamada", yylineno); append_to_current_line(yytext); current_column += yyleng; return TOKEN_CHAMADA; }
{NEW_LINE}                                              { current_column = 1; clear_current_line(); }
.                                                       { fprintf(stderr, "~> Erro léxico - linha %d, coluna %d: %s\n", yylineno, current_column, yytext); }

%%
