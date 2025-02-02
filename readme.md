```
bison -d -Wcounterexamples -o syntactic/syntactic.tab.c syntactic/syntactic.y
```

Semântico:

<!-- - [ ] Verificar se uma variável já tem o valor atribuído para realizar certas operações ( A linguagem C não faz isso);
--- [ ] Operação de atribuição
--- [ ] Operação de comparação
--- [ ] Chamada de função
--- [ ] Operação matemática -->

- [x] Verificar se o retorno da função é compatível com o tipo de retorno da função
- [x] Verificar ao final de uma função que tem tipo de retorno, se há algum retorno daquele tipo;
- [x] Verificar se as variáveis estão isolados no próprio escopo;
--- [x] Variáveis locais de funções não podem ser acessadas em outras funções;
--- [x] Argumentos não permitem declaração de variáveis de mesmo nome;
--- [x] Não pode realizar a declaração da mesma variável mais de uma vez;
--- [x] Não pode realizar a declaração de uma mesma função mais de uma vez;
--- [x] Variáveis locais em bloco SE e ENQUANTO não podem ser acessíveis fora desses blocos;
--- [x] Variáveis locais de funções podem ser acessadas em blocos SE e ENQUANTO;

- [x] Verificar na atribuição se o tipo entre lhs e rhs são compatíveis;
--- [x] Verificar no caso em lhs é de uma declaração;
--- [x] Verificar no caso em que lhs é uma variável já declarada;
--- [x] Verificar no caso em que lhs é uma argumento da função;
--- [x] Verificar no caso em que rhs é uma argumento da função;
--- [x] Verificar no caso em que rhs é uma variável;
--- [x] Verificar no caso em que rhs é valor (inteiro, real, literal, caractere);
--- [x] Verificar no caso em que rhs é chamada de função;
--- [x] Verificar no caso em que rhs é uma operação matemática;

- [ ] Verificar na comparação se o tipo entre lhs e rhs são compatíveis;
--- [ ] Verificar no caso em que lhs é uma variável já declarada;
--- [ ] Verificar no caso em que lhs é uma argumento da função;
--- [ ] Verificar no caso em que lhs é um valor (inteiro, real, literal, caractere);
--- [ ] Verificar no caso em que rhs é uma variável já declarada;
--- [ ] Verificar no caso em que rhs é uma argumento da função;
--- [ ] Verificar no caso em que rhs é um valor (inteiro, real, literal, caractere);


- [ ] Verificar na chamada de função se o tipo dos parâmetros passados e os parâmetros esperados são compatíveis;
- [ ] Verificar na chamada de função se a quantidade de parâmetros estão corretos;
- [ ] Verificar na chamada de função se a função existe;

- [ ] Verificar se a expressão matématica funciona








MELHORIAS

- [ ] Permitir parâmetros além de identificadores
LISTA_PARAMETROS_CHAMADA:
    PARAMETRO_CHAMADA LISTA_PARAMETROS_CHAMADA {
        production("LISTA_PARAMETROS_CHAMADA -> TOKEN_IDENTIFICADOR LISTA_PARAMETROS_CHAMADA");
        $2.names = realloc($2.names, sizeof(char*) * ($2.count + 1));
        $2.names[$2.count++] = strdup($1);
        $$ = $2;
    }
    | // VAZIO
    ;

PARAMETRO_CHAMADA: 
    | TOKEN_IDENTIFICADOR {
        production("LISTA_CHAMA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR");
        $$ = (id_list_info){.count = 1, .names = malloc(sizeof(char*))};
        $$.names[0] = strdup($1);
    }
    | VALOR {
        production("LISTA_CHAMA_IDENTIFICADORES -> TOKEN_IDENTIFICADOR");
        $$ = (id_list_info){.count = 1, .names = malloc(sizeof(char*))};
        $$.names[0] = strdup($1);
    }
    ;