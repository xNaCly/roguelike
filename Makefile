CFLAGS := -std=c23 \
	-fdiagnostics-color=always \
	-Wall \
	-Wpedantic \
	-Wextra \
	-Wshadow \
	-Wundef \
	-fno-common
FILES := $(shell find ./src -name "*.c")

all: build-full
	./rogue

debug: build-debug
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		 ./rogue-debug

build-full:
	$(CC) $(CFLAGS) -O1 $(FILES) -o rogue

build-debug:
	$(CC) $(CFLAGS) -g3 $(FILES) -o rogue-debug
