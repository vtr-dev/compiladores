#include "scope_manager.h"

scope *current_scope = NULL;
int global_scope_id = 0;

void init_scope(scope *new_scope, scope *parent)
{
  new_scope->scope_id = global_scope_id++;
  new_scope->ht = (hash_table *)malloc(sizeof(hash_table));
  if (!new_scope->ht)
  {
    fprintf(stderr, "Erro: falha ao alocar tabela de símbolos.\n");
    exit(1);
  }
  init_hash_table(new_scope->ht);
  new_scope->parent = parent;
  new_scope->return_type = TYPE_UNDEFINED;
  new_scope->children = NULL;
  new_scope->child_count = 0;
}

void init_scope_manager()
{
  current_scope = (scope *)malloc(sizeof(scope));
  if (!current_scope)
  {
    fprintf(stderr, "Erro: falha ao alocar escopo global.\n");
    exit(1);
  }
  init_scope(current_scope, NULL);
}

void enter_scope(var_type return_type)
{
  scope *new_scope = (scope *)malloc(sizeof(scope));
  if (!new_scope)
  {
    fprintf(stderr, "Erro: falha ao alocar novo escopo.\n");
    exit(1);
  }

  init_scope(new_scope, current_scope);
  new_scope->return_type = return_type;

  current_scope->children = (scope **)realloc(current_scope->children,
                                              sizeof(scope *) * (current_scope->child_count + 1));
  current_scope->children[current_scope->child_count++] = new_scope;

  current_scope = new_scope;
}

void exit_scope()
{
  if (current_scope != NULL)
  {
    current_scope = current_scope->parent;
  }
  else
  {
    fprintf(stderr, "Erro: tentativa de sair de um escopo inexistente.\n");
  }
}

node *lookup_symbol_scope(char *lex)
{
  scope *s = current_scope;
  while (s != NULL)
  {
    node *symbol = lookup_symbol(s->ht, lex, s->scope_id);

    if (symbol != NULL)
    {
      return symbol;
    }
    s = s->parent;
  }
  return NULL;
}

scope *current_scope_get()
{
  return current_scope;
}

var_type current_scope_return_type()
{
  if (current_scope)
  {
    return current_scope->return_type;
  }
  return TYPE_UNDEFINED;
}

void dump_all_scopes_by_level()
{
  printf("........................................................\n");

  // Fila para travessia em largura
  scope **queue = (scope **)malloc(sizeof(scope *));
  int queue_size = 0, queue_capacity = 1;

  if (current_scope == NULL)
    return;

  queue[queue_size++] = current_scope;

  while (queue_size > 0)
  {
    scope *s = queue[0];

    for (int i = 1; i < queue_size; i++)
    {
      queue[i - 1] = queue[i];
    }
    queue_size--;
    printf("\nEscopo ID: %d\n", s->scope_id);
    printf("Tabela de símbolos do escopo %d:\n", s->scope_id);
    ht_dump(s->ht);
    printf("\n---------------------------------------------------\n");
    for (int i = 0; i < s->child_count; i++)
    {
      if (queue_size == queue_capacity)
      {
        queue_capacity *= 2;
        queue = (scope **)realloc(queue, sizeof(scope *) * queue_capacity);
      }
      queue[queue_size++] = s->children[i];
    }
  }
  free(queue);
}

int get_scope_ident_count(scope *current_scope)
{
  int count = 0;
  scope *s = current_scope;
  while (s != NULL)
  {
    count++;
    s = s->parent;
  }
  return count - 1;
}
