#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_MAX_SIZE 100
#include "utils.h"

typedef struct node
{
  char *lex;
  char *token;
  int line;
  var_type type;
  symbol_kind kind;
  int param_count;
  var_type *param_types;
  int scope;
  struct node *next_node;
} node;

typedef struct
{
  int max_size;
  node **buckets;
} hash_table;

void init_hash_table(hash_table *ht);

int hash_function(hash_table *ht, char *lex);

void fill_node(node *node, char *lex, char *token, int line, var_type type, symbol_kind kind, int scope);

void insert(hash_table *ht, char *lex, char *token, int line, var_type type, symbol_kind kind, int scope);

void set_function_params(node *func_node, int param_count, var_type *param_types);

node* create_function_symbol(hash_table *ht, char *name, int line, var_type return_type, int scope);

node* create_variable_symbol(hash_table *ht, char *name, int line, var_type type, int scope);

node *lookup_symbol(hash_table *ht, char *lex, int scope);

char *search(hash_table *ht, char *lex);

char *line_search(hash_table *ht, char *lex, int line);

void delete(hash_table *ht, char *lex);

void line_delete(hash_table *ht, char *lex, int line);

void drop_hash_table(hash_table *ht);

void ht_dump(hash_table *ht);

var_type get_symbol_type(node * symbol);

#endif