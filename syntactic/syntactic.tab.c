/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "syntactic/syntactic.y"

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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 64 "syntactic/syntactic.y"
{
    int integer;         // Para armazenar valores inteiros
    double real;         // Para armazenar valores reais (ponto flutuante)
    char *string;        // Para armazenar strings
}
/* Line 193 of yacc.c.  */
#line 240 "syntactic/syntactic.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 265 "syntactic/syntactic.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   113

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    14,    18,    21,    22,
      27,    30,    32,    35,    36,    38,    40,    42,    44,    46,
      47,    49,    52,    54,    57,    59,    63,    65,    67,    70,
      72,    74,    76,    78,    80,    82,    84,    86,    90,    92,
      94,   100,   103,   105,   106,   109,   112,   114,   116,   118,
     120,   122,   126,   128,   130,   132,   134,   141,   146,   151,
     152,   155,   156,   158,   166,   168,   173,   175,   177,   179,
     181,   184,   186,   189,   192,   195,   197,   200,   203,   206,
     208,   210,   211,   213,   215,   219,   223,   225
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    41,    -1,    42,    41,    -1,    42,    -1,
      13,    43,    14,    -1,    13,    43,     1,    -1,     1,    14,
      -1,    -1,    44,    45,    47,    53,    -1,     1,    53,    -1,
       5,    -1,    29,    46,    -1,    -1,    30,    -1,    32,    -1,
      31,    -1,    33,    -1,    48,    -1,    -1,    49,    -1,    50,
      49,    -1,    50,    -1,    51,    52,    -1,    62,    -1,     5,
      11,    52,    -1,     5,    -1,    54,    -1,    55,    54,    -1,
      55,    -1,    56,    -1,    58,    -1,    60,    -1,    66,    -1,
      71,    -1,    73,    -1,    63,    -1,    17,    57,    12,    -1,
       4,    -1,     5,    -1,    26,    27,     5,    59,    12,    -1,
       5,    59,    -1,     5,    -1,    -1,    62,    61,    -1,     5,
      12,    -1,    73,    -1,    30,    -1,    31,    -1,    32,    -1,
      33,    -1,    28,    64,    12,    -1,     5,    -1,    65,    -1,
       3,    -1,     4,    -1,    18,    67,    70,    68,    69,    21,
      -1,     9,    82,    10,    19,    -1,    20,    18,    67,    70,
      -1,    -1,    20,    70,    -1,    -1,    53,    -1,    22,     9,
      82,    10,    23,    72,    24,    -1,    53,    -1,     5,     8,
      74,    12,    -1,    58,    -1,     5,    -1,    75,    -1,    65,
      -1,    77,    76,    -1,    77,    -1,    34,    75,    -1,    35,
      75,    -1,    79,    78,    -1,    79,    -1,    36,    77,    -1,
      37,    77,    -1,    80,    81,    -1,    34,    -1,    35,    -1,
      -1,     5,    -1,     3,    -1,     9,    75,    10,    -1,    83,
       6,    83,    -1,     5,    -1,    65,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   114,   118,   126,   129,   134,   139,   146,
     149,   158,   166,   170,   178,   181,   184,   187,   194,   197,
     203,   209,   212,   218,   224,   229,   232,   239,   245,   248,
     254,   255,   256,   257,   258,   259,   260,   264,   270,   273,
     279,   285,   288,   291,   297,   303,   306,   312,   315,   318,
     321,   327,   333,   336,   342,   345,   350,   356,   362,   365,
     371,   374,   380,   386,   392,   399,   405,   406,   407,   408,
     413,   416,   422,   425,   431,   434,   440,   443,   449,   455,
     458,   461,   467,   470,   473,   480,   486,   489
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_NUMERO", "TOKEN_STRING_LITERAL",
  "TOKEN_IDENTIFICADOR", "TOKEN_OP_RELACIONAL", "TOKEN_OP_ARITMETICO",
  "TOKEN_ATRIBUICAO", "TOKEN_ABRE_PAR", "TOKEN_FECHA_PAR", "TOKEN_VIRGULA",
  "TOKEN_PONTO_E_VIRG", "TOKEN_INICIO_FUNCAO", "TOKEN_FIM_FUNCAO",
  "TOKEN_INICIO_ARGS", "TOKEN_FIM_ARGS", "TOKEN_ESCREVA", "TOKEN_SE",
  "TOKEN_ENTAO", "TOKEN_SENAO", "TOKEN_FIM_SE", "TOKEN_ENQUANTO",
  "TOKEN_FACA", "TOKEN_FIM_ENQUANTO", "TOKEN_ERRO", "TOKEN_CHAMA",
  "TOKEN_CHAMADA", "TOKEN_RETORNA", "TOKEN_TIPO", "TOKEN_INTEIRO",
  "TOKEN_REAL", "TOKEN_CARACTERE", "TOKEN_LITERAL", "TOKEN_SOMA",
  "TOKEN_SUB", "TOKEN_MULT", "TOKEN_DIVISAO", "TOKE_SUB", "$accept",
  "PROGRAMA", "LISTA_FUNCOES", "FUNCAO", "FUNCAO_DECLARACAO",
  "FUNCAO_NOME", "FUNCAO_RETORNO", "FUNCAO_RETORNO_TIPO", "FUNCAO_ARGS",
  "FUNCAO_ARGS_CORPO", "LISTA_ARGS", "ARG_DECLARACAO", "TIPO_ARG",
  "LISTA_IDENTIFICADORES", "FUNCAO_CORPO", "LISTA_DECLARACOES",
  "DECLARACAO", "ESCREVA_DECLARACAO", "ESCREVA_CORPO", "CHAMA_DECLARACAO",
  "CHAMA_ARGS", "VARIAVEL_DECLARACAO", "VARIAVEL_DECLARACAO_CORPO",
  "VARIAVEL_TIPO", "RETORNA_DECLARACAO", "RETORNA_CORPO", "VALOR",
  "SE_DECLARACAO", "SE_CABECALHO", "SENAO_SE_BLOCO", "SENAO_BLOCO",
  "SE_CORPO", "ENQUANTO_DECLARACAO", "ENQUANTO_CORPO",
  "ATRIBUICAO_DECLARACAO", "EXPRESSAO", "EXPRESSAO_MATEMATICA",
  "EXPRESSAO_SOMA_SUB", "TERMO_MATEMATICO", "EXPRESSAO_MULT_DIV",
  "FATOR_MATEMATICO", "SINAL_MATEMATICO", "FATOR_PRIMARIO_MATEMATICO",
  "EXPRESSAO_BOOLEANA", "TERMO_BOOLEANO", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    42,    43,
      43,    44,    45,    45,    46,    46,    46,    46,    47,    47,
      48,    49,    49,    50,    51,    52,    52,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    56,    57,    57,
      58,    59,    59,    59,    60,    61,    61,    62,    62,    62,
      62,    63,    64,    64,    65,    65,    66,    67,    68,    68,
      69,    69,    70,    71,    72,    73,    74,    74,    74,    74,
      75,    75,    76,    76,    77,    77,    78,    78,    79,    80,
      80,    80,    81,    81,    81,    82,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     3,     3,     2,     0,     4,
       2,     1,     2,     0,     1,     1,     1,     1,     1,     0,
       1,     2,     1,     2,     1,     3,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       5,     2,     1,     0,     2,     2,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     1,     6,     4,     4,     0,
       2,     0,     1,     7,     1,     4,     1,     1,     1,     1,
       2,     1,     2,     2,     2,     1,     2,     2,     2,     1,
       1,     0,     1,     1,     3,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     7,     0,    11,     0,
      13,     1,     3,     0,     0,     0,     0,     0,     0,    47,
      48,    49,    50,    10,    27,    29,    30,    31,    32,     0,
      36,    33,    34,    35,     6,     5,     0,    19,    81,    38,
      39,     0,     0,     0,     0,     0,    54,    55,    52,     0,
      53,    28,     0,    44,    46,    14,    16,    15,    17,    12,
       0,    18,    20,    22,     0,    24,    67,    79,    80,    66,
      69,     0,    68,    71,    75,     0,    37,    86,    87,     0,
       0,    62,    59,     0,    43,    51,    45,     9,    21,    26,
      23,    65,    81,    81,    70,    81,    81,    74,    83,    82,
      81,    78,     0,     0,     0,    61,     0,    42,     0,     0,
      72,    73,    76,    77,     0,    57,    85,     0,     0,     0,
       0,    41,    40,    25,    84,     0,    60,    56,    64,     0,
      58,    63
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     9,    10,    37,    59,    60,    61,
      62,    63,    64,    90,    81,    24,    25,    26,    41,    27,
     108,    28,    53,    29,    30,    49,    78,    31,    43,   105,
     119,    82,    32,   129,    33,    71,    72,    94,    73,    97,
      74,    75,   101,    79,    80
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -105
static const yytype_int8 yypact[] =
{
       9,    -8,    42,    18,  -105,    15,  -105,     8,  -105,     3,
      -9,  -105,  -105,     0,    61,    14,    20,    10,    47,  -105,
    -105,  -105,  -105,  -105,  -105,     8,  -105,  -105,  -105,    30,
    -105,  -105,  -105,  -105,  -105,  -105,    24,    28,    -2,  -105,
    -105,    57,    59,     8,    59,    41,  -105,  -105,  -105,    64,
    -105,  -105,    37,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
       8,  -105,  -105,    28,    72,  -105,  -105,  -105,  -105,  -105,
    -105,    66,  -105,    33,    34,    39,  -105,  -105,  -105,    69,
      74,  -105,    62,    71,    78,  -105,  -105,  -105,  -105,    73,
    -105,  -105,    38,    38,  -105,    38,    38,  -105,  -105,  -105,
      38,  -105,    67,    59,    70,    65,    68,    78,    75,    72,
    -105,  -105,  -105,  -105,    79,  -105,  -105,    14,     8,    76,
       8,  -105,  -105,  -105,  -105,     8,  -105,  -105,  -105,    77,
    -105,  -105
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -105,  -105,    85,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
      29,  -105,  -105,   -16,    -7,    80,  -105,  -105,  -105,    56,
     -12,  -105,  -105,   -32,  -105,  -105,   -11,  -105,   -19,  -105,
    -105,  -104,  -105,  -105,    81,  -105,   -81,  -105,   -21,  -105,
    -105,  -105,  -105,    52,    -4
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -9
static const yytype_int16 yytable[] =
{
      23,    46,    47,    66,    34,    65,     6,    50,    38,    -8,
       1,   110,   111,    13,   126,    -4,     1,    35,    11,   114,
      36,   130,     2,    42,    17,    14,    15,    70,     2,    44,
      16,    65,    67,    68,    17,    52,    18,    45,    19,    20,
      21,    22,    98,     7,    99,    38,    84,     8,   100,    86,
      46,    47,    48,    87,    55,    56,    57,    58,    19,    20,
      21,    22,    46,    47,    77,    39,    40,    92,    93,    76,
      95,    96,    67,    68,   112,   113,    85,    89,    91,   102,
     103,   106,   104,   107,   109,   118,   115,   122,   117,   124,
      12,   120,    88,   123,    69,   121,    83,   127,   125,   116,
       0,   131,     0,     0,     0,    51,     0,     0,     0,     0,
      54,     0,     0,   128
};

static const yytype_int8 yycheck[] =
{
       7,     3,     4,     5,     1,    37,    14,    18,     8,     0,
       1,    92,    93,     5,   118,     0,     1,    14,     0,   100,
      29,   125,    13,     9,    26,    17,    18,    38,    13,     9,
      22,    63,    34,    35,    26,     5,    28,    27,    30,    31,
      32,    33,     3,     1,     5,     8,     5,     5,     9,    12,
       3,     4,     5,    60,    30,    31,    32,    33,    30,    31,
      32,    33,     3,     4,     5,     4,     5,    34,    35,    12,
      36,    37,    34,    35,    95,    96,    12,     5,    12,    10,
       6,    10,    20,     5,    11,    20,    19,    12,    18,    10,
       5,    23,    63,   109,    38,   107,    44,    21,   117,   103,
      -1,    24,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      29,    -1,    -1,   120
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    13,    40,    41,    42,    14,     1,     5,    43,
      44,     0,    41,     5,    17,    18,    22,    26,    28,    30,
      31,    32,    33,    53,    54,    55,    56,    58,    60,    62,
      63,    66,    71,    73,     1,    14,    29,    45,     8,     4,
       5,    57,     9,    67,     9,    27,     3,     4,     5,    64,
      65,    54,     5,    61,    73,    30,    31,    32,    33,    46,
      47,    48,    49,    50,    51,    62,     5,    34,    35,    58,
      65,    74,    75,    77,    79,    80,    12,     5,    65,    82,
      83,    53,    70,    82,     5,    12,    12,    53,    49,     5,
      52,    12,    34,    35,    76,    36,    37,    78,     3,     5,
       9,    81,    10,     6,    20,    68,    10,     5,    59,    11,
      75,    75,    77,    77,    75,    19,    83,    18,    20,    69,
      23,    59,    12,    52,    10,    67,    70,    21,    53,    72,
      70,    24
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 106 "syntactic/syntactic.y"
    {
        // Produção inicial: LISTA_FUNCOES
        print_production("PROGRAMA -> LISTA_FUNCOES");
    ;}
    break;

  case 3:
#line 114 "syntactic/syntactic.y"
    {
        // Produção para lista de funções: uma função seguida de uma lista de funções
        print_production("LISTA_FUNCOES -> FUNCAO LISTA_FUNCOES");
    ;}
    break;

  case 4:
#line 118 "syntactic/syntactic.y"
    {
        // Produção para lista de funções: uma única função
        print_production("LISTA_FUNCOES -> FUNCAO");
    ;}
    break;

  case 5:
#line 126 "syntactic/syntactic.y"
    {
        print_production("FUNCAO -> TOKEN_INICIO_FUNCAO FUNCAO_DECLARACAO TOKEN_FIM_FUNCAO");
    ;}
    break;

  case 6:
#line 129 "syntactic/syntactic.y"
    { 
        yyerror_with_location(&(yylsp[(1) - (3)]), "Erro de sintaxe no fim da função"); 
        yyerrok; 
        yyclearin; 
    ;}
    break;

  case 7:
#line 134 "syntactic/syntactic.y"
    { 
        yyerror_with_location(&(yylsp[(1) - (2)]), "Erro de sintaxe no início da função"); 
        yyerrok; 
        yyclearin; 
    ;}
    break;

  case 8:
#line 139 "syntactic/syntactic.y"
    {
        print_production("FUNCAO -> epsilon");
    ;}
    break;

  case 9:
#line 146 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_DECLARACAO -> FUNCAO_NOME FUNCAO_RETORNO FUNCAO_ARGS FUNCAO_CORPO");
    ;}
    break;

  case 10:
#line 149 "syntactic/syntactic.y"
    { 
        yyerror_with_location(&(yylsp[(1) - (2)]), "Erro de sintaxe na declaração da função"); 
        yyerrok; 
        yyclearin; 
    ;}
    break;

  case 11:
#line 158 "syntactic/syntactic.y"
    {
        // Nome da função: identificador
        print_production("FUNCAO_NOME -> TOKEN_IDENTIFICADOR");
    ;}
    break;

  case 12:
#line 166 "syntactic/syntactic.y"
    {
        // Produção para tipo de retorno
        print_production("FUNCAO_RETORNO -> TOKEN_TIPO FUNCAO_RETORNO_TIPO");
    ;}
    break;

  case 13:
#line 170 "syntactic/syntactic.y"
    {
        // Retorno vazio (epsilon)
        print_production("FUNCAO_RETORNO -> epsilon");
    ;}
    break;

  case 14:
#line 178 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_INTEIRO");
    ;}
    break;

  case 15:
