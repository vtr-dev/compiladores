/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_NUMERO = 258,
     TOKEN_STRING_LITERAL = 259,
     TOKEN_IDENTIFICADOR = 260,
     TOKEN_OP_RELACIONAL = 261,
     TOKEN_OP_ARITMETICO = 262,
     TOKEN_ATRIBUICAO = 263,
     TOKEN_ABRE_PAR = 264,
     TOKEN_FECHA_PAR = 265,
     TOKEN_VIRGULA = 266,
     TOKEN_PONTO_E_VIRG = 267,
     TOKEN_INICIO_FUNCAO = 268,
     TOKEN_FIM_FUNCAO = 269,
     TOKEN_INICIO_ARGS = 270,
     TOKEN_FIM_ARGS = 271,
     TOKEN_ESCREVA = 272,
     TOKEN_SE = 273,
     TOKEN_ENTAO = 274,
     TOKEN_SENAO = 275,
     TOKEN_FIM_SE = 276,
     TOKEN_ENQUANTO = 277,
     TOKEN_FACA = 278,
     TOKEN_FIM_ENQUANTO = 279,
     TOKEN_ERRO = 280,
     TOKEN_CHAMA = 281,
     TOKEN_CHAMADA = 282,
     TOKEN_RETORNA = 283,
     TOKEN_TIPO = 284,
     TOKEN_INTEIRO = 285,
     TOKEN_REAL = 286,
     TOKEN_CARACTERE = 287,
     TOKEN_LITERAL = 288,
     TOKEN_SOMA = 289,
     TOKEN_SUB = 290,
     TOKEN_MULT = 291,
     TOKEN_DIVISAO = 292,
     TOKE_SUB = 293
   };
#endif
/* Tokens.  */
#define TOKEN_NUMERO 258
#define TOKEN_STRING_LITERAL 259
#define TOKEN_IDENTIFICADOR 260
#define TOKEN_OP_RELACIONAL 261
#define TOKEN_OP_ARITMETICO 262
#define TOKEN_ATRIBUICAO 263
#define TOKEN_ABRE_PAR 264
#define TOKEN_FECHA_PAR 265
#define TOKEN_VIRGULA 266
#define TOKEN_PONTO_E_VIRG 267
#define TOKEN_INICIO_FUNCAO 268
#define TOKEN_FIM_FUNCAO 269
#define TOKEN_INICIO_ARGS 270
#define TOKEN_FIM_ARGS 271
#define TOKEN_ESCREVA 272
#define TOKEN_SE 273
#define TOKEN_ENTAO 274
#define TOKEN_SENAO 275
#define TOKEN_FIM_SE 276
#define TOKEN_ENQUANTO 277
#define TOKEN_FACA 278
#define TOKEN_FIM_ENQUANTO 279
#define TOKEN_ERRO 280
#define TOKEN_CHAMA 281
#define TOKEN_CHAMADA 282
#define TOKEN_RETORNA 283
#define TOKEN_TIPO 284
#define TOKEN_INTEIRO 285
#define TOKEN_REAL 286
#define TOKEN_CARACTERE 287
#define TOKEN_LITERAL 288
#define TOKEN_SOMA 289
#define TOKEN_SUB 290
#define TOKEN_MULT 291
#define TOKEN_DIVISAO 292
#define TOKE_SUB 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 64 "syntactic/syntactic.y"
{
    int integer;         // Para armazenar valores inteiros
    double real;         // Para armazenar valores reais (ponto flutuante)
    char *string;        // Para armazenar strings
}
/* Line 1529 of yacc.c.  */
#line 131 "syntactic/syntactic.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
