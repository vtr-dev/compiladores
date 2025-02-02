%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "syntactic.tab.h"
#include "position_manager.h"

extern int errors_number;

void append_and_advance(const char *text, int length) {
    line_append(text);
    col_advance(length);
}

void update_position_for_comment(const char *text, int length) {
    for (int i = 0; i < length; i++) {
        if (text[i] == '\n') {
            line_next();
        } else {
            line_append((char[]){text[i], '\0'});
            col_advance(1);
        }
    }
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
%option noinput nounput noyywrap
%%

funcao             { append_and_advance(yytext, yyleng); return TOKEN_INICIO_FUNCAO; } 
fimfuncao          { append_and_advance(yytext, yyleng); return TOKEN_FIM_FUNCAO; } 
chama              { append_and_advance(yytext, yyleng); return TOKEN_CHAMA; } 
retorna            { append_and_advance(yytext, yyleng); return TOKEN_RETORNA; } 
tipo               { append_and_advance(yytext, yyleng); return TOKEN_TIPO; } 
args               { append_and_advance(yytext, yyleng); return TOKEN_INICIO_ARGS; } 
fimargs            { append_and_advance(yytext, yyleng); return TOKEN_FIM_ARGS; } 
escreva            { append_and_advance(yytext, yyleng); return TOKEN_ESCREVA; } 
inteiro            { append_and_advance(yytext, yyleng); return TOKEN_INTEIRO; } 
real               { append_and_advance(yytext, yyleng); return TOKEN_REAL; } 
caractere          { append_and_advance(yytext, yyleng); return TOKEN_CARACTERE; }
literal            { append_and_advance(yytext, yyleng); return TOKEN_LITERAL; } 
se                 { append_and_advance(yytext, yyleng); return TOKEN_SE; } 
entao              { append_and_advance(yytext, yyleng); return TOKEN_ENTAO; } 
senao              { append_and_advance(yytext, yyleng); return TOKEN_SENAO; } 
fimse              { append_and_advance(yytext, yyleng); return TOKEN_FIM_SE; } 
enquanto           { append_and_advance(yytext, yyleng); return TOKEN_ENQUANTO; } 
faca               { append_and_advance(yytext, yyleng); return TOKEN_FACA; } 
fimenquanto        { append_and_advance(yytext, yyleng); return TOKEN_FIM_ENQUANTO; }                                  
{QUOTE}({D}|{L}|{S}|{WHITESPACE}|{TAB}|\\n)*{QUOTE} { append_and_advance(yytext, yyleng); yylval.string = strdup(yytext); return TOKEN_STRING_LITERAL; }
{WHITESPACE}       { append_and_advance(yytext, yyleng); } 
{TAB}              { append_and_advance(yytext, yyleng); }
[\r]               { append_and_advance(yytext, yyleng); }
[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)? { append_and_advance(yytext, yyleng);  yylval.string = strdup(yytext); return TOKEN_NUMERO; }
{L}({L}|{D}|{UNDERSCORE})* { append_and_advance(yytext, yyleng); yylval.string = strdup(yytext); return TOKEN_IDENTIFICADOR; }
\<|\>|>=|<=|==|<> { append_and_advance(yytext, yyleng); yylval.string = strdup(yytext); return TOKEN_OP_RELACIONAL; }
\+                { append_and_advance(yytext, yyleng); yylval.string = strdup(yytext); return TOKEN_SOMA; }
\-                { append_and_advance(yytext, yyleng); yylval.string = strdup(yytext); return TOKEN_SUB; }
\*                { append_and_advance(yytext, yyleng); yylval.string = strdup(yytext); return TOKEN_MULT; }
\/                { append_and_advance(yytext, yyleng); yylval.string = strdup(yytext); return TOKEN_DIVISAO; }
=                 { append_and_advance(yytext, yyleng); return TOKEN_ATRIBUICAO; }
\(                { append_and_advance(yytext, yyleng); return TOKEN_ABRE_PAR; }
\)                { append_and_advance(yytext, yyleng); return TOKEN_FECHA_PAR; }
\{({L}|{D}|{S}|{WHITESPACE}|{TAB})*\} {update_position_for_comment(yytext, yyleng);}
,                 { append_and_advance(yytext, yyleng); return TOKEN_VIRGULA; }
;                 { append_and_advance(yytext, yyleng); return TOKEN_PONTO_E_VIRG; }
@                 { append_and_advance(yytext, yyleng); return TOKEN_CHAMADA; }
{NEW_LINE}        { line_next(); }
.                 { 
                  fprintf(stderr, "\n🟣 Erro léxico - linha %d, coluna %d: %s\n\n", pos_line(), pos_col(), yytext); 
                  errors_number++;
                  col_advance(yyleng);
                }

%%