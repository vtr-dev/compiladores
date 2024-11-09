D [0-9]
L [a-zA-Z]
S [~\`!@#\$%^&*()_\-+\[\]{}|‘?><.\=,]

KEYWORDS funcao|fimfuncao|chama|retorna|tipo|args|fimargs|escreva|inteiro|real|caractere|se|entao|senao|fimse|enquanto|faca|fimenquanto

WHITESPACE [ ]
NEW_LINE [\n]
TAB [\t]
UNDERSCORE [_]
QUOTE \"

%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "hash_table.h"
extern hash_table *ht;

%}

%option yylineno
%x COMMENT

%%

{KEYWORDS}                                              { insert(ht, yytext, yytext, yylineno); } 
{QUOTE}({D}|{L}|{S}|{WHITESPACE}|{TAB}|\\n)*{QUOTE}     { insert(ht, yytext, "literal", yylineno); return "TOKEN_LITERAL"; }
({WHITESPACE}|{TAB}|[\r]|{NEW_LINE})+                   { insert(ht, yytext, "vazio", yylineno);}
[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?                     { insert(ht, yytext, "numero", yylineno); return "TOKEN_NUMERO"; }
{L}({L}|{D}|{UNDERSCORE})*                              { insert(ht, yytext, "id_ou_funcao", yylineno); }
\<|\>|>=|<=|==|<>                                       { insert(ht, yytext, "op_relacional", yylineno); return "TOKEN_OP_RELACIONAL"; }
\+|\-|\*|\/                                             { insert(ht, yytext, "op_aritmetico", yylineno); return "TOKEN_OP_ARITMETICO"; }
=                                                       { insert(ht, yytext, "atribuicao", yylineno); return "TOKEN_OP_ATRIBUICAO";}
\(                                                      { insert(ht, yytext, "abre_par", yylineno); return "TOKEN_ABRE_PAR"; }
\)                                                      { insert(ht, yytext, "fecha_par", yylineno); return "TOKEN_FECHA_PAR"; }
\{({L}|{D}|{S}|{WHITESPACE}|{TAB})*\}                   { insert(ht, yytext, "comentario", yylineno);}
,                                                       { insert(ht, yytext, "virgula", yylineno); return "TOKEN_VIRGULA"; }
;                                                       { insert(ht, yytext, "ponto_e_virg", yylineno); return "TOKEN_PONTO_E_VIRG"; }
@                                                       { insert(ht, yytext, "chamada", yylineno); }
.                                                       { printf("(%d,ERROR,\"%s\")\n", yylineno, yytext); }

%%
