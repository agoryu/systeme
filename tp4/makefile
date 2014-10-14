CC	= gcc
CFLAGS	= -Wall -Werror -pedantic -m32
CFLAGS	+= -D_XOPEN_SOURCE=500
CFLAGS	+= -g

dirve		: main.c drive.o
			$(CC) $(CFLAGS) main.c drive.o -o drive

drive.o	: drive.c drive.h
			$(CC) $(CFLAGS) -c drive.c

.PHONY: clean

clean	:
		$(RM) -f *~ *.o
