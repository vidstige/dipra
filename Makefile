CC      := gcc
BIN     := ./bin
OBJ     := ./obj
INCLUDE := ./include
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
OBJS    := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
BINARY  := bin/examples
CFLAGS  := -I$(INCLUDE)
LDLIBS  := -lm

.PHONY: all run clean

all: $(BINARY)

$(BINARY): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ) $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ) $(BIN):
	mkdir $@

run: $(BINARY)
	$<

clean:
	rm -r $(OBJ) $(BINARY)
