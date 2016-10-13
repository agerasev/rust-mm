CFLAGS=-IC:/devel/lib/SDL2/include
CC=gcc
AR=ar

SRC_DIR=src/mmc

_SRCS=lib.c error.c window.c event.c time.c
_HEADERS=error.h window.h event.h time.h

_OBJS=$(_SRCS:%.c=%.o)
SRCS=$(_SRCS:%=$(SRC_DIR)/%)
HEADERS=$(_HEADERS:%=$(SRC_DIR)/%)
OBJS=$(_OBJS:%=$(OUT_DIR)/%)

.phony: all

all: $(OUT_DIR)/libmmc.a

$(OUT_DIR)/libmmc.a: $(OBJS)
	$(AR) rcs $@ $^

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) -c $< -o $@ $(CFLAGS)