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
#include<math.h>

struct node {
  char* key;
  char* value;
  int line;
  struct node* next;
}
 
void setNode(struct node* node, char* key, char* value, int line)
{
  node->key = (char*)malloc(strlen(key) + 1);
  node->value = (char*)malloc(strlen(value) + 1);
  strcpy(node->key, key);
  strcpy(node->value, value);
  node->line = line;
  node->next = NULL;
};
 
struct hash_table {
  int numOfElements, capacity; 
  struct node** arr;
};
 
void initialize_hash_table(struct hash_table* ht)
{
  ht->capacity = 100;
  ht->numOfElements = 0;
  ht->arr = (struct node**)malloc(sizeof(struct node*) * ht->capacity);
  return;
}
 
int hashFunction(struct hash_table* ht, char* key)
{
  int bucketIndex;
  int sum = 0, factor = 31;
  
  for (int i = 0; i < strlen(key); i++) {
    sum = ((sum % ht->capacity) + (((int)key[i]) * factor) % ht->capacity) % ht->capacity;
    factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucketIndex = sum;
  return bucketIndex;
}

char* search(struct hash_table* ht, char* key)
{
  int bucketIndex = hashFunction(ht, key);
  
  struct node* bucketHead = ht->arr[bucketIndex];
  while (bucketHead != NULL) {
    if (strcmp(bucketHead->key, key) == 0) {
      return bucketHead->value;
    }

    bucketHead = bucketHead->next;
  }
  return "Oops! No data found.\n";
}
 
void insert(struct hash_table* ht, char* key, char* value, int line)
{
  int bucketIndex = hashFunction(ht, key);
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  setNode(newNode, key, value, line);

  if (ht->arr[bucketIndex] == NULL) {
    ht->arr[bucketIndex] = newNode;
  }

  else {
    newNode->next = ht->arr[bucketIndex];
    ht->arr[bucketIndex] = newNode;
  }

  return;
}
 
void delete (struct hash_table* ht, char* key)
{
  int bucketIndex = hashFunction(ht, key);

  struct node* prevNode = NULL;

  struct node* currNode = ht->arr[bucketIndex];

  while (currNode != NULL) {
    if (strcmp(key, currNode->key) == 0) {
      if (currNode == ht->arr[bucketIndex]) {
          ht->arr[bucketIndex] = currNode->next;
      }
      else {
          prevNode->next = currNode->next;
      }
      free(currNode);
      break;
    }
    prevNode = currNode;
    currNode = currNode->next;
  }

  return;
}

void delete_hash_table(struct hash_table* ht)
{
  for (int i = 0; i < ht->capacity; i++) {
    struct node* current = ht->arr[i];
    while (current != NULL) {
      struct node* temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(ht->arr);
  ht->arr = NULL;
  ht->numOfElements = 0;
  ht->capacity = 0;
  return;
}

void ht_dump(struct hash_table* ht)
{
  printf("---> Hash Table Dump:\n");
  for (int i = 0; i < ht->capacity; i++) {
    struct node* current = ht->arr[i];
    if (current != NULL) {
      printf("\nBucket %d:\n", i);
    }
    while (current != NULL) {
      printf("Key: %s, Value: %s, Line: %d\n", current->key, current->value, current->line);
      current = current->next;
    }
  }
  return;
}

struct hash_table* ht;
    
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

{KEYWORDS}                                              { insert(ht, yytext, yytext, yylineno); } 
{QUOTE}({D}|{L}|{S}|{WHITESPACE}|{TAB}|\\n)*{QUOTE}     { insert(ht, "literal", yytext, yylineno); }
({WHITESPACE}|{TAB}|[\r]|{NEW_LINE})+                   { insert(ht, "vazio", yytext, yylineno);}
[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?                     { insert(ht, "numero", yytext, yylineno); }
{L}({L}|{D}|{UNDERSCORE})*                              { insert(ht, "id_ou_funcao", yytext, yylineno); }
\<|\>|>=|<=|==|<>                                       { insert(ht, "op_relacional", yytext, yylineno); }
\+|\-|\*|\/                                             { insert(ht, "op_aritmetico", yytext, yylineno); }
=                                                       { insert(ht, "atribuicao", yytext, yylineno); }
\(                                                      { insert(ht, "abre_par", yytext, yylineno); }
\)                                                      { insert(ht, "fecha_par", yytext, yylineno); }
\{({L}|{D}|{S}|{WHITESPACE}|{TAB})*\}                   { remove_first_and_last_char(yytext); insert(ht, "comentario", yytext, yylineno);}
,                                                       { insert(ht, "virgula", yytext, yylineno); }
;                                                       { insert(ht, "ponto_e_virg", yytext, yylineno); }
@                                                       { insert(ht, "chamada", yytext, yylineno); }
.                                                       { printf("(%d,ERROR,\"%s\")\n", yylineno, yytext); return 0; }

%%

int main() {

  ht = (struct hash_table*)malloc(sizeof(struct hash_table));
  initialize_hash_table(ht);

  yylex();

  ht_dump(ht);

  delete_hash_table(ht);

  return 0;
}