#line 181 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_CARACTERE");
    ;}
    break;

  case 16:
#line 184 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_REAL");
    ;}
    break;

  case 17:
#line 187 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_RETORNO_TIPO -> TOKEN_LITERAL");
    ;}
    break;

  case 18:
#line 194 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_ARGS -> FUNCAO_ARGS_CORPO");
    ;}
    break;

  case 19:
#line 197 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_ARGS -> epsilon");
    ;}
    break;

  case 20:
#line 203 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_ARGS_CORPO -> LISTA_ARGS");
    ;}
    break;

  case 21:
#line 209 "syntactic/syntactic.y"
    {
        print_production("LISTA_ARGS -> ARG_DECLARACAO LISTA_ARGS");
    ;}
    break;

  case 22:
#line 212 "syntactic/syntactic.y"
    {
        print_production("LISTA_ARGS -> ARG_DECLARACAO");
    ;}
    break;

  case 23:
#line 218 "syntactic/syntactic.y"
    {
        print_production("ARG_DECLARACAO -> TIPO_ARG LISTA_IDENTIFICADORES");
    ;}
    break;

  case 24:
#line 224 "syntactic/syntactic.y"
    {
        print_production("TIPO_ARG -> VARIAVEL_TIPO");
    ;}
    break;

  case 25:
