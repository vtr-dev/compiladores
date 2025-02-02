#include "semantic_rules.h"
#include "semantic_utils.h"
#include "scope_manager.h"
#include <stdio.h>
#include <stdlib.h>

void semantic_rule_variavel_declaracao(char *var_name, var_type type, int line)
{
  node *sym = lookup_symbol_scope(var_name);
  if (sym && sym->scope == current_scope_get()->scope_id)
  {
    semantic_error("Variável '%s' já declarada neste escopo.", var_name);
    return;
  }
  insert(current_scope_get()->ht, var_name, "variable", line, type, SYMBOL_VAR, current_scope_get()->scope_id);
}

void semantic_rule_atribuicao(char *var_name, var_type expr_type)
{
  node *sym = lookup_symbol_scope(var_name);
  if (!sym)
  {
    semantic_error("Variável '%s' não declarada.", var_name);
    return;
  }

  if (!check_assignment(sym->type, expr_type))
  {
    semantic_error("Atribuição incompatível: variável '%s' é do tipo '%s' e a expressão é '%s'.",
                   var_name, var_type_to_label(sym->type), var_type_to_label(expr_type));
  }
}

var_type semantic_rule_operacao_binaria(var_type lhs_type, var_type rhs_type)
{
  if ((lhs_type == TYPE_INT || lhs_type == TYPE_REAL) &&
      (rhs_type == TYPE_INT || rhs_type == TYPE_REAL))
  {
    return (lhs_type == TYPE_REAL || rhs_type == TYPE_REAL) ? TYPE_REAL : TYPE_INT;
  }
  else
  {
    semantic_error("Operação binária inválida entre tipos '%s' e '%s'.", var_type_to_label(lhs_type), var_type_to_label(rhs_type));
    return TYPE_UNDEFINED;
  }
}

var_type semantic_rule_expressao_booleana(var_type lhs_type, var_type rhs_type)
{
  if (check_type_compatibility(lhs_type, rhs_type))
  {
    if (lhs_type == TYPE_REAL)
      return TYPE_REAL;
    if (rhs_type == TYPE_REAL)
      return TYPE_REAL;
    if (lhs_type == TYPE_CHAR)
      return TYPE_CHAR;
    return TYPE_INT;
  }
  else if (lhs_type != TYPE_UNDEFINED && rhs_type != TYPE_UNDEFINED)
  { // ANALISAR
    semantic_error("Comparação inválida entre tipos '%s' e '%s'.", var_type_to_label(lhs_type), var_type_to_label(rhs_type));
    return TYPE_UNDEFINED;
  }
  return TYPE_UNDEFINED;
}

var_type semantic_rule_chamada_funcao(char **arg_names, int arg_count)
{
  if (arg_count == 0)
  {
    semantic_error("Chamada de função sem função encontrada");
    return TYPE_UNDEFINED;
  }

  char *func_name = arg_names[arg_count - 1];

  var_type *arg_types = malloc(arg_count * sizeof(var_type));
  for (int i = 0; i < arg_count - 1; i++)
  {
    node *symbol = lookup_symbol_scope(arg_names[i]);
    arg_types[i] = get_symbol_type(symbol);
  }
  arg_count--;

  if (!check_function_call(func_name, arg_count, arg_types))
  {
    return TYPE_UNDEFINED;
  }

  node *func_node = lookup_symbol_scope(func_name);
  if (!func_node)
  {
    semantic_error("Função '%s' não encontrada após verificação.", func_name);
    return TYPE_UNDEFINED;
  }
  return func_node->type;
}

void semantic_rule_funcao_declaracao(char *func_name, var_type return_type, int param_count, var_type *param_types, int line)
{
  node *sym = lookup_symbol_scope(func_name);
  if (sym && sym->scope == current_scope_get()->scope_id)
  {
    semantic_error("Função '%s' já declarada neste escopo.", func_name);
    return;
  }

  node *parent_func_symbol = create_function_symbol(current_scope_get()->parent->ht, func_name, line, return_type, current_scope_get()->parent->scope_id);
  set_function_params(parent_func_symbol, param_count, param_types);

  node *func_symbol = create_function_symbol(current_scope_get()->ht, func_name, line, return_type, current_scope_get()->scope_id);
  set_function_params(func_symbol, param_count, param_types);
}

void semantic_rule_retorna_declaracao(var_type func_type, var_type return_type)
{
  if (!check_function_return(func_type, return_type))
  {
    semantic_error("Tipo de retorno incompatível. Esperado '%s', obtido '%s'.", var_type_to_label(func_type), var_type_to_label(return_type));
  }
}

void semantic_rule_var_existe(char *var_name)
{
  check_variable_exists(var_name);
}