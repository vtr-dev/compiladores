#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "syntactic.tab.h"
#include "position_manager.h"
#include "scope_manager.h"

extern int yyparse();
extern int yylex();
extern char *yytext;
extern FILE *yyin;

int errors_number = 0;
char current_line[1024];
int current_column = 1;
int verbose = 0;
int temp_var_count = 1;
int cond_var_count = 1;
int while_label_count = 1;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "USO CORRETO ~> %s <arquivo_codigo_fonte>\n", argv[0]);
    return 1;
  }
  if (argc >= 3 && !strcmp(argv[2], "-verbose"))
  {
    verbose = 1;
  }

  init_scope_manager();
  pos_init();

  FILE *file = fopen(argv[1], "r");
  if (!file)
  {
    fprintf(stderr, "Arquivo %s não encontrado\n", argv[1]);
    return 1;
  }
  yyin = file;

  yyparse();

  if (verbose)
  {
    dump_all_scopes_by_level();
  }

  exit_scope();

  if (!errors_number)
  {
    fprintf(stdout, "\n~> Compilado com sucesso! ✅\n\n");
  }
  else
  {
    fprintf(stdout, "\n~> Compilação falhou com %d erro(s)! ❌\n\n", errors_number);

    if (access("main.bril", F_OK) == 0)
    {
      unlink("main.bril");
    }
  }

  fclose(file);
  return 0;
}