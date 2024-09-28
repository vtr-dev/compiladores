D [0-9]
L [a-zA-Z]
S [~\`!@#\$%^&*()_\-+\[\]{}|‘?><.\=,]

KEYWORDS funcao|fimfuncao|chama|retorna|tipo|arg|fimargs|escreva|inteiro|real|caractere|se|entao|senao|fimse|enquanto|faca|fimenquanto

WHITESPACE [ ]
NEW_LINE [\n]
TAB [\t]
UNDERSCORE [_]
QUOTE \"

%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define HT_PRIME_1 5
#define HT_PRIME_2 7

typedef struct
{
  char *token;
  char *value;
  int line;
} ht_item;

typedef struct
{
  int size;
  int count;
  ht_item **items;
} ht_hash_table;

ht_item *ht_new_item(const char *t, const char *v, const int l)
{
  ht_item *i = malloc(sizeof(ht_item));
  i->token = strdup(t);
  i->value = strdup(v);
  i->line = l;
  return i;
}

ht_hash_table *ht_new()
{
  ht_hash_table *ht = malloc(sizeof(ht_hash_table));
  ht->size = 53;
  ht->count = 0;
  ht->items = calloc((size_t)ht->size, sizeof(ht_item *));
  return ht;
}

void ht_del_item(ht_item *i)
{
  free(i->token);
  free(i->value);
  
  free(i);
}

void ht_del_hash_table(ht_hash_table *ht)
{
  for (int i = 0; i < ht->size; i++)
  {
    ht_item *item = ht->items[i];
    if (item != NULL)
    {
      ht_del_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

int ht_hash(const char* s, const int a, const int m) {
  long hash = 0;
  const int len_s = strlen(s);
  for (int i = 0; i < len_s; i++) {
      hash += (long)pow(a, len_s - (i+1)) * s[i];
      hash = hash % m;
  }
  return (int)hash;
}

int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
  const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
  const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table* ht, const char* token, const char* value, const int line) {
  ht_item* item = ht_new_item(token, value, line);
  int index = ht_get_hash(item->token, ht->size, 0);
  ht_item* cur_item = ht->items[index];
  int i = 1;
  while (cur_item != NULL) {
      index = ht_get_hash(item->token, ht->size, i);
      cur_item = ht->items[index];
      i++;
  } 
  ht->items[index] = item;
  ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* token) {
  int index = ht_get_hash(token, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;
  while (item != NULL) {
      if (strcmp(item->token, token) == 0) {
          return item->value;
      }
      index = ht_get_hash(token, ht->size, i);
      item = ht->items[index];
      i++;
  } 
  return NULL;
}

static ht_item HT_DELETED_ITEM = {NULL, NULL};

void ht_delete(ht_hash_table* ht, const char* token) {
  int index = ht_get_hash(token, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;
  while (item != NULL) {
      if (item != &HT_DELETED_ITEM) {
          if (strcmp(item->token, token) == 0) {
              ht_del_item(item);
              ht->items[index] = &HT_DELETED_ITEM;
          }
      }
      index = ht_get_hash(token, ht->size, i);
      item = ht->items[index];
      i++;
  } 
  ht->count--;
}

void ht_dump(ht_hash_table* ht) {
  printf("Hash Table Dump:\n");
  for (int i = 0; i < ht->size; i++) {
      ht_item* item = ht->items[i];
      if (item == NULL) {
          printf("[%d]: NULL\n", i);
      } else if (item == &HT_DELETED_ITEM) {
          printf("[%d]: DELETED\n", i);
      } else {
          printf("[%d]: Token = %s, Value = %s, Line = %d\n", i, item->token, item->value, item->line);
      }
  }
}

ht_hash_table* ht;

void remove_first_and_last_char(char* str) {
  int len = strlen(str);
  
  if (len > 1) {
    memmove(str, str + 1, len - 1);
    str[len - 2] = '\0';
  }
}

%}

%option yylineno
%x COMMENT

%%

{KEYWORDS}                                              { ht_insert(ht, yytext, yytext, yylineno); } 
{QUOTE}({D}|{L}|{S}|{WHITESPACE}|{TAB}|\\n)*{QUOTE}     { ht_insert(ht, "literal", yytext, yylineno); }
({WHITESPACE}|{TAB}|[\r]|{NEW_LINE})+                   { }
[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?                     { ht_insert(ht, "numero", yytext, yylineno); }
{L}({L}|{D}|{UNDERSCORE})*                              { ht_insert(ht, "id_ou_funcao", yytext, yylineno); }
\<|\>|>=|<=|==|<>                                       { ht_insert(ht, "op_relacional", yytext, yylineno); }
\+|\-|\*|\/                                             { ht_insert(ht, "op_aritmetico", yytext, yylineno); }
=                                                       { ht_insert(ht, "atribuicao", yytext, yylineno); }
\(                                                      { ht_insert(ht, "abre_par", yytext, yylineno); }
\)                                                      { ht_insert(ht, "fecha_par", yytext, yylineno); }
\{({L}|{D}|{S}|{WHITESPACE}|{TAB})*\}                   { remove_first_and_last_char(yytext); printf("(%d,comentario,\"%s\")\n", yylineno, yytext);}
,                                                       { ht_insert(ht, "virgula", yytext, yylineno); }
;                                                       { ht_insert(ht, "ponto_e_virg", yytext, yylineno); }
@                                                       { ht_insert(ht, "chamada", yytext, yylineno); }
.                                                       { printf("(%d,ERROR,\"%s\")\n", yylineno, yytext); return 0; }

%%

int main() {
  ht = ht_new();

  yylex();

  ht_dump(ht);

  ht_del_hash_table(ht);

  return 0;
}