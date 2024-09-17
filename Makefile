CFLAGS := -std=c23 \
	-O2 \
	-Wall \
	-Wextra \
	-Werror \
	-fdiagnostics-color=always \
	-fsanitize=address,undefined \
	-fno-common \
	-Winit-self \
	-Wfloat-equal \
	-Wundef \
	-Wshadow \
	-Wpointer-arith \
	-Wcast-align \
	-Wstrict-prototypes \
	-Wstrict-overflow=5 \
	-Wwrite-strings \
	-Waggregate-return \
	-Wcast-qual \
	-Wswitch-default \
	-Wswitch-enum \
	-Wunreachable-code \
	-Wno-discarded-qualifiers\
	-Wpedantic 
FILES := $(shell find ./src -name "*.c")

all: build-full
	./rogue

debug: build-debug
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		 ./rogue-debug

build-full:
	$(CC) $(CFLAGS) $(FILES) -o rogue

build-debug:
	$(CC) $(CFLAGS) -g3 $(FILES) -o rogue-debug