#line 229 "syntactic/syntactic.y"
    {
        print_production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR , LISTA_IDENTIFICADORES");
    ;}
    break;

  case 26:
#line 232 "syntactic/syntactic.y"
    {
        print_production("LISTA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR");
    ;}
    break;

  case 27:
#line 239 "syntactic/syntactic.y"
    {
        print_production("FUNCAO_CORPO -> { LISTA_DECLARACOES }");
    ;}
    break;

  case 28:
#line 245 "syntactic/syntactic.y"
    {
        print_production("LISTA_DECLARACOES -> DECLARACAO LISTA_DECLARACOES");
    ;}
    break;

  case 29:
#line 248 "syntactic/syntactic.y"
    {
        print_production("LISTA_DECLARACOES -> DECLARACAO");
    ;}
    break;

  case 37:
#line 264 "syntactic/syntactic.y"
    {
        print_production("ESCREVA_DECLARACAO -> TOKEN_ESCREVA ESCREVA_CORPO ;");
    ;}
    break;

  case 38:
#line 270 "syntactic/syntactic.y"
    {
        print_production("ESCREVA_CORPO -> TOKEN_STRING_LITERAL");
    ;}
    break;

  case 39:
#line 273 "syntactic/syntactic.y"
    {
        print_production("ESCREVA_CORPO -> TOKEN_IDENTIFICADOR");
    ;}
    break;

  case 40:
