#include <stdio.h>
#include "hash_table.h"
#include "syntactic.tab.h"
#include <string.h>
#include <stdlib.h>

extern int yyparse(); // Declaração da função de análise sintática
extern int yylex();   // Declaração da função de análise léxica
extern char *yytext;  // Declaração do texto do token
extern FILE *yyin;    // Declaração do arquivo de entrada

int number_errors = 0;
int current_column = 1;
int verbose = 0;
hash_table *ht = NULL;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "Uso: %s <arquivo de código fonte>\n", argv[0]);
    return 1;
  }
  if (argc >= 3 && !strcmp(argv[2], "-v"))
  {
    printf("VERBOSE ATIVADO\n");
    verbose = 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file)
  {
    fprintf(stderr, "Não foi possível abrir o arquivo %s\n", argv[1]);
    return 1;
  }
  yyin = file;

  ht = (hash_table *)malloc(sizeof(hash_table));
  init_hash_table(ht);

  yyparse();

  if (verbose)
  {
    ht_dump(ht);
  }

  if (number_errors == 0)
  {
    fprintf(stdout, "\n~> Compilado com sucesso.\n");
  }

  fclose(file);
  return 0;
}