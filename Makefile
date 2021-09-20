IDIR=include
CC=gcc
CFLAGS=-g -I$(IDIR) -O3 -Wall -std=gnu99
#CFLAGS_DEBUG=-ggdb $(CFLAGS)

PNAME=pico-wars

ODIR=obj
LDIR=lib

LIBS=-lm -lcriterion -lncurses -lrt

_DEPS = uthash.h utlist.h comm.h draw.h game.h tilemap.h board.h units.h defines.h units.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tilemap.o draw.o game.o board.o

_MAIN_OBJ = $(_OBJ) main.o
MAIN_OBJ = $(patsubst %,$(ODIR)/%,$(_MAIN_OBJ))

_TEST_OBJ = $(_OBJ) test.o
TEST_OBJ = $(patsubst %,$(ODIR)/%,$(_TEST_OBJ))


$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pico-wars: $(MAIN_OBJ)
	$(CC) -o $(PNAME) $^ $(CFLAGS) $(LIBS)

test: $(TEST_OBJ)
	$(CC) -o test $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~