CC      := cc
CFLAGS  := -std=c11 -O2 -Wall -Wextra
INCLUDE := -Iinclude
SRC     := src/main.c src/life.c src/term.c
BIN     := life

all: $(BIN)

$(BIN): $(SRC) include/life.h
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)

