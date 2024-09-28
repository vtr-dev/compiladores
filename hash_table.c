#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash_table.h"

void init_hash_table(hash_table *ht)
{
  ht->max_size = TABLE_MAX_SIZE;
  ht->buckets = (node **)malloc(sizeof(node *) * ht->max_size);
  return;
}

void fill_node(node *node, char *lex, char *token, int line)
{
  node->lex = (char *)malloc(strlen(lex) + 1);
  node->token = (char *)malloc(strlen(token) + 1);
  strcpy(node->token, token);
  strcpy(node->lex, lex);
  node->line = line;
  node->next_node = NULL;
};

int hash_function(hash_table *ht, char *lex)
{
  int bucket_index;
  int sum = 0, factor = 31;

  for (int i = 0; i < strlen(lex); i++)
  {
    sum = ((sum % ht->max_size) + (((int)lex[i]) * factor) % ht->max_size) % ht->max_size;
    factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucket_index = sum;
  return bucket_index;
}

void insert(hash_table *ht, char *lex, char *token, int line)
{
  node *new_node = (node *)malloc(sizeof(node));
  fill_node(new_node, lex, token, line);

  int bucket_index = hash_function(ht, lex);

  new_node->next_node = ht->buckets[bucket_index];
  ht->buckets[bucket_index] = new_node;

  return;
}

char *search(hash_table *ht, char *lex)
{
  int bucket_index = hash_function(ht, lex);
  node *current_node = ht->buckets[bucket_index];

  while (current_node != NULL)
  {
    if (strcmp(current_node->lex, lex) == 0)
    {
      return current_node->token;
    }

    current_node = current_node->next_node;
  }

  return "No token found.\n";
}

char *line_search(hash_table *ht, char *lex, int line)
{
  int bucket_index = hash_function(ht, lex);
  node *current_node = ht->buckets[bucket_index];

  while (current_node != NULL)
  {
    if (strcmp(current_node->lex, lex) == 0 && current_node->line == line)
    {
      return current_node->token;
    }

    current_node = current_node->next_node;
  }

  return "No token found.\n";
}

void delete(hash_table *ht, char *lex)
{
  node *previous_node = NULL;

  int bucket_index = hash_function(ht, lex);
  node *current_node = ht->buckets[bucket_index];

  while (current_node != NULL)
  {
    if (strcmp(lex, current_node->lex) == 0)
    {
      if (current_node == ht->buckets[bucket_index])
      {
        ht->buckets[bucket_index] = current_node->next_node;
      }
      else
      {
        previous_node->next_node = current_node->next_node;
      }

      free(current_node);
    }

    previous_node = current_node;
    current_node = current_node->next_node;
  }

  return;
}

void line_delete(hash_table *ht, char *lex, int line)
{
  node *previous_node = NULL;

  int bucket_index = hash_function(ht, lex);
  node *current_node = ht->buckets[bucket_index];

  while (current_node != NULL)
  {
    if (strcmp(lex, current_node->lex) == 0 && current_node->line == line)
    {
      if (current_node == ht->buckets[bucket_index])
      {
        ht->buckets[bucket_index] = current_node->next_node;
      }
      else
      {
        previous_node->next_node = current_node->next_node;
      }

      free(current_node);
    }

    previous_node = current_node;
    current_node = current_node->next_node;
  }

  return;
}

void drop_hash_table(hash_table *ht)
{
  for (int i = 0; i < ht->max_size; i++)
  {
    node *current_node = ht->buckets[i];

    while (current_node != NULL)
    {
      node *temp = current_node;
      current_node = current_node->next_node;
      free(temp);
    }
  }

  free(ht->buckets);
  ht->buckets = NULL;
  ht->max_size = 0;
  return;
}

void ht_dump(hash_table *ht)
{
  printf("HASH TABLE DUMP:\n");
  for (int i = 0; i < ht->max_size; i++)
  {
    node *current_node = ht->buckets[i];

    if (current_node != NULL)
    {
      printf("\nBucket %d:\n", i);
    }

    while (current_node != NULL)
    {
      printf("lex: %s, token: %s, line: %d\n", current_node->lex, current_node->token, current_node->line);
      current_node = current_node->next_node;
    }
  }

  return;
}