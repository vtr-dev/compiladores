#include "semantic_utils.h"
#include "scope_manager.h"
#include "position_manager.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

extern int errors_number;

int check_type_compatibility(var_type var, var_type expr)
{
  if (var == expr)
  {
    return TRUE;
  }

  if ((var == TYPE_INT && expr == TYPE_REAL) || (var == TYPE_REAL && expr == TYPE_INT))
  {
    return TRUE;
  }

  if ((var == TYPE_CHAR && expr == TYPE_STRING) || (var == TYPE_STRING && expr == TYPE_CHAR))
  {
    return TRUE;
  }

  return FALSE;
}

int check_assignment(var_type var, var_type expr)
{
  return check_type_compatibility(var, expr);
}

int check_function_return(var_type func_type, var_type return_type)
{
  return check_type_compatibility(func_type, return_type);
}

int check_function_call(char *func_name, int arg_count, var_type *arg_types)
{
  node *func_node = lookup_symbol_scope(func_name);

  if (!func_node)
  {
    semantic_error("Função '%s' não declarada.", func_name);
    return FALSE;
  }

  if (func_node->kind != SYMBOL_FUNC)
  {
    semantic_error("Símbolo '%s' não é uma função.", func_name);
    return FALSE;
  }

  if (func_node->param_count != arg_count)
  {
    semantic_error("A função '%s' espera %d parâmetros, mas foi chamada com %d.",
                   func_name, func_node->param_count, arg_count);
    return FALSE;
  }

  for (int i = 0; i < arg_count; i++)
  {
    if (!check_type_compatibility(func_node->param_types[i], arg_types[i]))
    {
      semantic_error("Tipo do parâmetro %d da função '%s' incompatível. Esperado '%d', encontrado '%d'.",
                     i + 1, func_name, func_node->param_types[i], arg_types[i]);
      return FALSE;
    }
  }

  return 1;
}

int check_variable_exists(char *name)
{
  node *sym = lookup_symbol_scope(name);
  if (!sym)
  {
    semantic_error("Variável '%s' não declarada neste escopo.", name);
    return FALSE;
  }
  return TRUE;
}

void semantic_error(const char *message, ...)
{
  errors_number++;
  va_list args;
  va_start(args, message);
  fprintf(stderr, "\n🔴 Erro semântico: - linha %d, coluna %d: ", line_num, col_num);
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  fprintf(stderr, "~> Linha do erro: \"%s\"\n\n", line_text);
  va_end(args);
}
