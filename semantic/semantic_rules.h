#ifndef SEMANTIC_RULES_H
#define SEMANTIC_RULES_H

#include "semantic_utils.h"
#include "utils.h"

/**
 * Verifica se a declaração de variável é válida (não duplicada) e insere na tabela.
 */
void semantic_rule_variavel_declaracao(char *var_name, var_type type, int line);


/**
 * Verifica atribuição de uma expressão a uma variável.
 */
void semantic_rule_atribuicao(char *var_name, var_type expr_type);

/**
 * Verifica operação binária.
 * Retorna o tipo resultante ou TYPE_UNDEFINED em caso de erro.
 */
var_type semantic_rule_operacao_binaria(var_type lhs_type, var_type rhs_type);

/**
 * Verifica expressão booleana (comparação).
 * Retorna TYPE_INT se válido, TYPE_UNDEFINED se não.
 */
var_type semantic_rule_expressao_booleana(var_type lhs_type, var_type rhs_type);

/**
 * Verifica chamada de função.
 * Retorna o tipo da função ou TYPE_UNDEFINED em caso de erro.
 */
var_type semantic_rule_chamada_funcao(char ** arg_names, int arg_count);

/**
 * Verifica declaração de função.
 */
void semantic_rule_funcao_declaracao(char *func_name, var_type return_type, int param_count, var_type *param_types, int line);

/**
 * Verifica retorno da função.
 */
void semantic_rule_retorna_declaracao(var_type func_type, var_type return_type);

/**
 * Verifica se variável existe.
 */
void semantic_rule_var_existe(char *var_name);

#endif