#line 279 "syntactic/syntactic.y"
    {
        print_production("CHAMA_DECLARACAO -> TOKEN_CHAMA TOKEN_CHAMADA TOKEN_IDENTIFICADOR CHAMA_ARGS ;");
    ;}
    break;

  case 41:
#line 285 "syntactic/syntactic.y"
    {
        print_production("CHAMA_ARGS -> TOKEN_IDENTIFICADOR CHAMA_ARGS");
    ;}
    break;

  case 42:
#line 288 "syntactic/syntactic.y"
    {
        print_production("CHAMA_ARGS -> TOKEN_IDENTIFICADOR");
    ;}
    break;

  case 43:
#line 291 "syntactic/syntactic.y"
    {
        print_production("CHAMA_ARGS -> epsilon");
    ;}
    break;

  case 44:
#line 297 "syntactic/syntactic.y"
    {
        print_production("VARIAVEL_DECLARACAO -> VARIAVEL_TIPO VARIAVEL_DECLARACAO_CORPO");
    ;}
    break;

  case 45:
#line 303 "syntactic/syntactic.y"
    {
        print_production("VARIAVEL_DECLARACAO_CORPO -> TOKEN_IDENTIFICADOR ;");
    ;}
    break;

  case 46:
#line 306 "syntactic/syntactic.y"
    {
        print_production("VARIAVEL_DECLARACAO_CORPO -> ATRIBUICAO_DECLARACAO");
    ;}
    break;

  case 47:
