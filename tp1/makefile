CC	= gcc
CFLAGS	= -Wall -Werror -pedantic -m32
CFLAGS	+= -D_XOPEN_SOURCE=500
CFLAGS	+= -g

try		: try_mul.c try.o
		$(CC) $(CFLAGS) try_mul.c try.o -o try

try.o		: try.c try.h
		$(CC) $(CFLAGS) -c try.c

.PHONY: clean

clean	:
	$(RM) -f *~ *.o
