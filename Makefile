CFLAGS := -std=c23 \
	-O1 \
	-fdiagnostics-color=always \
	-Wall \
	-g3 \
	-Wpedantic \
	-Wextra \
	-Wshadow \
	-Wundef \
	-fno-common
FILES := $(shell find ./src -name "*.c")

all: build-full
	./rogue

build-full:
	$(CC) $(CFLAGS) $(FILES) -o rogue
