CC       := gcc
BIN      := ../bin/
LIB      := ../lib/
INCLUDE  := ../include/
SRCS     := $(wildcard *.c)
BINARIES := $(SRCS:%.c=../bin/%)
CFLAGS   := -I$(INCLUDE)
LDLIBS   := -ldipra -lm

.PHONY: all clean

all: $(BINARIES)

$(BIN)%: %.c | $(BIN)
	$(CC) $< $(CFLAGS) -o $@ -L$(LIB) $(LDLIBS)

$(BIN):
	mkdir $@

clean:
	rm -r $(BIN)
