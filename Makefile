CC= clang
CFLAGS= -Wall -Wextra -std=c99

SRC_DIR= src
SRC= $(wildcard $(SRC_DIR)/*.c)

INCLUDE_DIR= includes

main: $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@.o $^

clean:
	rm -rf *.o