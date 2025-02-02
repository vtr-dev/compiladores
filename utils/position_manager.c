#include "position_manager.h"
#include <string.h>

int line_num = 1;
int col_num = 1;
char line_text[1024];

void pos_init() {
    line_num = 1;
    col_num = 1;
    line_clear();
}

void line_clear() {
    line_text[0] = '\0';
}

void line_append(const char *text) {
    strncat(line_text, text, sizeof(line_text) - strlen(line_text) - 1);
}

void line_next() {
    line_num++;
    col_num = 1;
    line_clear();
}

void col_advance(int len) {
    col_num += len;
}

void col_set(int col) {
    col_num = col;
}

int pos_line() {
    return line_num;
}

int pos_col() {
    return col_num;
}

const char* pos_line_text() {
    return line_text;
}
