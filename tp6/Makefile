ROOTDIR =/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic -m32 -ansi -std=c11
CFLAGS	+= -D_XOPEN_SOURCE=500
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware

BINARIES= dmps frmt
OBJECTS	= drive.o dmps.o frmt.o



all: 	$(BINARIES) $(OBJECTS)


# -------------------------------------------
# This line is for Makefly check
check-syntax:
	gcc $(CFLAGS) -o nul -S $(INCDIR) ${CHK_SOURCES}
# -------------------------------------------


# Deuxieme couche: gestion de volumes
#mbr.o: 	drive.o mbr.h mbr.c
#	$(CC) $(CFLAGS) -c $^ $(INCDIR)


# Premiere couche: acces materiel
frmt:	frmt.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

dmps: 	dmps.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

frmt.o:  drive.h  frmt.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

dmps.o:  drive.h  dmps.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

drive.o: drive.h drive.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)




.PHONY:	clean realclean

clean:
	$(RM) *~ *.o \#*\# nul *.gch

realclean: clean
	$(RM) $(BINARIES) vdiskA.bin vdiskB.bin