#line 312 "syntactic/syntactic.y"
    {
        print_production("VARIAVEL_TIPO -> TOKEN_INTEIRO");
    ;}
    break;

  case 48:
#line 315 "syntactic/syntactic.y"
    {
        print_production("VARIAVEL_TIPO -> TOKEN_REAL");
    ;}
    break;

  case 49:
#line 318 "syntactic/syntactic.y"
    {
        print_production("VARIAVEL_TIPO -> TOKEN_CARACTERE");
    ;}
    break;

  case 50:
#line 321 "syntactic/syntactic.y"
    {
        print_production("VARIAVEL_TIPO -> TOKEN_LITERAL");
    ;}
    break;

  case 51:
#line 327 "syntactic/syntactic.y"
    {
        print_production("RETORNA_DECLARACAO -> TOKEN_RETORNA RETORNA_CORPO ;");
    ;}
    break;

  case 52:
#line 333 "syntactic/syntactic.y"
    {
        print_production("RETORNA_CORPO -> TOKEN_IDENTIFICADOR");
    ;}
    break;

  case 53:
#line 336 "syntactic/syntactic.y"
    {
        print_production("RETORNA_CORPO -> VALOR");
    ;}
    break;

  case 54:
#line 342 "syntactic/syntactic.y"
    {
        print_production("VALOR -> TOKEN_NUM");
    ;}
    break;

  case 55:
