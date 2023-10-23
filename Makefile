
SRC_DIR := ./src
INC_DIR := ./include
OBJ_DIR := ./objects
BIN_DIR := ./bin

CC := gcc
CFLAGS := -std=c99 -Wall -O2

ifeq ($(DEBUG),1)
	OFLAGS := -g -D_PRINTING
else
	OFLAGS := -g
endif

BF_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-bf.o $(OBJ_DIR)/strings.o
KMP_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-kmp.o $(OBJ_DIR)/strings.o
KMP2_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-kmp2.o $(OBJ_DIR)/strings.o
STRSTR_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-strstr.o $(OBJ_DIR)/strings.o
RK_CH_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-rk-ch.o $(OBJ_DIR)/strings.o
RK_RF_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-rk-rf.o $(OBJ_DIR)/strings.o
MEMCHR_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-memchr.o $(OBJ_DIR)/strings.o
MEMCHR_KMP_OBJS := $(OBJ_DIR)/substring.o $(OBJ_DIR)/strsearch-memchr-kmp.o $(OBJ_DIR)/strings.o

all: $(BIN_DIR)/subs-bf $(BIN_DIR)/subs-kmp $(BIN_DIR)/subs-kmp2 $(BIN_DIR)/subs-strstr \
$(BIN_DIR)/subs-rk-ch $(BIN_DIR)/subs-rk-rf $(BIN_DIR)/subs-memchr $(BIN_DIR)/subs-memchr-kmp

$(BIN_DIR)/subs-bf: $(BF_OBJS)
	$(CC) $(CFLAGS) $(BF_OBJS) -o $@

$(BIN_DIR)/subs-kmp: $(KMP_OBJS)
	$(CC) $(CFLAGS) $(KMP_OBJS) -o $@

$(BIN_DIR)/subs-kmp2: $(KMP2_OBJS)
	$(CC) $(CFLAGS) $(KMP2_OBJS) -o $@

$(BIN_DIR)/subs-strstr: $(STRSTR_OBJS)
	$(CC) $(CFLAGS) $(STRSTR_OBJS) -o $@

$(BIN_DIR)/subs-rk-ch: $(RK_CH_OBJS)
	$(CC) $(CFLAGS) $(RK_CH_OBJS) -o $@

$(BIN_DIR)/subs-rk-rf: $(RK_RF_OBJS)
	$(CC) $(CFLAGS) $(RK_RF_OBJS) -o $@

$(BIN_DIR)/subs-memchr: $(MEMCHR_OBJS)
	$(CC) $(CFLAGS) $(MEMCHR_OBJS) -o $@

$(BIN_DIR)/subs-memchr-kmp: $(MEMCHR_KMP_OBJS)
	$(CC) $(CFLAGS) $(MEMCHR_KMP_OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(INC_DIR) $(CFLAGS) $(OFLAGS) -o $@ $^ -c

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*
