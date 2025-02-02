#ifndef SEMANTIC_UTILS_H
#define SEMANTIC_UTILS_H

#include "hash_table.h"
#include "utils.h"

/**
 * @brief Verifica compatibilidade de tipos. 
 *        Por exemplo, TYPE_INT com TYPE_INT é compatível, TYPE_INT com TYPE_REAL pode ser compatível dependendo da regra, etc.
 * @param var_type Tipo da variável ou tipo esperado.
 * @param expr_type Tipo da expressão ou tipo obtido.
 * @return 1 se compatível, 0 caso contrário.
 */
int check_type_compatibility(var_type var, var_type expr_type);

/**
 * @brief Verifica se a atribuição é compatível entre variável e expressão.
 *        Usa internamente check_type_compatibility.
 * @param var_type Tipo da variável.
 * @param expr_type Tipo da expressão a atribuir.
 * @return 1 se compatível, 0 caso contrário.
 */
int check_assignment(var_type var, var_type expr_type);

/**
 * @brief Verifica o tipo de retorno da função.
 * @param func_type Tipo declarado da função.
 * @param return_type Tipo do valor retornado.
 * @return 1 se compatível, 0 caso contrário.
 */
int check_function_return(var_type func_type, var_type return_type);

/**
 * @brief Verifica chamada de função consultando a tabela de símbolos.
 * @param func_name Nome da função.
 * @param arg_count Número de argumentos na chamada.
 * @param arg_types Lista de tipos dos argumentos.
 * @return 1 se a chamada é válida, 0 caso contrário.
 */
int check_function_call(char *func_name, int arg_count, var_type *arg_types);

/**
 * @brief Verifica se uma variável existe no escopo atual ou ascendente.
 * @param name Nome da variável.
 * @return 1 se existe, 0 caso contrário.
 */
int check_variable_exists(char *name);

/**
 * @brief Registra um erro semântico. Incrementa o contador de erros e imprime mensagem.
 * @param message Mensagem com formato printf-like.
 * @param ... Argumentos da mensagem formatada.
 */
void semantic_error(const char *message, ...);

#endif // SEMANTIC_UTILS_H