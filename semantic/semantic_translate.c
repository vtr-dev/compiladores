#include "scope_manager.h"
#include "semantic_translate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define IDENT_SIZE 2
#define MAX_STACK 1000000

extern scope *current_scope;
extern int temp_var_count;
extern int while_label_count;

FILE *bril_file = NULL;
int file_opened = 0;

const char *var_type_to_string(var_type type)
{
  switch (type)
  {
  case TYPE_INT:
    return "int";
  case TYPE_REAL:
    return "real";
  case TYPE_CHAR:
    return "char";
  case TYPE_STRING:
    return "char";
  case TYPE_UNDEFINED:
    return "undefined";
  default:
    return "unknown";
  }
}

const char *op_to_string(char *op)
{
  if (strcmp(op, "==") == 0)
  {
    return "eq";
  }

  if (strcmp(op, "<>") == 0)
  {
    return "ne";
  }

  if (strcmp(op, ">") == 0)
  {
    return "gt";
  }

  if (strcmp(op, "<") == 0)
  {
    return "lt";
  }

  if (strcmp(op, ">=") == 0)
  {
    return "ge";
  }

  if (strcmp(op, "<=") == 0)
  {
    return "le";
  }

  return "unknown";
}

void ensure_file_open()
{
  if (!file_opened)
  {
    bril_file = fopen("main.bril", "w");
    if (bril_file == NULL)
    {
      perror("Detalhes do erro");
      exit(EXIT_FAILURE);
    }
    else
    {
      file_opened = 1;
    }
  }
}

void close_bril_file()
{
  if (file_opened)
  {
    fclose(bril_file);
    file_opened = 0;
    bril_file = NULL;
  }
}

void write_with_indent(const char *format, ...)
{
  int indent_count = get_scope_ident_count(current_scope);
  int total_indent = indent_count * IDENT_SIZE;

  char indent[total_indent + 1];
  for (int i = 0; i < total_indent; i++)
  {
    indent[i] = ' ';
  }
  indent[total_indent] = '\0';

  va_list args;
  va_start(args, format);
  fprintf(bril_file, "%s", indent);
  vfprintf(bril_file, format, args);
  va_end(args);
}

void translate_function_declaration(char *func_name, var_type function_type, char **param_names, var_type *param_types, int num_args)
{
  ensure_file_open();

  scope *previous_scope = current_scope;
  current_scope = current_scope->parent;

  if (strcmp(func_name, "principal") == 0)
  {
    strcpy(func_name, "main");
  }

  write_with_indent("@%s(", func_name);
  current_scope = previous_scope;

  for (int i = num_args - 1; i >= 0; i--)
  {
    fprintf(bril_file, "%s: %s", param_names[i], var_type_to_string(param_types[i]));
    if (i > 0)
    {
      fprintf(bril_file, ", ");
    }
  }
  if (function_type != TYPE_UNDEFINED)
  {
    fprintf(bril_file, "): %s {\n", var_type_to_string(function_type));
    return;
  }

  fprintf(bril_file, ") {\n");
}

void translate_function_end()
{
  ensure_file_open();

  write_with_indent("}\n\n");
}

void translate_var_declaration(char **var_names, var_type type, int var_count)
{
  ensure_file_open();

  switch (type)
  {
  case TYPE_INT:
    for (int i = 0; i < var_count; i++)
    {
      write_with_indent("%s: int = const 0;\n", var_names[i]);
    }
    break;

  case TYPE_REAL:
    for (int i = 0; i < var_count; i++)
    {
      write_with_indent("%s: real = const 0.0;\n", var_names[i]);
    }
    break;

  case TYPE_CHAR:
    for (int i = 0; i < var_count; i++)
    {
      write_with_indent("%s: char = const 'a';\n", var_names[i]);
    }
    break;

  case TYPE_STRING:
    for (int i = 0; i < var_count; i++)
    {
      write_with_indent("%s: char = const 'a';\n", var_names[i]);
    }
    break;

  default:
    break;
  }
}

