#ifndef DRIVE_H
#define DRIVE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "hardware.h"


#define ENABLE_HDA      1 
#define HDA_FILENAME    "vdiskA.bin"
#define HDA_CMDREG      0x3F6
#define HDA_DATAREGS    0x110
#define HDA_IRQ         14
#define HDA_MAXCYLINDER 16
#define HDA_MAXSECTOR   16
#define HDA_SECTORSIZE  32
#define HDA_STPS        2
#define HDA_STPC        1
#define HDA_PON_DELAY   30
#define HDA_POFF_DELAY  30 

#define SECTOR_SIZE 1024

int is_valid_cylinder(unsigned int cylinder);

int is_valid_sector(unsigned int sector);

int seek_sector(unsigned int cylinder, unsigned int sector);

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer);

void write_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer);

void format_sector(unsigned int cylinder, 
		   unsigned int sector, 
		   unsigned int nsector, 
		   unsigned int value);

void format_all(unsigned int value);

#endif
