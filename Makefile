CC=gcc
CFLAGS=-Wall -Wextra -g -Iinclude
OBJ=$(patsubst src/%.c,build/%.o,$(wildcard src/*.c))

sim: $(OBJ)
	$(CC) $(OBJ) -o sim

build/%.o: src/%.c include/sched.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build sim
