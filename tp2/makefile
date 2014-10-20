CC	= gcc
CFLAGS	= -Wall -Werror -pedantic -m32
CFLAGS	+= -D_XOPEN_SOURCE=500
CFLAGS	+= -g

context		: main.c context.o
			$(CC) $(CFLAGS) main.c context.o -o context

context.o	: context.c context.h
			$(CC) $(CFLAGS) -c context.c

.PHONY: clean

clean	:
		$(RM) -f *~ *.o
