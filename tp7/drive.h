#ifndef _DRIVE_H_
#define _DRIVE_H_

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
#define HDA_SECTORSIZE  256
#define HDA_STPS        2
#define HDA_STPC        1
#define HDA_PON_DELAY   30
#define HDA_POFF_DELAY  30 


int is_valid_cylinder(const unsigned int cylinder);

int is_valid_sector(const unsigned int sector);

int seek_sector(const unsigned int cylinder, const unsigned int sector);

void read_sector(const unsigned int cylinder, 
		 const unsigned int sector, 
		 unsigned char* buffer);

void read_sector_n(const unsigned int cylinder, 
		   const unsigned int sector, 
		   unsigned char* buffer, 
		   const size_t n);

void write_sector(const unsigned int cylinder, 
		  const unsigned int sector, 
		  const unsigned char* buffer);

void write_sector_n(const unsigned int cylinder, 
		    const unsigned int sector, 
		    const unsigned char* buffer,
		    const size_t n);

void format_sector(const unsigned int cylinder, 
		   const unsigned int sector, 
		   const unsigned int nsector, 
		   const unsigned int value);

void format_all(const unsigned int value);

#endif
