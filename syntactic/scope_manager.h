#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H

#include "hash_table.h"
#include "utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct scope
{
  int scope_id;
  hash_table *ht;
  struct scope *parent;
  var_type return_type;
  struct scope **children;
  int child_count;
} scope;

void init_scope(scope *new_scope, scope *parent);

void init_scope_manager();

void enter_scope(var_type return_type);

void exit_scope();

node *lookup_symbol_scope(char *lex);

scope *current_scope_get();

var_type current_scope_return_type();

void dump_all_scopes_by_level();

int get_scope_ident_count(scope *current_scope);

#endif // SCOPE_MANAGER_H
