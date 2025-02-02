CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Ilexical -Isyntactic -Isemantic -Iutils -Wall -Wextra -g

LEX_SRC = lexical/lexical.l
LEX_OUT = lexical/lexical.yy.c

BISON_SRC = syntactic/syntactic.y
BISON_OUT_C = syntactic/syntactic.tab.c
BISON_OUT_H = syntactic/syntactic.tab.h

LEX_OBJS = lexical/lexical.yy.o lexical/hash_table.o
BISON_OBJS = syntactic/syntactic.tab.o syntactic/scope_manager.o 
SEMANTIC_OBJS = semantic/semantic_rules.o semantic/semantic_utils.o semantic/semantic_translate.o
UTILS_OBJS = utils/position_manager.o utils/utils.o
MAIN_OBJ = main.o
LIB_PATH = -L/opt/homebrew/opt/flex/lib

OBJS = $(UTILS_OBJS) $(LEX_OBJS) $(SEMANTIC_OBJS) $(BISON_OBJS) $(MAIN_OBJ)

TARGET = compilador

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIB_PATH) -lfl

lexical/lexical.yy.c: $(LEX_SRC) $(BISON_OUT_H)
	$(FLEX) -o $@ $<

syntactic/syntactic.tab.c syntactic/syntactic.tab.h: $(BISON_SRC)
	$(BISON) -d -o syntactic/syntactic.tab.c $(BISON_SRC)

utils/position_manager.o: utils/position_manager.c utils/utils.c
	$(CC) $(CFLAGS) -c -o $@ $<

lexical/lexical.yy.o: lexical/lexical.yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

lexical/hash_table.o: lexical/hash_table.c
	$(CC) $(CFLAGS) -c -o $@ $<

syntactic/syntactic.tab.o: syntactic/syntactic.tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

syntactic/scope_manager.o: syntactic/scope_manager.c
	$(CC) $(CFLAGS) -c -o $@ $<

semantic/semantic_utils.o: semantic/semantic_utils.c
	$(CC) $(CFLAGS) -c -o $@ $<

semantic/semantic_rules.o: semantic/semantic_rules.c
	$(CC) $(CFLAGS) -c -o $@ $<

semantic/semantic_translate.o: semantic/semantic_translate.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET) main.bril lexical/lexical.yy.c syntactic/syntactic.tab.c syntactic/syntactic.tab.h

.PHONY: all clean