#line 345 "syntactic/syntactic.y"
    {
        print_production("VALOR -> TOKEN_STRING_LITERAL");
    ;}
    break;

  case 56:
#line 350 "syntactic/syntactic.y"
    {
        print_production("SE_DECLARACAO -> TOKEN_SE SE_CABECALHO SE_CORPO SENAO_SE_BLOCO SENAO_BLOCO TOKEN_FIM_SE");
    ;}
    break;

  case 57:
#line 356 "syntactic/syntactic.y"
    {
        print_production("SE_CABECALHO -> ( EXPRESSAO_BOOLEANA ) TOKEN_ENTAO");
    ;}
    break;

  case 58:
#line 362 "syntactic/syntactic.y"
    {
        print_production("SENAO_SE_BLOCO -> TOKEN_SENAO TOKEN_SE SE_CABECALHO SE_CORPO");
    ;}
    break;

  case 59:
#line 365 "syntactic/syntactic.y"
    {
        print_production("SENAO_SE_BLOCO -> epsilon");
    ;}
    break;

  case 60:
#line 371 "syntactic/syntactic.y"
    {
        print_production("SENAO_BLOCO -> TOKEN_SENAO SE_CORPO");
    ;}
    break;

  case 61:
#line 374 "syntactic/syntactic.y"
    {
        print_production("SENAO_BLOCO -> epsilon");
    ;}
    break;

  case 62:
#line 380 "syntactic/syntactic.y"
    {
        print_production("SE_CORPO -> FUNCAO_CORPO");
    ;}
    break;

  case 63:
#line 386 "syntactic/syntactic.y"
    {
        print_production("ENQUANTO_DECLARACAO -> TOKEN_ENQUANTO ( EXPRESSAO_BOOLEANA ) TOKEN_FACA ENQUANTO_CORPO TOKEN_FIM_ENQUANTO");
    ;}
    break;

  case 64:
#line 392 "syntactic/syntactic.y"
    {
        print_production("ENQUANTO_CORPO -> FUNCAO_CORPO");
    ;}
    break;

  case 65:
