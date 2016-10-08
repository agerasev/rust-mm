SRC=src/lib.c
OBJ=$(OUT_DIR)/lib.o
LIB=$(OUT_DIR)/libmmc.a

.phony: all

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $<

$(OBJ): $(SRC)
	gcc -c -fPIC $< -o $@

