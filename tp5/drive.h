#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "hardware.h"

#define SECTOR_SIZE 1024

void dump(unsigned char *buffer,
	  unsigned int buffer_size,
	  int ascii_dump,
	  int octal_dump); 
void read_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