#line 399 "syntactic/syntactic.y"
    {
        print_production("ATRIBUICAO_DECLARACAO -> TOKEN_IDENTIFICADOR = EXPRESSAO ;");
    ;}
    break;

  case 70:
#line 413 "syntactic/syntactic.y"
    {
        print_production("EXPRESSAO_MATEMATICA -> TERMO_MATEMATICO EXPRESSAO_SOMA_SUB");
    ;}
    break;

  case 71:
#line 416 "syntactic/syntactic.y"
    {
        print_production("EXPRESSAO_MATEMATICA -> TERMO_MATEMATICO");
    ;}
    break;

  case 72:
#line 422 "syntactic/syntactic.y"
    {
        print_production("EXPRESSAO_SOMA_SUB -> TOKEN_SOMA EXPRESSAO_MATEMATICA");
    ;}
    break;

  case 73:
#line 425 "syntactic/syntactic.y"
    {
        print_production("EXPRESSAO_SOMA_SUB -> TOKEN_SUB EXPRESSAO_MATEMATICA");
    ;}
    break;

  case 74:
#line 431 "syntactic/syntactic.y"
    {
        print_production("TERMO_MATEMATICO -> FATOR_MATEMATICO EXPRESSAO_MULT_DIV");
    ;}
    break;

  case 75:
#line 434 "syntactic/syntactic.y"
    {
        print_production("TERMO_MATEMATICO -> FATOR_MATEMATICO");
    ;}
    break;

  case 76:
#line 440 "syntactic/syntactic.y"
    {
        print_production("EXPRESSAO_MULT_DIV -> TOKEN_MULT TERMO_MATEMATICO");
    ;}
    break;

  case 77:
#line 443 "syntactic/syntactic.y"
    {
        print_production("EXPRESSAO_MULT_DIV -> TOKEN_DIVISAO TERMO_MATEMATICO");
    ;}
    break;

  case 78:
#line 449 "syntactic/syntactic.y"
    {
        print_production("FATOR_MATEMATICO -> SINAL_MATEMATICO FATOR_PRIMARIO_MATEMATICO");
    ;}
    break;

  case 79:
#line 455 "syntactic/syntactic.y"
    {
        print_production("SINAL_MATEMATICO -> TOKEN_SOMA");
    ;}
    break;

  case 80:
#line 458 "syntactic/syntactic.y"
    {
        print_production("SINAL_MATEMATICO -> TOKEN_SUB");
    ;}
    break;

  case 81:
#line 461 "syntactic/syntactic.y"
    {
        print_production("SINAL_MATEMATICO -> epsilon");
    ;}
    break;

  case 82:
#line 467 "syntactic/syntactic.y"
    {
        print_production("FATOR_PRIMARIO_MATEMATICO -> TOKEN_IDENTIFICADOR");
    ;}
    break;

  case 83:
#line 470 "syntactic/syntactic.y"
    {
        print_production("FATOR_PRIMARIO_MATEMATICO -> TOKEN_NUMERO");
    ;}
    break;

  case 84:
#line 473 "syntactic/syntactic.y"
    {
        print_production("FATOR_PRIMARIO_MATEMATICO -> ( EXPRESSAO_MATEMATICA )");
    ;}
    break;

  case 85:
#line 480 "syntactic/syntactic.y"
    {
        print_production("EXPRESSAO_BOOLEANA -> TERMO_BOOLEANO TOKEN_OP_RELACIONAL TERMO_BOOLEANO");
    ;}
    break;

  case 86:
#line 486 "syntactic/syntactic.y"
    {
        print_production("TERMO_BOOLEANO -> TOKEN_IDENTIFICADOR");
    ;}
    break;

  case 87:
#line 489 "syntactic/syntactic.y"
    {
        print_production("TERMO_BOOLEANO -> VALOR");
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2156 "syntactic/syntactic.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 495 "syntactic/syntactic.y"


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
