CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Ilexical -Isyntactic

LEX_SRC = lexical/lexical.l
LEX_OUT = lexical/lexical.yy.c
BISON_SRC = syntactic/syntactic.y
BISON_OUT_C = syntactic/syntactic.tab.c
BISON_OUT_H = syntactic/syntactic.tab.h
LEX_OBJS = lexical/lexical.yy.o main.o lexical/hash_table.o
BISON_OBJS = syntactic/syntactic.tab.o
OBJS = $(LEX_OBJS) $(BISON_OBJS)
TARGET = compilador
LIB_PATH = -L/opt/homebrew/opt/flex/lib

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ ${LIB_PATH} -lfl

lexical/lexical.yy.c: $(LEX_SRC) $(BISON_OUT_H)
	$(FLEX) -o $@ $<

syntactic/syntactic.tab.c syntactic/syntactic.tab.h: $(BISON_SRC)
	$(BISON) -d -o syntactic/syntactic.tab.c $(BISON_SRC)

lexical/lexical.yy.o: lexical/lexical.yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

lexical/hash_table.o: lexical/hash_table.c
	$(CC) $(CFLAGS) -c -o $@ $<

syntactic/syntactic.tab.o: syntactic/syntactic.tab.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET) lexical/lexical.yy.c syntactic/syntactic.tab.c syntactic/syntactic.tab.h

.PHONY: all clean
