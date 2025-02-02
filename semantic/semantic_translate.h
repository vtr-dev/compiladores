#ifndef SEMANTIC_TRANSLATE_H
#define SEMANTIC_TRANSLATE_H

#include "utils.h"

void translate_function_declaration(char *func_name, var_type function_type, char **param_names, var_type *param_types, int num_args);

void translate_function_end();

void translate_declaration_header(char *var_name, var_type type);

void translate_declaration_footer();

void translate_assignment(char *var_name, var_type type, char *content);

char *translate_constant(char *str_value);

char *translate_string(char *str_value);

void translate_var_declaration(char **var_names, var_type type, int var_count);

void translate_var_declaration_assign(char *var_name, var_type type, char *var);

void translate_print(char *name, symbol_kind kind);

char *translate_function_call(char **names, int count);

void translate_return(char *content);

void translate_if_header(char *id1, symbol_kind kind1, char *id2, symbol_kind kind2, var_type type, char *op, int id_if, int id_bool_expr);

void translate_if_footer(int id_if);

char *translate_conditional_operator(var_type type, char *op);

void translate_conditional(char *id1, symbol_kind kind1, char *id2, symbol_kind kind2, var_type type, char *op, int id_bool_expr);

void translate_while_header(char *id1, symbol_kind kind1, char *id2, symbol_kind kind2, var_type type, char *op, int id_while, int id_bool_expr);

void translate_while_footer(int id_while);

void write_with_indent(const char *format, ...);

char *translate_bril_from_postfix(const char *postfix, var_type type);

int is_operator(const char *token);

#endif
