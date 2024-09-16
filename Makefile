CFLAGS := -std=c23 -O1
FILES := $(shell find ./src -name "*.c")

all: build-full
	./rogue

build-full:
	$(CC) $(CFLAGS) $(FILES) -o rogue