void translate_var_declaration_assign(char *var_name, var_type type, char *var)
{
  ensure_file_open();

  switch (type)
  {
  case TYPE_INT:
    write_with_indent("%s: int = %s;\n", var_name, var);
    break;

  case TYPE_REAL:
    write_with_indent("%s: real = %s;\n", var_name, var);
    break;

  case TYPE_CHAR:
    write_with_indent("%s: char = %s;\n", var_name, var);
    break;

  case TYPE_STRING:
    write_with_indent("%s: char = %s;\n", var_name, var);
    break;

  default:
    break;
  }
}

void translate_declaration_header(char *var_name, var_type type)
{
  ensure_file_open();
  write_with_indent("%s: %s", var_name, var_type_to_string(type));
}

void translate_assignment(char *var_name, var_type type, char *content)
{
  ensure_file_open();
  translate_declaration_header(var_name, type);
  fprintf(bril_file, " = ");
  fprintf(bril_file, "%s", content);
}

char *translate_constant(char *str_value)
{
  ensure_file_open();
  char *const_str_value = calloc(1, 1000);
  sprintf(const_str_value, "const %s", str_value);
  return const_str_value;
}

char *translate_string(char *str_value)
{
  char *string_without_quotes = strdup(str_value + 1);
  string_without_quotes[strlen(string_without_quotes) - 1] = '\0';

  if (strlen(string_without_quotes) != 1)
  {
    return NULL;
  }

  char single_char = string_without_quotes[0];
  char *single_char_with_quotes = malloc(4 * sizeof(char));
  sprintf(single_char_with_quotes, "'%c'", single_char);
  return single_char_with_quotes;
}

void translate_declaration_footer()
{
  ensure_file_open();
  fprintf(bril_file, ";\n");
}

void translate_print(char *name, symbol_kind kind)
{
  ensure_file_open();

  if (kind == SYMBOL_VAR)
  {
    write_with_indent("print %s;\n", name);
    return;
  }

  int len = strlen(name);
  for (int i = 0; i < len; i++)
  {
    write_with_indent("t%d: char = const '%c';\n", temp_var_count, name[i]);
    temp_var_count++;
  }

  write_with_indent("print");
  for (int i = temp_var_count - len; i < temp_var_count; i++)
  {
    fprintf(bril_file, " t%d", i);
  }
  fprintf(bril_file, ";\n");
}

char *translate_function_call(char **names, int count)
{
  char *str = calloc(1, 1000);
  ensure_file_open();
  sprintf(str, "call @%s", names[count - 1]);

  for (int i = count - 2; i >= 0; i--)
  {
    strcat(str, " ");
    strcat(str, names[i]);
  }

  return str;
}

void translate_return(char *content)
{
  ensure_file_open();

  write_with_indent("ret %s;\n", content);
}

void translate_if_header(char *id1, symbol_kind kind1, char *id2, symbol_kind kind2, var_type type, char *op, int id_if, int id_bool_expr)
{
  ensure_file_open();
  translate_conditional(id1, kind1, id2, kind2, type, op, id_bool_expr);
  write_with_indent("br cond%d .true%d .false%d;\n", id_bool_expr, id_if, id_if);
  scope *previous_scope = current_scope;
  current_scope = current_scope->parent;
  write_with_indent(".true%d:\n", id_if);
  current_scope = previous_scope;
}

void translate_conditional(char *id1, symbol_kind kind1, char *id2, symbol_kind kind2, var_type type, char *op, int id_bool_expr)
{
  ensure_file_open();

  if (kind1 != SYMBOL_VAR)
  {
    write_with_indent("t%d: %s = const %s;\n", temp_var_count, var_type_to_string(type), id1);
    id1 = malloc(10);
    sprintf(id1, "t%d", temp_var_count);
    temp_var_count++;
  }

  if (kind2 != SYMBOL_VAR)
  {
    write_with_indent("t%d: %s = const %s;\n", temp_var_count, var_type_to_string(type), id2);
    id2 = malloc(10);
    sprintf(id2, "t%d", temp_var_count);
    temp_var_count++;
  }

  char *op_str = translate_conditional_operator(type, op);
  write_with_indent("cond%d: bool = %s %s %s;\n", id_bool_expr, op_str, id1, id2);

  free(op_str);
}

