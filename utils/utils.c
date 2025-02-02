#include "utils.h"

const char *VarTypeLabels[] = {
    "Inteiro",       // TYPE_INT
    "Real",   // TYPE_REAL
    "Caractere",     // TYPE_CHAR
    "Literal",        // TYPE_STRING
    "Indefinido" // TYPE_UNDEFINED
};

const char *SymbolKindLabels[] = {
    "Variavel",         // SYMBOL_VAR
    "Funcao",         // SYMBOL_FUNC
    "Argumento",        // SYMBOL_PARAM
    "Simbolo indefinido"  // SYMBOL_UNDEFINED
};

const char *var_type_to_label(var_type type) {
    if (type >= 0 && type <= TYPE_UNDEFINED) {
        return VarTypeLabels[type];
    }
    return "Unknown Type";
}

const char *symbol_kind_to_label(symbol_kind kind) {
    if (kind >= 0 && kind <= SYMBOL_UNDEFINED) {
        return SymbolKindLabels[kind];
    }
    return "Unknown Symbol";
}

int is_integer(const char* str) {
    char *endptr;
    strtol(str, &endptr, 10);

    if (*endptr != '\0') {
        return 0;
    }
    return 1;
}

int is_real(const char* str) {
    char *endptr;
    strtod(str, &endptr);

    if (*endptr != '\0') {
        return 0;
    }
    return strchr(str, '.') != NULL;
}

char *combine_postfix(const char *op1, const char *op2, const char *oper) {
    int size = strlen(op1) + strlen(op2) + strlen(oper) + 3;
    char *result = malloc(size);
    snprintf(result, size, "%s %s %s", op1, op2, oper);
    return result;
}

char *combine_unary_postfix(const char *op, const char *unary_op) {
    int size = strlen(op) + strlen(unary_op) + 2;
    char *result = malloc(size);
    snprintf(result, size, "%s %s", op, unary_op);
    return result;
}