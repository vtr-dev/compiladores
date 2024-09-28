D [0-9]
L [a-zA-Z]
S [~\`!@#\$%^&*()_\-+\[\]{}|‘?><.\=,]

KEYWORDS funcao|fimfuncao|chama|retorna|tipo|args|fimargs|escreva|inteiro|real|caractere|se|entao|senao|fimse|enquanto|faca|fimenquanto

WHITESPACE [ ]
NEW_LINE [\n]
TAB [\t]
UNDERSCORE [_]
QUOTE \"

%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TABLE_MAX_SIZE 100

struct node {
  char* lex;
  char* token;
  int line;
  struct node* next_node;
} typedef node;

struct hash_table {
  int max_size; 
  node** buckets;
} typedef hash_table;
 
void init_hash_table(hash_table* ht)
{
  ht->max_size = TABLE_MAX_SIZE;
  ht->buckets = (node**)malloc(sizeof(node*) * ht->max_size);
  return;
}

void fill_node(node* node, char* lex, char* token, int line)
{
  node->lex = (char*)malloc(strlen(lex) + 1);
  node->token = (char*)malloc(strlen(token) + 1);
  strcpy(node->token, token);
  strcpy(node->lex, lex);
  node->line = line;
  node->next_node = NULL;
};
 
int hash_function(hash_table* ht, char* lex)
{
  int bucket_index;
  int sum = 0, factor = 31;
  
  for (int i = 0; i < strlen(lex); i++) {
    sum = ((sum % ht->max_size) + (((int)lex[i]) * factor) % ht->max_size) % ht->max_size;
    factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucket_index = sum;
  return bucket_index;
}

void insert(hash_table* ht, char* lex, char* token, int line)
{
  node* new_node = (node*)malloc(sizeof(node));
  fill_node(new_node, lex, token, line);

  int bucket_index = hash_function(ht, lex);
  
  new_node->next_node = ht->buckets[bucket_index];
  ht->buckets[bucket_index] = new_node;

  return;
}

char* search(hash_table* ht, char* lex)
{
  int bucket_index = hash_function(ht, lex);
  node* current_node = ht->buckets[bucket_index];

  while (current_node != NULL) {
    if (strcmp(current_node->lex, lex) == 0) {
      return current_node->token;
    }

    current_node = current_node->next_node;
  }

  return "No token found.\n";
}

char* search_in_line(hash_table* ht, char* lex, int line)
{
  int bucket_index = hash_function(ht, lex);
  node* current_node = ht->buckets[bucket_index];

  while (current_node != NULL) {
    if (strcmp(current_node->lex, lex) == 0 && current_node->line == line) {
      return current_node->token;
    }

    current_node = current_node->next_node;
  }

  return "No token found.\n";
}
 
void delete(hash_table* ht, char* lex)
{
  node* previous_node = NULL;

  int bucket_index = hash_function(ht, lex);
  node* current_node = ht->buckets[bucket_index];

  while (current_node != NULL) {
    if (strcmp(lex, current_node->lex) == 0) {
      if (current_node == ht->buckets[bucket_index]) {
        ht->buckets[bucket_index] = current_node->next_node;
      }
      else {
        previous_node->next_node = current_node->next_node;
      }
      free(current_node);
      break;
    }

    previous_node = current_node;
    current_node = current_node->next_node;
  }

  return;
}

void drop_hash_table(hash_table* ht)
{
  for (int i = 0; i < ht->max_size; i++) {
    node* current_node = ht->buckets[i];

    while (current_node != NULL) {
      node* temp = current_node;
      current_node = current_node->next_node;
      free(temp);
    }
  }

  free(ht->buckets);
  ht->buckets = NULL;
  ht->max_size = 0;
  return;
}

void ht_dump(hash_table* ht)
{
  printf("HASH TABLE DUMP:\n");
  for (int i = 0; i < ht->max_size; i++) {
    node* current_node = ht->buckets[i];

    if (current_node != NULL) {
      printf("\nBucket %d:\n", i);
    }

    while (current_node != NULL) {
      printf("lex: %s, token: %s, line: %d\n", current_node->lex, current_node->token, current_node->line);
      current_node = current_node->next_node;
    }
  }
  
  return;
}

hash_table* ht;

%}

%option yylineno
%x COMMENT

%%

{KEYWORDS}                                              { insert(ht, yytext, yytext, yylineno); } 
{QUOTE}({D}|{L}|{S}|{WHITESPACE}|{TAB}|\\n)*{QUOTE}     { insert(ht, yytext, "literal", yylineno); }
({WHITESPACE}|{TAB}|[\r]|{NEW_LINE})+                   { insert(ht, yytext, "vazio", yylineno);}
[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?                     { insert(ht, yytext, "numero", yylineno); }
{L}({L}|{D}|{UNDERSCORE})*                              { insert(ht, yytext, "id_ou_funcao", yylineno); }
\<|\>|>=|<=|==|<>                                       { insert(ht, yytext, "op_relacional", yylineno); }
\+|\-|\*|\/                                             { insert(ht, yytext, "op_aritmetico", yylineno); }
=                                                       { insert(ht, yytext, "atribuicao", yylineno); }
\(                                                      { insert(ht, yytext, "abre_par", yylineno); }
\)                                                      { insert(ht, yytext, "fecha_par", yylineno); }
\{({L}|{D}|{S}|{WHITESPACE}|{TAB})*\}                   { insert(ht, yytext, "comentario", yylineno);}
,                                                       { insert(ht, yytext, "virgula", yylineno); }
;                                                       { insert(ht, yytext, "ponto_e_virg", yylineno); }
@                                                       { insert(ht, yytext, "chamada", yylineno); }
.                                                       { printf("(%d,ERROR,\"%s\")\n", yylineno, yytext); return 0; }

%%

#define LINE 10

int main() {

  ht = (hash_table*)malloc(sizeof(hash_table));
  init_hash_table(ht);

  yylex();

  ht_dump(ht);

  printf("\nNo line search: %s\n", search(ht, "escreva"));
  printf("Search in line: %s\n", search_in_line(ht, "escreva", 10));

  drop_hash_table(ht);

  return 0;
}