CC	= gcc
CFLAGS	= -Wall -Werror -pedantic -m32
CFLAGS	+= -D_XOPEN_SOURCE=500
CFLAGS	+= -g

context		: main.c context.o hw.o
			$(CC) $(CFLAGS) main.c context.o hw.o -o context

context.o	: context.c context.h
			$(CC) $(CFLAGS) -c context.c
			
hw.o		: hw.c hw.h
			$(CC) $(CFLAGS) -c hw.c

.PHONY: clean

clean	:
		$(RM) -f *~ *.o
