CC      := gcc
OBJ     := obj/
LIB     := lib/
INCLUDE := include/
SRC     := src/
SRCS    := $(wildcard $(SRC)*.c)
OBJS    := $(patsubst $(SRC)%.c,$(OBJ)%.o,$(SRCS))
LIBRARY := lib/libdipra.a
CFLAGS  := -I$(INCLUDE)
LDLIBS  := -lm

.PHONY: all examples clean

all: $(LIBRARY)

examples:
	make -C examples

$(LIBRARY): $(OBJS) | $(LIB)
	ar rcs $@ $^
#	ranlib $@

$(OBJ)%.o: $(SRC)%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ) $(LIB):
	mkdir $@

clean:
	rm -r $(OBJ) $(LIBRARY)
