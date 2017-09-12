CC      = cc
CFLAGS  = -O2 -Wall
LDFLAGS = -L ../lib -lcairo -lpango -lpangocairo -lgobject
LDFLAGS = `pkg-config --cflags --libs pango` \
		  `pkg-config --cflags --libs cairo` \
		  `pkg-config --cflags --libs pangocairo` \
		  `pkg-config --cflags --libs glib-2.0`
PREFIX  = /usr/local
EXEC    = zquote

all: $(EXEC)

$(EXEC): zquote.c qcard.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ $?

clean:
	rm -rf *.o *.out $(EXEC)

.PHONY: all $(EXEC) clean
