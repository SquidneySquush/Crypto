CC=			gcc
CFLAGS=		-g -Wall -std=gnu99
LD=			gcc
LDFLAGS=	-L.
AR=			ar
ARFLAGS=	rcs

TARGETS= 	pa01.o \
			gradingPA01

clean:
	rm -f $(TARGETS) *.o

pa01.o:	pa01.c	
	$(CC) $(CFLAGS) -c -o $@ $^ -lgmp

pa01: pa01.o
	$(LD) $(LDFLAGS) -o $@ $^ -lgmp

gradingPA01-local.o:	gradingPA01-local.c	
	$(CC) $(CFLAGS) -c -o $@ $^ -lgmp

gradingPA01-local:	gradingPA01-local.o	
	$(LD) $(LDFLAGS) -o $@ $^ -lgmp