ROOTDIR =../libhardware
#ROOTDIR =/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic -m32 -std=c11
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware


BINARIES= dmps frmt mkvol dvol validation_volume mknfs dfs
OBJ_LIB	= drive.o mbr.o vol.o inode.o ifile.o
OBJ_EXE = dmps.o frmt.o mkvol.o dvol.o 
OBJ_EXE += validation_volume.o mknfs.o dfs.o
OBJECTS = $(OBJ_LIB) $(OBJ_EXE)



all: 	$(BINARIES) $(OBJECTS)


# -------------------------------------------
# This line is for Makefly check
check-syntax:
	gcc $(CFLAGS) -o nul -S $(INCDIR) ${CHK_SOURCES}
# -------------------------------------------

# Quatrième couche: manipulation de fichiers
ifile.o: ifile.h ifile.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

# Troisième couche (2e partie): structure d'un fichier
inode.o: inode.h inode.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

# Troisième couche (1ere partie): structure d'un volume
mknfs: mknfs.o vol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

dfs: dfs.o vol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

validation_volume: validation_volume.o vol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

dfs.o: vol.h dfs.c mbr.h drive.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

mknfs.o: vol.h mknfs.c mbr.h drive.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

validation_volume.o: vol.h validation_volume.c mbr.h drive.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

vol.o: vol.h vol.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

# Deuxieme couche: gestion de volumes
mkvol: 	mkvol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

dvol: 	dvol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

mkvol.o: mbr.h mkvol.c drive.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

dvol.o:	mbr.h dvol.c drive.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

mbr.o:  mbr.h mbr.c drive.h
	$(CC) $(CFLAGS) -c $^ $(INCDIR)


# Premiere couche: acces materiel
frmt:	frmt.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

dmps: 	dmps.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

frmt.o: drive.h  frmt.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

dmps.o: drive.h  dmps.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)

drive.o: drive.h drive.c
	$(CC) $(CFLAGS) -c $^ $(INCDIR)



.PHONY:	clean realclean doc

clean:
	$(RM) *~ *.o \#*\# nul *.gch

cleandoc:
	$(RM) -R ./html/

realclean: clean cleandoc
	$(RM) $(BINARIES) vdiskA.bin vdiskB.bin

doc:
	doxygen doxygen_log.txt
