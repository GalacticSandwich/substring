
SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./objects
BIN_DIR := ./bin

CC := gcc
CFLAGS := -std=c99 -Wall -O2

ifeq ($(DEBUG),1)
	OFLAGS := -g -D_VERBOSE
else
	OFLAGS := -g
endif

KMP_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-kmp.o $(OBJ_DIR)/strings.o
STRSTR_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-strstr.o $(OBJ_DIR)/strings.o

all: $(BIN_DIR)/subs-kmp $(BIN_DIR)/subs-strstr

$(BIN_DIR)/subs-kmp: $(KMP_OBJS)
	$(CC) $(CFLAGS) $(KMP_OBJS) -o $@

$(BIN_DIR)/subs-strstr: $(STRSTR_OBJS)
	$(CC) $(CFLAGS) $(STRSTR_OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(INC_DIR) $(CFLAGS) $(OFLAGS) -o $@ $^ -c

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*
