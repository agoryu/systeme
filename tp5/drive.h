#ifndef DRIVE_H
#define DRIVE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "hardware.h"

#define SEEK   0x02
#define READ   0x04
#define WRITE  0x6
#define FORMAT 0x08
#define STATUS 0x12
#define DMASET 0x14
#define DSKNFO 0x16
#define MANUF  0xA2
#define DIAG   0xA4

#define SECTOR_SIZE 1024

void dump(unsigned char *buffer,
	  unsigned int buffer_size,
	  int ascii_dump,
	  int octal_dump); 
void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);

#endif
