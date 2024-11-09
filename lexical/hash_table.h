#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_MAX_SIZE 100

struct node
{
  char *lex;
  char *token;
  int line;
  struct node *next_node;
} typedef node;

struct hash_table
{
  int max_size;
  node **buckets;
} typedef hash_table;

extern hash_table *ht;

void init_hash_table(hash_table *ht);

void fill_node(node *node, char *lex, char *token, int line);

int hash_function(hash_table *ht, char *lex);

void insert(hash_table *ht, char *lex, char *token, int line);

char *search(hash_table *ht, char *lex);

char *line_search(hash_table *ht, char *lex, int line);

void delete(hash_table *ht, char *lex);

void line_delete(hash_table *ht, char *lex, int line);

void drop_hash_table(hash_table *ht);

void ht_dump(hash_table *ht);

#endif