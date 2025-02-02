#ifndef POSITION_MANAGER_H
#define POSITION_MANAGER_H

#include <stdio.h>

extern int line_num;
extern int col_num;
extern char line_text[1024];

void pos_init();

void line_clear();

void line_append(const char *text);

void line_next();

void col_advance(int len);

void col_set(int col);

int pos_line();

int pos_col();

const char* pos_line_text();

#endif
