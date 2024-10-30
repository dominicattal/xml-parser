export TEMP := ./.git/info/tmp
export TMP := ./.git/info/tmp

CC=gcc
CFLAGS=-Wall -Wextra -O3
NAME=parser
SRC_DIR=src
BIN_DIR=bin
OBJ_DIR=obj
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(OBJS)
	@$(CC) $(OBJS) -o $(BIN_DIR)/$(NAME)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/my_program

.PHONY: clean