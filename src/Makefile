CC      = cc
CFLAGS  = -O2 -Wall
INCLUDE = -I ../include
LDFLAGS = -L ../lib -lcairo -lpango -lpangocairo -lgobject
PREFIX  = /usr/local
EXEC    = zquote

all: $(EXEC)

$(EXEC): zquote.c qcard.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ $?

clean:
	rm -rf *.o *.out $(EXEC) *.png

.PHONY: all $(EXEC) clean
