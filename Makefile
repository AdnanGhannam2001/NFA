CC= clang
CFLAGS= -Wall -Wextra -std=c99

DEBUG ?= 0

ifeq ($(DEBUG), 0)
	CFLAGS+= -O3 -static
else
	CFLAGS+= -g -Wpedantic -Werror -Wshadow -Wconversion -Wsign-conversion -Wfloat-equal -Wuninitialized -Wnull-dereference -Wpointer-sign -Wcast-qual 
endif

SRC_DIR= src
SRC= $(wildcard $(SRC_DIR)/*.c)

INCLUDE_DIR= includes

main: $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@.o $^

clean:
	rm -rf *.o