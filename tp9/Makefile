#ROOTDIR =../libhardware
ROOTDIR =/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -Werror -ansi -pedantic -m32 
CFLAGS  += -std=c11
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware


BINARIES =  test
OBJECTS  =  mi_kernel.o mi_user.o

TRASHFILE = *.gch *~ \#*\# nul



all: 	$(BINARIES) $(OBJECTS)


# -------------------------------------------
# This line is for Makefly check
check-syntax:
	gcc $(CFLAGS) -o nul -S $(INCDIR) ${CHK_SOURCES}
# -------------------------------------------

# Quatrième couche: manipulation de fichiers
test: mi_user.o mi_kernel.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

mi_user.o: mi_user.c mi_syscall.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

mi_kernel.o: mi_kernel.c mi_syscall.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)





.PHONY:	clean cleantrash cleandoc cleanbin realclean doc

cleantrash:
	$(RM) $(TRASHFILE)

clean: cleantrash
	$(RM) *.o

cleandoc:
	$(RM) -R ./html/

cleanbin:
	$(RM) $(BINARIES)

cleandisk:
	$(RM) vdiskA.bin vdiskB.bin

realclean: clean cleandoc cleanbin cleandisk

doc:
	doxygen doxygen_log.txt
