CC=			gcc
CFLAGS=		-g -Wall -std=gnu99
LD=			gcc
LDFLAGS=	-L.
AR=			ar
ARFLAGS=	rcs

TARGETS= 	pa02.o \
			gradingPA02

clean:
	rm -f $(TARGETS) *.o

pa02.o:	pa02.c	
	$(CC) $(CFLAGS) -c -o $@ $^ -lgmp

pa02: pa02.o
	$(LD) $(LDFLAGS) -o $@ $^ -lgmp

gradingPA02-local.o:	gradingPA02-local.c	
	$(CC) $(CFLAGS) -c -o $@ $^ -lgmp

gradingPA02-local:	gradingPA02-local.o	
	$(LD) $(LDFLAGS) -o $@ $^ -lgmp