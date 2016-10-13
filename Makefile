.phony: all

all: $(OUT_DIR)/libmmc.a

$(OUT_DIR)/libmmc.a: $(OUT_DIR)/lib.o $(OUT_DIR)/window.o $(OUT_DIR)/error.o $(OUT_DIR)/time.o $(OUT_DIR)/event.o
	ar rcs $@ $^

$(OUT_DIR)/lib.o: src/lib.c
	gcc -c -fPIC $< -o $@

$(OUT_DIR)/window.o: src/window.c
	gcc -c -fPIC $< -o $@

$(OUT_DIR)/error.o: src/error.c
	gcc -c -fPIC $< -o $@

$(OUT_DIR)/time.o: src/time.c
	gcc -c -fPIC $< -o $@

$(OUT_DIR)/event.o: src/event.c
	gcc -c -fPIC $< -o $@