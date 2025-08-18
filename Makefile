CC      := cc
CFLAGS  := -std=c11 -O2 -Wall -Wextra -Iinclude -D_POSIX_C_SOURCE=199309L
INCLUDE := -Iinclude
SRC     := src/main.c src/life.c src/term.c
BIN     := life

all: $(BIN)

$(BIN): $(SRC) include/life.h
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)