char *translate_conditional_operator(var_type type, char *op)
{
  char *op_str = malloc(5);
  op_str[0] = '\0';

  if (type == TYPE_REAL)
    strcpy(op_str, "f");
  if (type == TYPE_CHAR)
    strcpy(op_str, "c");

  op_str = realloc(op_str, strlen(op_str) + strlen(op_to_string(op)) + 1);
  strcat(op_str, op_to_string(op));
  return op_str;
}

void translate_while_header(char *id1, symbol_kind kind1, char *id2, symbol_kind kind2, var_type type, char *op, int id_while, int id_bool_expr)
{
  ensure_file_open();
  write_with_indent(".while.cond%d:\n", id_while);
  translate_conditional(id1, kind1, id2, kind2, type, op, id_bool_expr);
  write_with_indent("br cond%d .while.body%d .while.finish%d;\n", id_bool_expr, id_while, id_while);
  write_with_indent(".while.body%d:\n", id_while);
}

void translate_while_footer(int id_while)
{
  ensure_file_open();
  write_with_indent("jmp .while.cond%d;\n", id_while);
  write_with_indent(".while.finish%d:\n", id_while);
}

void translate_if_footer(int id_if)
{
  ensure_file_open();

  scope *previous_scope = current_scope;
  current_scope = current_scope->parent;
  write_with_indent(".false%d:\n", id_if);
  current_scope = previous_scope;
}

typedef struct
{
  char *stack[MAX_STACK];
  int top;
} operand_stack;

static void push(operand_stack *s, const char *val)
{
  s->stack[++s->top] = strdup(val);
}

static char *pop(operand_stack *s)
{
  return s->stack[s->top--];
}

char *translate_bril_from_postfix(const char *postfix, var_type type)
{
  operand_stack s;
  s.top = -1;

  char *code = strdup(postfix);
  char *token = strtok(code, " ");

  while (token)
  {
    if (is_operator(token))
    {
      char *op2 = pop(&s);
      char *op1 = pop(&s);

      char temp_reg[1000];
      snprintf(temp_reg, 1000, "t%d", temp_var_count++);

      if (strcmp(token, "+") == 0)
      {
        write_with_indent("%s: %s = add %s %s;\n", temp_reg, var_type_to_string(type), op1, op2);
      }
      else if (strcmp(token, "-") == 0)
      {
        write_with_indent("%s: %s = sub %s %s;\n", temp_reg, var_type_to_string(type), op1, op2);
      }
      else if (strcmp(token, "*") == 0)
      {
        write_with_indent("%s: %s = mul %s %s;\n", temp_reg, var_type_to_string(type), op1, op2);
      }
      else if (strcmp(token, "/") == 0)
      {
        write_with_indent("%s: %s = div %s %s;\n", temp_reg, var_type_to_string(type), op1, op2);
      }
      else if (strcmp(token, "~") == 0)
      {
        write_with_indent("%s: %s = neg %s;\n", temp_reg, var_type_to_string(type), op1);
      }

      push(&s, temp_reg);

      free(op1);
      free(op2);
    }
    else
    {
      push(&s, token);
    }

    token = strtok(NULL, " ");
  }

  char *final = pop(&s);
  return final;
}

int is_operator(const char *token)
{
  return (strcmp(token, "+") == 0 ||
          strcmp(token, "-") == 0 ||
          strcmp(token, "*") == 0 ||
          strcmp(token, "/") == 0 ||
          strcmp(token, "~") == 0);
}