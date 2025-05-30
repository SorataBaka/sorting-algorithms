CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = sort.o
BIN_DIR = bin

all: $(BIN_DIR)/counting $(BIN_DIR)/insert $(BIN_DIR)/bubble $(BIN_DIR)/shaker $(BIN_DIR)/quick

$(OBJ): sort.c sort.h
	$(CC) $(CFLAGS) -c sort.c -o sort.o

$(BIN_DIR)/counting: counting.c $(OBJ)
	$(CC) $(CFLAGS) counting.c sort.o -o $(BIN_DIR)/counting

$(BIN_DIR)/insert: insert.c $(OBJ)
	$(CC) $(CFLAGS) insert.c sort.o -o $(BIN_DIR)/insert

$(BIN_DIR)/bubble: bubble.c $(OBJ)
	$(CC) $(CFLAGS) bubble.c sort.o -o $(BIN_DIR)/bubble

$(BIN_DIR)/shaker: shaker.c $(OBJ)
	$(CC) $(CFLAGS) shaker.c sort.o -o $(BIN_DIR)/shaker

$(BIN_DIR)/quick: quick.c $(OBJ)
	$(CC) $(CFLAGS) quick.c sort.o -o $(BIN_DIR)/quick

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/*
