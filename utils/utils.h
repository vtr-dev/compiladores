
#ifndef UTILS_H
#define UTILS_H

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
  TYPE_INT,
  TYPE_REAL,
  TYPE_CHAR,
  TYPE_STRING,
  TYPE_UNDEFINED
} var_type;

typedef enum
{
  SYMBOL_VAR,
  SYMBOL_FUNC,
  SYMBOL_PARAM,
  SYMBOL_UNDEFINED
} symbol_kind;

const char *var_type_to_label(var_type type);

const char *symbol_kind_to_label(symbol_kind kind);

int is_integer(const char* str);

int is_real(const char* str);

char *combine_postfix(const char *op1, const char *op2, const char *oper);

char *combine_unary_postfix(const char *op, const char *unary_op);

#endif